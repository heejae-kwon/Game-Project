#include "Model.hpp"
#include <iostream>
#include "glad/glad.h"
#include <SOIL2/SOIL2.h>

// TO DO: Textures

/*  Functions   */
// constructor, expects a filepath to a 3D model.
Model::Model(std::string const &path, bool gamma)
  : gammaCorrection(gamma)
{
  loadModel(path);
}

// loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
void Model::loadModel(std::string const &path)
{
  // read file via ASSIMP
  Assimp::Importer importer;
  const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
  // check for errors
  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
  {
    std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
    return;
  }

  // get name of the model itself
  name_ = path.substr(path.find_last_of('/') + 1, path.find_last_of('.') - path.find_last_of('/') - 1);

  // retrieve the directory path of the filepath
  directory_ = path.substr(0, path.find_last_of('/'));

  // process ASSIMP's root node recursively
  processNode(scene->mRootNode, scene);

}

// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
void Model::processNode(aiNode *node, const aiScene *scene)
{
  // process each mesh located at the current node
  for (unsigned int i = 0; i < node->mNumMeshes; i++)
  {
    // the node object only contains indices to index the actual objects in the scene. 
    // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
    aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
    meshes_.push_back(processMesh(mesh, scene));
    std::string temp = mesh->mName.C_Str();
    if (temp != "")
    {
      std::cout << "d" << std::endl;
    }
  }
  // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
  for (unsigned int i = 0; i < node->mNumChildren; i++)
  {
    processNode(node->mChildren[i], scene);
  }

}


Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
  // data to fill
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<Texture> textures;



  // Walk through each of the mesh's vertices
  for (unsigned int i = 0; i < mesh->mNumVertices; i++)
  {
    Vertex vertex;
    glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
                      // positions
    vector.x = mesh->mVertices[i].x;
    vector.y = mesh->mVertices[i].y;
    vector.z = mesh->mVertices[i].z;
    vertex.position = vector;

    // normals
    if (mesh->mNormals)
    {
      vector.x = mesh->mNormals[i].x;
      vector.y = mesh->mNormals[i].y;
      vector.z = mesh->mNormals[i].z;
      vertex.normal = vector;
    }
    else
    {
      vertex.normal = glm::vec3(0.0f, 0.0f, 0.0f);
    }
    // texture coordinates
    if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
    {
      glm::vec2 vec;
      // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
      // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
      vec.x = mesh->mTextureCoords[0][i].x;
      vec.y = mesh->mTextureCoords[0][i].y;
      vertex.texCoords = vec;
    }
    else
      vertex.texCoords = glm::vec2(0.0f, 0.0f);
    // tangent
    /*
    if (mesh->mTangents)
    {
      vector.x = mesh->mTangents[i].x;
      vector.y = mesh->mTangents[i].y;
      vector.z = mesh->mTangents[i].z;
      vertex.Tangent = vector;
    }*/
    // bitangent
    /*
    if (mesh->mBitangents)
    {
      vector.x = mesh->mBitangents[i].x;
      vector.y = mesh->mBitangents[i].y;
      vector.z = mesh->mBitangents[i].z;
      vertex.Bitangent = vector;
    }
    */
    vertices.push_back(vertex);
  }
  // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
  for (unsigned int i = 0; i < mesh->mNumFaces; i++)
  {
    aiFace face = mesh->mFaces[i];
    // retrieve all indices of the face and store them in the indices vector
    for (unsigned int j = 0; j < face.mNumIndices; j++)
      indices.push_back(face.mIndices[j]);
  }
  // process materials
  aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		material;
  // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
  // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
  // Same applies to other texture as the following list summarizes:
  // diffuse: texture_diffuseN
  // specular: texture_specularN
  // normal: texture_normalN

  //std::vector<ModelMesh::ModelTexture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

  // 1. diffuse maps
  /*
  std::vector<ModelMesh::ModelTexture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
  textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
  // 2. specular maps
  std::vector<ModelMesh::ModelTexture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
  textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
  // 3. normal maps
  std::vector<ModelMesh::ModelTexture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
  textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
  // 4. height maps
  std::vector<ModelMesh::ModelTexture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
  textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
  */
  // return a mesh object created from the extracted mesh data
  return Mesh(vertices, indices, textures);
}

// checks all material textures of a given type and loads the textures if they're not loaded yet.
// the required info is returned as a Texture struct.
/*
std::vector<ModelMesh::ModelTexture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
{
  std::vector<ModelMesh::ModelTexture> textures;
  for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
  {
    aiString str;
    mat->GetTexture(type, i, &str);
    // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
    bool skip = false;
    for (unsigned int j = 0; j < textures_loaded.size(); j++)
    {
      if (std::strcmp(textures_loaded[j].path.C_Str(), str.C_Str()) == 0)
      {
        textures.push_back(textures_loaded[j]);
        skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
        break;
      }
    }
    if (!skip)
    {   // if texture hasn't been loaded already, load it
      ModelMesh::ModelTexture texture;
      texture.id = TextureFromFile(str.C_Str(), this->directory);
      texture.type = typeName;
      texture.path = str;
      textures.push_back(texture);
      textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
    }
  }
  return textures;
}
*/

unsigned int TextureFromFile(const char *path, const std::string &directory, bool /*gamma*/)
{
  std::string filename = std::string(path);
  filename = directory + '/' + filename;

  unsigned int textureID;
  glGenTextures(1, &textureID);

  int width, height;// , nrComponents;
  unsigned char *data = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
  if (data)
  {

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //stbi_image_free(data);
    SOIL_free_image_data(data);
    glBindTexture(GL_TEXTURE_2D, 0);
  }
  else
  {
    std::cout << "Texture failed to load at path: " << path << std::endl;
  }

  return textureID;
}

Model::~Model()
{
}


void Model::bindMeshes()
{
  for (auto& mesh : meshes_)
  {
    mesh.bindMesh();
  }
}