/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      Texture.cpp
Language:       C++
Project:        GAM250
Author:         Name : Wonjae Jung
Email:          wonjae0925@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/
#include <iostream>

#include "Texture.hpp"


BE::Texture::Texture()
    : size(0, 0), spriteSize(1., 1.f), spriteCoord(0.f, 0.f), Internal_Format(GL_RGB), Image_Format(GL_RGB), Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT), Filter_Min(GL_LINEAR), Filter_Max(GL_LINEAR)
{
    glGenTextures(1, &this->ID);
}

void
BE::Texture::Generate(unsigned int width, unsigned int height, unsigned char* data)
{
    size.x = width;
    size.y = height;
    // Create Texture
    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, width, height, 0, this->Image_Format, GL_UNSIGNED_BYTE, data);
    // Set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);
    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void
BE::Texture::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->ID);
}

glm::vec2
BE::Texture::getSize()
{
    return (glm::vec2(static_cast<float>(size.x) * spriteSize.x, static_cast<float>(size.y) * spriteSize.y));
}
