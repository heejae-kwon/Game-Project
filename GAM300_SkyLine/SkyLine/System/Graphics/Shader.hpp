#pragma once

#include <string>
#include "glm/glm.hpp"
#include "glad/glad.h"

class Shader
{
  public:
    Shader() = delete;
    Shader(const char * vertex_file_path, const char * fragment_file_path);
    virtual ~Shader();
    GLuint getProgram() { return program_; }

    void use()
    {
      glUseProgram(program_);
    }

    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string &name, bool value) const
    {
      glUniform1i(glGetUniformLocation(program_, name.c_str()), (int)value);
    }
    // ------------------------------------------------------------------------
    void setInt(const std::string &name, int value) const
    {
      glUniform1i(glGetUniformLocation(program_, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void setFloat(const std::string &name, float value) const
    {
      glUniform1f(glGetUniformLocation(program_, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void setVec2(const std::string &name, const glm::vec2 &value) const
    {
      glUniform2fv(glGetUniformLocation(program_, name.c_str()), 1, &value[0]);
    }
    void setVec2(const std::string &name, float x, float y) const
    {
      glUniform2f(glGetUniformLocation(program_, name.c_str()), x, y);
    }
    // ------------------------------------------------------------------------
    void setVec3(const std::string &name, const glm::vec3 &value) const
    {
      glUniform3fv(glGetUniformLocation(program_, name.c_str()), 1, &value[0]);
    }
    void setVec3(const std::string &name, float x, float y, float z) const
    {
      glUniform3f(glGetUniformLocation(program_, name.c_str()), x, y, z);
    }
    // ------------------------------------------------------------------------
    void setVec4(const std::string &name, const glm::vec4 &value) const
    {
      glUniform4fv(glGetUniformLocation(program_, name.c_str()), 1, &value[0]);
    }
    void setVec4(const std::string &name, float x, float y, float z, float w)
    {
      glUniform4f(glGetUniformLocation(program_, name.c_str()), x, y, z, w);
    }
    // ------------------------------------------------------------------------
    void setMat2(const std::string &name, const glm::mat2 &mat) const
    {
      glUniformMatrix2fv(glGetUniformLocation(program_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat3(const std::string &name, const glm::mat3 &mat) const
    {
      glUniformMatrix3fv(glGetUniformLocation(program_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat4(const std::string &name, const glm::mat4 &mat) const
    {
      glUniformMatrix4fv(glGetUniformLocation(program_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void setMat4Projection(const glm::mat4 &mat) { glUniformMatrix4fv(uni_loc_projection_, 1, GL_FALSE, &mat[0][0]); }

    void setMat4View(const glm::mat4 &mat) { glUniformMatrix4fv(uni_loc_view_, 1, GL_FALSE, &mat[0][0]); }

    void setMat4Model(const glm::mat4 &mat) { glUniformMatrix4fv(uni_loc_model_, 1, GL_FALSE, &mat[0][0]); }

  protected:
    GLuint program_;
    bool loadFailed = false;

  private:
    GLuint uni_loc_projection_ = 0;
    GLuint uni_loc_view_ = 1;
    GLuint uni_loc_model_ = 2;
};