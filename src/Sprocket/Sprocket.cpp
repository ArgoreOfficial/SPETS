#include "Sprocket.h"
#include "Json.h"

#include <nlohmann/json.hpp>

#include <fstream>
#include <unordered_map>

#include <windows.h>
#include <shlobj.h>
#include <filesystem>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#pragma comment(lib, "shell32.lib")

bool Sprocket::loadCompartmentFromFile( const std::string& _path, MeshData& _out )
{
	std::ifstream f( _path );
	if ( !f.is_open() )
		return false;

	nlohmann::json json = nlohmann::json::parse( f );
	f.close(); // immediately close file

	if ( json[ "v" ] == "2.0" )
	{
		printf( "Vehicle Blueprint, NOT IMPLEMENTED YET" );
		return false;
	}
	
	_out = json.get<Sprocket::MeshData>();
	
	return true;
}

bool Sprocket::saveCompartmentToFile( const std::string& _path, const MeshData& _compartment )
{
	std::ofstream f( _path );
	if ( !f.is_open() )
		return false;

	nlohmann::json json = _compartment;
	f << json.dump();
	f.close();

    return true;
}

bool Sprocket::importMesh( const std::string& _path, MeshData& _outMesh )
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile( _path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if ( scene == nullptr )
		return false;
	
	if ( scene->mNumMeshes == 0 )
		return false;

	std::unordered_map< uint16_t, uint16_t > edgeMap{};
	uint32_t indexOffset = 0;
	MeshData meshData{ };
	meshData.name = scene->mName.C_Str();

	for ( size_t meshIndex = 0; meshIndex < scene->mNumMeshes; meshIndex++ )
	{
		aiMesh* mesh = scene->mMeshes[ meshIndex ];
		
		// setup vertices
		for ( size_t vertexIndex = 0; vertexIndex < mesh->mNumVertices; vertexIndex++ )
		{
			aiVector3D vert = mesh->mVertices[ vertexIndex ];
			meshData.mesh.vertexPositions.push_back( vert.x );
			meshData.mesh.vertexPositions.push_back( vert.y );
			meshData.mesh.vertexPositions.push_back( vert.z );
		}

		for ( size_t faceIndex = 0; faceIndex < mesh->mNumFaces; faceIndex++ )
		{
			aiFace face = mesh->mFaces[ faceIndex ];
			if ( face.mNumIndices != 3 && face.mNumIndices != 4 )
				continue;

			Sprocket::SerializedFace serializedFace{};
			for ( size_t i = 0; i < face.mNumIndices; i++ )
			{
				uint16_t edgeA = indexOffset + face.mIndices[ i ];
				uint16_t edgeB = indexOffset + face.mIndices[ (i + 1) % face.mNumIndices ];

				serializedFace.vertices.push_back( edgeA );
				serializedFace.thicknesses.push_back( 1.0f );

				if ( edgeMap.count( edgeA ) == 0 )
					edgeMap[ edgeA ] = edgeB;
			}
			meshData.mesh.serializedFaces.push_back( serializedFace );
		}

		//printf( "Parsed %s vertices\n", mesh->mName.C_Str() );
		indexOffset += mesh->mNumVertices;
	}

	for ( auto e : edgeMap )
	{
		meshData.mesh.serializedEdges.push_back( e.first );
		meshData.mesh.serializedEdges.push_back( e.second );
		meshData.mesh.serializedEdgeFlags.push_back( SerializedEdgeFlags_None );
	}

	//printf( "Constructed edge map\n" );

	_outMesh = meshData;
	return true;
}

bool Sprocket::doesFactionExist( const std::string& _name )
{
	return std::filesystem::is_directory( getFactionPath( _name ) );
}

std::string Sprocket::getFactionPath( const std::string& _name )
{
	CHAR myDocumentsStr[ MAX_PATH ];
	HRESULT result = SHGetFolderPath( NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, myDocumentsStr );

	if ( result != S_OK )
		return "";

	return std::string{ myDocumentsStr } + "\\My Games\\Sprocket\\Factions\\" + _name + "\\";
}
