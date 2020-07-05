#pragma once
#include "Texture.h"
#include <memory>
#include <string>
#include <map>
#include <vector>

class TextureManager {
public:
  TextureManager();

  ~TextureManager();

  void initializeTextures(std::vector<std::string>& filePaths);

  // Load a regular texture from a filepath
  bool loadTextureFromFile(const std::string& filePath, bool gamma);

  //Load a cubemap texture
  // faces : a vector of 6 filepaths to the faces
  // name : the name of the FOLDER of the skybox (example: /exampleskybox/)
  bool loadCubemap(std::vector<std::string>& faces, const char* name);

  std::shared_ptr<Texture> getTexture(const char* textureName) const { return textures_.at(textureName); }
  std::shared_ptr<Texture> getCubeMapTexture(const char* cubeMapTextureName) const { return cubeMaps_.at(cubeMapTextureName); }

  private:
    std::map<std::string, std::shared_ptr<Texture> > textures_;
    std::map<std::string, std::shared_ptr<Texture> > cubeMaps_;
};