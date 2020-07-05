/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      Texture.hpp
Language:       C++
Project:        GAM250
Author:         Name : Wonjae Jung
Email:          wonjae0925@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/
#pragma once

#include <GL/gl3w.h>
#include <glm/glm.hpp>

#include <vector>

namespace BE
{
    class Texture
    {
    public:
        // Holds the ID of the texture object, used for all texture operations to reference to this particlar texture
        GLuint ID;
        
        // Texture image dimensions
        glm::ivec2  size;           // Width and height of loaded image in pixels
        glm::vec2   spriteSize;     // Size of sprite to be displayed
        glm::vec2   spriteCoord;    // Position of sprite to be dislayed

        // Texture Format
        unsigned int Internal_Format; // Format of texture object
        unsigned int Image_Format; // Format of loaded image
                                   // Texture configuration
        unsigned int Wrap_S; // Wrapping mode on S axis
        unsigned int Wrap_T; // Wrapping mode on T axis
        unsigned int Filter_Min; // Filtering mode if texture pixels < screen pixels
        unsigned int Filter_Max; // Filtering mode if texture pixels > screen pixels
                                 // Constructor (sets default texture modes)
        Texture();
        // Generates texture from image data
        void Generate(unsigned int width, unsigned int height, unsigned char* data);
        // Binds the texture as the current active GL_TEXTURE_2D texture object
        void Bind() const;
        glm::vec2 getSize();
    };
}
