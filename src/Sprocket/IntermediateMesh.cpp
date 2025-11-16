#include "IntermediateMesh.h"

#include <Sprocket/Error.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

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
			if ( face.mNumIndices != 3 && face.mNumIndices != 4 )
			{
				ngons++;
				continue;
			}

			IntermediateFace imFace{};
			for ( size_t i = 0; i < face.mNumIndices; i++ )
			{
				uint16_t index = indexOffset + face.mIndices[ i ];
				imFace.vertices.insert( imFace.vertices.begin(), index );
			}

			imMesh.faces.push_back( imFace );
		}

		indexOffset += mesh->mNumVertices;
	}

	if ( ngons > 0 )
		SPROCKET_PUSH_ERROR( "{} ngons encountered.", ngons );

	_out = imMesh;
	return true;
}

bool Sprocket::IntermediateMesh::appendIntermediateMesh( const IntermediateMesh& _mesh )
{
	size_t offset = vertices.size();

	if ( _mesh.vertices.size() == 0 || _mesh.faces.size() == 0 )
	{
		SPROCKET_PUSH_ERROR( "IntermediateMesh : Nothing to append." );
		return false;
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

	return true;
}
