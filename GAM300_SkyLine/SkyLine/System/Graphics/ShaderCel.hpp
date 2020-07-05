#pragma once
#include "Shader.hpp"

class ShaderCel : public Shader {
public:
  ShaderCel(const char * vertex_file_path, const char * fragment_file_path) : Shader::Shader(vertex_file_path, fragment_file_path)
  {
    uni_loc_light_position_ = glGetUniformLocation(program_, "Light.position");
    uni_loc_light_intensity_ = glGetUniformLocation(program_, "Light.intensity");
    uni_loc_diffuse_ = glGetUniformLocation(program_, "Kd");
    uni_loc_ambient_ = glGetUniformLocation(program_, "Ka");
    uni_loc_textureSampler_ = glGetUniformLocation(program_, "texture1");
    uni_loc_bool_textured_ = glGetUniformLocation(program_, "textured");
  }

  void setLightPosition(glm::vec4& position) const
  {
    glUniform4f(uni_loc_light_position_, position.x, position.y, position.z, position.w);
  }

  void setLightIntensity(glm::vec3& intensity) const
  {
    glUniform3f(uni_loc_light_intensity_, intensity.x, intensity.y, intensity.z);
  }

  void setDiffuse(glm::vec3& diffuse) const
  {
    glUniform3f(uni_loc_diffuse_, diffuse.x, diffuse.y, diffuse.z);
  }

  void setAmbient(glm::vec3& ambient) const
  {
    glUniform3f(uni_loc_ambient_, ambient.x, ambient.y, ambient.z);
  }

  void setTextureUnit(int value) const
  {
    glUniform1i(uni_loc_textureSampler_, value);
  }

  void setBoolTextured(bool value) const
  {
    glUniform1i(uni_loc_bool_textured_, value);
  }

private:
  GLuint uni_loc_light_position_;
  GLuint uni_loc_light_intensity_;
  GLuint uni_loc_diffuse_;
  GLuint uni_loc_ambient_;
  GLuint uni_loc_textureSampler_;
  GLuint uni_loc_bool_textured_;
};