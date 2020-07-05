#pragma once
#include "Shader.hpp"

class ShaderOcean : public Shader {
public:
  ShaderOcean(const char * vertex_file_path, const char * fragment_file_path) : Shader::Shader(vertex_file_path, fragment_file_path)
  { }

};