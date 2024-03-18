#include "cMeshImporter.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <math/hash/MurmurHash3.h>

#include <fstream>
#include <map>

//////////////////////////////////////////////////////////////////

#define RAD_DEG_CONST 57.2957795

cMeshImporter::cMeshImporter( std::string _path, std::string _out, eMeshImporterFlags _flags ):
	m_outpath{ _out }
{
	m_filename = _path.substr( _path.find_last_of( "/\\" ) + 1 );
	m_filename = m_filename.substr( 0, m_filename.find_last_of( "." ) );

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile( _path, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded );

	// TODO: change to wv::assert
	if ( !scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode )
	{
		printf( "ERROR::ASSIMP::%s\n", importer.GetErrorString() );
		return;
	}

	processAssimpNode( scene->mRootNode, scene );	
	loadCompartments();

	if ( _flags & MeshImporterFlags_ImportAsVehicle )
		importAsBlueprint();
	else
		importAsCompartments();

}

//////////////////////////////////////////////////////////////////

cMeshImporter::~cMeshImporter( void )
{
	for ( int i = 0; i < m_compartments.size(); i++ )
		delete m_compartments[ i ];
	
	for ( int i = 0; i < m_meshes.size(); i++ )
		delete m_meshes[ i ];

}

//////////////////////////////////////////////////////////////////

void cMeshImporter::loadCompartments( void )
{
	for ( int i = 0; i < m_meshes.size(); i++ )
		processMeshToCompartment( m_meshes[ i ] );
}

//////////////////////////////////////////////////////////////////

void cMeshImporter::processMeshToCompartment( sMesh* _mesh )
{
	if ( !_mesh )
	{
		printf( "No mesh\n" );
		return;
	}

	sCompartment* comp = new sCompartment();
	comp->name = _mesh->name;

	// TODO: make faster with resize and memcpy 
	// comp->compartment.points.resize( _mesh->vertices.size() * 3 );
	comp->pos = { _mesh->position.x, _mesh->position.y, _mesh->position.z };
	comp->rot = { _mesh->rotation.x, _mesh->rotation.y, _mesh->rotation.z };

	comp->compartment = {
		.points = { },
		.sharedPoints = {},
		.thicknessMap = {},
		.faceMap = {}
	};
	
	for ( int i = 0; i < _mesh->vertices.size(); i++ )
	{
		comp->compartment.points.push_back( _mesh->vertices[ i ].x );
		comp->compartment.points.push_back( _mesh->vertices[ i ].y );
		comp->compartment.points.push_back( _mesh->vertices[ i ].z );
		comp->compartment.thicknessMap.push_back( 1 );
	}
	
	recalculateSharedPoints( comp, _mesh );

	for ( int i = 0; i < _mesh->faces.size(); i++ )
	{
		std::vector<int> face_vec;
		for ( int j = 0; j < _mesh->faces[ i ].indices.size(); j++ )
			face_vec.push_back( _mesh->faces[ i ].indices[ j ] );
		
		comp->compartment.faceMap.push_back( face_vec );
	}

	m_compartments.push_back( comp );

	
}

//////////////////////////////////////////////////////////////////

void cMeshImporter::importAsBlueprint( void )
{
	sVehicle vehicle;

	sCompartment root{
		.ID = 0,
		.parentID = -1,
		.flags = 3
	};

	sBlueprint root_bp{
		.id = "Compartment",
		.data = root.serialize().dump(),
		.metaData = ""
	};
	
	vehicle.blueprints.push_back( root_bp.serialize() );

	for ( int i = 0; i < m_compartments.size(); i++ )
	{
		sCompartment& comp = *m_compartments[ i ];
		comp.ID = i + 1;
		comp.flags = 4;
		comp.parentID = 0;
		comp.turret.enabled = true;

		sBlueprint bp{
			.id = "Compartment",
			.data = comp.serialize().dump(),
			.metaData = ""
		};

		vehicle.blueprints.push_back( bp.serialize() );
	}

	// save to file
	std::ofstream file( m_outpath + "\\" + m_filename + ".blueprint");
	file << vehicle.serialize();
}

//////////////////////////////////////////////////////////////////

void cMeshImporter::importAsCompartments( void )
{
	for ( int i = 0; i < m_compartments.size(); i++ )
	{
		sCompartment& comp = *m_compartments[ i ];

		sBlueprint bp{
			.id = "Compartment",
			.data = comp.serialize().dump(),
			.metaData = ""
		};

		// save to file
		std::ofstream file( m_outpath + comp.name + ".blueprint" );
		file << bp.serialize();
	}
}

//////////////////////////////////////////////////////////////////

void cMeshImporter::processAssimpNode( aiNode* _node, const aiScene* _scene )
{
	// process all the node's meshes (if any)
	for ( unsigned int i = 0; i < _node->mNumMeshes; i++ )
	{
		aiMesh* mesh = _scene->mMeshes[ _node->mMeshes[ i ] ];
		m_meshes.push_back( processAssimpMesh( mesh, _scene, _node ) );
	}

	// then do the same for each of its children
	for ( unsigned int i = 0; i < _node->mNumChildren; i++ )
		processAssimpNode( _node->mChildren[ i ], _scene );

}

sMesh* cMeshImporter::processAssimpMesh( aiMesh* _assimp_mesh, const aiScene* _scene, aiNode* _node )
{
	sMesh* mesh = new sMesh();
	mesh->name = _assimp_mesh->mName.C_Str();
	
	aiVector3D pos;
	aiVector3D scale;
	aiVector3D rot;
	_node->mTransformation.Decompose( scale, rot, pos );
	
	mesh->position = { pos.x, pos.y, pos.z };
	mesh->rotation = { rot.x * RAD_DEG_CONST, rot.y * RAD_DEG_CONST, rot.z * RAD_DEG_CONST };
	
	// process vertices
	sVertex v;
	for ( int i = 0; i < _assimp_mesh->mNumVertices; i++ )
	{
		v.x = _assimp_mesh->mVertices[ i ].x * scale.x;
		v.y = _assimp_mesh->mVertices[ i ].y * scale.y;
		v.z = _assimp_mesh->mVertices[ i ].z * scale.z;

		mesh->vertices.push_back( v );
	}
	
	// process indices
	for ( unsigned int i = 0; i < _assimp_mesh->mNumFaces; i++ )
	{
		aiFace face = _assimp_mesh->mFaces[ i ];
		mesh->faces.push_back( {} );

		for ( int j = 0; j < face.mNumIndices; j++ )
			mesh->faces[ i ].indices.push_back( face.mIndices[ j ] );
	}

	return mesh;
}

//////////////////////////////////////////////////////////////////

void cMeshImporter::recalculateSharedPoints( sCompartment* _blueprint, sMesh* _mesh )
{
	std::map<uint32_t, std::vector<int>> hash_space;

	for ( int i = 0; i < _mesh->vertices.size(); i++ )
	{
		sVertexi v{
			(int)( _mesh->vertices[ i ].x * 1000 ),
			(int)( _mesh->vertices[ i ].y * 1000 ),
			(int)( _mesh->vertices[ i ].z * 1000 )
		};
		uint32_t hash;

		MurmurHash3_x86_32( &v, sizeof( int ) * 3, 1, &hash );
		hash_space[ hash ].push_back( i );
	}

	for ( auto& vec : hash_space )
		_blueprint->compartment.sharedPoints.push_back( vec.second );
	
}
