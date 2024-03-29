#pragma once

#include <string>
#include <vector>
#include <blueprint/cBlueprint.h>

#include <mesh/sMesh.h>

struct aiNode;
struct aiScene;
struct aiMesh;

enum eMeshImporterFlags
{
	MeshImporterFlags_None              = 0b00000000,
	MeshImporterFlags_MergeCompartments = 0b00000001,
	MeshImporterFlags_ImportAsVehicle = 0b00000010,
};

class cMeshImporter
{

public:
	 cMeshImporter( std::string _path, std::string _out = "./", eMeshImporterFlags _flags = MeshImporterFlags_None );
	~cMeshImporter( void );

//////////////////////////////////////////////////////////////////

private:

	void loadCompartments   ( void );

	void processMeshToCompartment( sMesh* _mesh );

	void importAsBlueprint  ( void );
	void importAsCompartments( void );

	void   processAssimpNode( aiNode* _node, const aiScene* _scene );
	sMesh* processAssimpMesh( aiMesh* _assimp_mesh, const aiScene* _scene, aiNode* _node );

	void recalculateSharedPoints( sCompartment* _blueprint, sMesh* _mesh );

//////////////////////////////////////////////////////////////////

	std::vector<sCompartment*> m_compartments;
	std::vector<sMesh*> m_meshes;
	std::string m_outpath;
	std::string m_filename;

};