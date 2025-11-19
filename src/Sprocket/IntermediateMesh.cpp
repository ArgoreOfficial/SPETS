#include "IntermediateMesh.h"

#include <Sprocket/Error.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <unordered_map>

bool Sprocket::createIntermediateMeshFromFile( const std::filesystem::path& _path, IntermediateMesh& _out )
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile( _path.string(), aiProcess_JoinIdenticalVertices);

	if ( scene == nullptr || scene->mNumMeshes == 0 )
	{
		SPROCKET_PUSH_ERROR( "'{}' : Failed to load model.", _path.string() );
		return false;
	}

	uint32_t indexOffset = 0; // global mesh vertex offset
	uint32_t indexShift = 0; // so we can properly remove duplicate vertices and shift indices down

	IntermediateMesh imMesh{};

	int ngons = 0;
	int orphans = 0;

	for ( size_t meshIndex = 0; meshIndex < scene->mNumMeshes; meshIndex++ )
	{
		aiMesh* mesh = scene->mMeshes[ meshIndex ];

		for ( size_t vertexIndex = 0; vertexIndex < mesh->mNumVertices; vertexIndex++ )
		{
			aiVector3D& vert = mesh->mVertices[ vertexIndex ];
			// X is flipped by default 
			imMesh.vertices.push_back( { -vert.x, vert.y, vert.z } );
		}

		for ( size_t faceIndex = 0; faceIndex < mesh->mNumFaces; faceIndex++ )
		{
			aiFace face = mesh->mFaces[ faceIndex ];
			if ( face.mNumIndices > 4 )
			{
				ngons++;
				continue;
			}
			if ( face.mNumIndices < 3 )
			{
				orphans++;
				continue;
			}

			IntermediateFace imFace{};
			for ( size_t i = 0; i < face.mNumIndices; i++ )
			{
				uint16_t index = indexOffset + face.mIndices[ i ];
				// reverse winding order because x is flipped by default
				imFace.vertices.insert( imFace.vertices.begin(), index );
			}

			imMesh.faces.push_back( imFace );
		}

		indexOffset += mesh->mNumVertices;
	}

	if ( ngons > 0 )
		SPROCKET_PUSH_ERROR( "Skipped {} ngons. Mesh has still imported", ngons );

	if ( orphans > 0 )
		SPROCKET_PUSH_ERROR( "Skipped {} orphan lines or points. Mesh has still imported", orphans );

	_out = imMesh;
	return true;
}

bool Sprocket::createCompartmentFromIntermediateMesh( const IntermediateMesh& _mesh, MeshData& _out )
{
	std::unordered_map< uint16_t, std::vector<uint16_t> > edgeMap{};
	std::unordered_map< uint32_t, uint32_t > indexRemap{};

	MeshData meshData = _out;

	// setup vertices
	for ( size_t i = 0; i < _mesh.vertices.size(); i++ )
	{
		meshData.mesh.vertexPositions.push_back( _mesh.vertices[ i ].x );
		meshData.mesh.vertexPositions.push_back( _mesh.vertices[ i ].y );
		meshData.mesh.vertexPositions.push_back( _mesh.vertices[ i ].z );
	}

	for ( size_t f = 0; f < _mesh.faces.size(); f++ )
	{
		const IntermediateFace& face = _mesh.faces[ f ];
		
		Sprocket::SerializedFace serializedFace{};
		for ( size_t i = 0; i < face.vertices.size(); i++ )
		{
			uint16_t edgeA = face.vertices[ ( i ) % face.vertices.size() ];
			uint16_t edgeB = face.vertices[ ( i + 1 ) % face.vertices.size() ];

			if ( indexRemap.contains( edgeA ) ) edgeA = indexRemap[ edgeA ];
			if ( indexRemap.contains( edgeB ) ) edgeB = indexRemap[ edgeB ];

			serializedFace.vertices.push_back( edgeA );
			serializedFace.thicknesses.push_back( 1.0f );

			if ( edgeMap.count( edgeA ) == 0 )
				edgeMap[ edgeA ].push_back( edgeB );
		}

		meshData.mesh.serializedFaces.push_back( serializedFace );
	}

	for ( auto e : edgeMap )
	{
		for ( size_t i = 0; i < e.second.size(); i++ )
		{
			meshData.mesh.serializedEdges.push_back( e.second[ i ] );
			meshData.mesh.serializedEdges.push_back( e.first );
			meshData.mesh.serializedEdgeFlags.push_back( SerializedEdgeFlags_None );
		}
	}

	_out = meshData;
	return true;
}

void Sprocket::IntermediateMesh::appendIntermediateMesh( const IntermediateMesh& _mesh )
{
	size_t offset = vertices.size();

	if ( _mesh.vertices.size() == 0 || _mesh.faces.size() == 0 )
	{
		SPROCKET_PUSH_ERROR( "IntermediateMesh : Nothing to append." );
		return;
	}

	for ( size_t i = 0; i < _mesh.vertices.size(); i++ )
		vertices.push_back( _mesh.vertices[ i ] );
	
	for ( size_t i = 0; i < _mesh.faces.size(); i++ )
	{
		IntermediateFace f = _mesh.faces[ i ];
		for ( size_t v = 0; v < f.vertices.size(); v++ )
			f.vertices[ i ] += offset;
		faces.push_back( f );
	}
}

}

