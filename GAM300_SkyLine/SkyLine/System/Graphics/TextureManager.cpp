#include "TextureManager.h"
#include "glad/glad.h"
#include <iostream>
#include <SOIL2/SOIL2.h>

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager() 
{
}

void TextureManager::initializeTextures(std::vector<std::string>& fileNames)
{
  for (auto const & fileName : fileNames)
  {
    loadTextureFromFile(fileName, false);
  }
}

bool TextureManager::loadTextureFromFile(const std::string& filePath, bool /*gamma*/)
{
  unsigned int textureID;
  glGenTextures(1, &textureID);

  int width, height;// , nrComponents;
  unsigned char *data = SOIL_load_image(filePath.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
  if (data)
  {

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SOIL_free_image_data(data);
    glBindTexture(GL_TEXTURE_2D, 0);
  }
  else
  {
    std::cout << "Texture failed to load at path: " << filePath << std::endl;
    return false;
  }

  std::string directory = filePath.substr(0, filePath.find_last_of('/'));
  std::string name = filePath.substr(filePath.find_last_of('/') + 1, filePath.find_last_of('.') - filePath.find_last_of('/') - 1);
  //std::string directory = filename.substr(0, filename.find_last_of('/'));

  textures_.emplace(name, std::make_shared<Texture>(textureID, TextureType::REGULAR, directory));

  return true;
}

bool TextureManager::loadCubemap(std::vector<std::string>& faces, const char* name)
{
  unsigned int textureID;
  glGenTextures(1, &textureID);
  //glActiveTexture(GL_TEXTURE0 + slot);
  glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

  int width, height, nrComponents;
  for (unsigned int i = 0; i < faces.size(); i++)
  {
    unsigned char *data = SOIL_load_image(faces[i].c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      SOIL_free_image_data(data);
    }
    else
    {
      std::cout << "Cubemap texture failed to load at path: " << std::endl;
      SOIL_free_image_data(data);
      glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
      return false;
    }
  }

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
  glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

  std::string directory = faces[0].substr(0, faces[0].find_last_of('/'));

  cubeMaps_.emplace(name, std::make_shared<Texture>(textureID, TextureType::CUBEMAP, directory));

  return true;
}