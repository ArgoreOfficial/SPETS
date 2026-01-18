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
		SPROCKET_PUSH_ERROR( "'{}' : Failed to load model.", _path.string().c_str() );
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

void Sprocket::IntermediateMesh::mergeDuplicateVertices()
{
	// create remap
	std::unordered_map<uint16_t, uint16_t> remap;
	for ( size_t index = 0; index < vertices.size(); index++ )
	{
		for ( size_t otherIndex = 0; otherIndex < index; otherIndex++ )
		{
			if ( index == otherIndex ) 
				continue;

			IntermediateVertex v = vertices[ index ] - vertices[ otherIndex ];
			if ( v.length() > 0 )
				continue;

			if ( !remap.contains( index ) )
				remap[ index ] = otherIndex;
		}
	}

	// replace indices
	for ( size_t i = 0; i < faces.size(); i++ )
	{
		for ( size_t v = 0; v < faces[ i ].vertices.size(); v++ )
		{
			uint16_t vindex = faces[ i ].vertices[ v ];
			if ( remap.contains( vindex ) )
				faces[ i ].vertices[ v ] = remap[ vindex ];
		}
	}

	// reconstruct mesh
	std::vector<IntermediateFace> newFaces;
	std::vector<IntermediateVertex> newVertices;
	std::unordered_map<uint16_t, uint16_t> remap2;

	for ( size_t i = 0; i < faces.size(); i++ )
	{
		IntermediateFace face = faces[ i ];
		
		for ( size_t v = 0; v < face.vertices.size(); v++ )
		{
			uint16_t oldIndex = face.vertices[ v ];

			if ( remap2.contains( face.vertices[ v ] ) )
				face.vertices[ v ] = remap2[ oldIndex ];
			else
			{
				uint16_t newIndex = newVertices.size();
				remap2[ oldIndex ] = newIndex;
				face.vertices[ v ] = newIndex;

				newVertices.push_back( vertices[ oldIndex ] );
			}
		}

		newFaces.push_back( face );
	}

	vertices = newVertices;
	faces = newFaces;
}

void Sprocket::IntermediateMesh::reverseWindingOrder()
{
	for ( size_t i = 0; i < faces.size(); i++ )
	{
		IntermediateFace f{};
		for( size_t v = faces[ i ].vertices.size(); v --> 0; )
			f.vertices.push_back( faces[ i ].vertices[ v ] );
		faces[ i ] = f;
	}
}

bool Sprocket::IntermediateMesh::createCompartment( MeshData& _out )
{
	std::unordered_map< uint16_t, std::vector<uint16_t> > edgeMap{};
	std::unordered_map< uint32_t, uint32_t > indexRemap{};

	MeshData meshData = _out;

	// setup vertices
	for ( size_t i = 0; i < vertices.size(); i++ )
	{
		meshData.mesh.vertexPositions.push_back( vertices[ i ].x );
		meshData.mesh.vertexPositions.push_back( vertices[ i ].y );
		meshData.mesh.vertexPositions.push_back( vertices[ i ].z );
	}

	for ( size_t f = 0; f < faces.size(); f++ )
	{
		const IntermediateFace& face = faces[ f ];

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

