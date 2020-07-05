/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      Shader.hpp
Language:       C++
Project:        GAM250
Author:         Name : Wonjae Jung
Email:          wonjae0925@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/
#pragma once

#include <string>

#include <GL/gl3w.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace BE
{
// General purpsoe shader object. Compiles from file, generates
// compile/link-time error messages and hosts several utility 
// functions for easy management.
class Shader
{
public:
    // State
    GLuint ID;
    // Constructor
    Shader() { }

    void    LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
    Shader& Use();
    // Compiles the shader from given source code
    void    Compile(const GLchar *vertexSource, const GLchar *fragmentSource, const GLchar *geometrySource = nullptr); // Note: geometry source code is optional 
                                                                                                                       // Utility functions
    void    SetFloat(const GLchar *name, GLfloat value, GLboolean useShader = false);
    void    SetInteger(const GLchar *name, GLint value, GLboolean useShader = false);
    void    SetVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
    void    SetVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader = false);
    void    SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
    void    SetVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader = false);
    void    SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
    void    SetVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader = false);
    void    SetMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);
private:
    // Checks if compilation or linking failed and if so, print the error logs
    void    checkCompileErrors(GLuint object, std::string type);
};
}
