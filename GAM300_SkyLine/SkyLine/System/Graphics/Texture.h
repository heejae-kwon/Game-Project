#pragma once
#include <string>

enum TextureType {
  REGULAR = 0,
  CUBEMAP
};

class Texture {
public:
  Texture() {}
  Texture(unsigned int id, TextureType type, std::string directory) : id_(id), type_(type), directory_(directory)
  {}

  ~Texture() {}

  const unsigned int getID() const { return id_; }
  const TextureType getType() const { return type_; }
  const std::string& getDirectory() const { return directory_; }

private:
  unsigned int id_;
  TextureType type_;
  std::string directory_;
};