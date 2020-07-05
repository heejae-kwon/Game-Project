#pragma once

#include <vector>
#include <string>
#include "Mesh.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

class Model
{
public:
  // Construct a Model by giving it a filepath to the model file
  Model(std::string const &path, bool gamma = false);

  // Destructor
  ~Model();

  // Call the requisite OpenGL functions for these meshes
  void bindMeshes();

  // Return the mesh
  const vector<Mesh>& getMeshes() const { return meshes_; }

  // Get the name of the model
  const std::string& getName() const { return name_; };

  /*  Model Data */
  //std::vector<Mesh::ModelTexture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
  std::vector<Mesh> meshes_;
  std::string directory_;
  std::string name_;
  bool gammaCorrection;
private:
  // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
  void loadModel(std::string const &path);

  // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
  void processNode(aiNode *node, const aiScene *scene);

  Mesh processMesh(aiMesh *mesh, const aiScene *scene);

  //std::vector<ModelMesh::ModelTexture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};