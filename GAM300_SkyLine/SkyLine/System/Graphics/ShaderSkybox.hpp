#pragma once
#include "Shader.hpp"

class ShaderSkybox : public Shader {
  public:
    ShaderSkybox(const char * vertex_file_path, const char * fragment_file_path) : Shader::Shader(vertex_file_path, fragment_file_path)
    { }

    void setTextureUnit(int value) const
    {
      glUniform1i(uni_loc_sampleCube_, value);
    }

  private:
    GLuint uni_loc_sampleCube_ = 3;
};