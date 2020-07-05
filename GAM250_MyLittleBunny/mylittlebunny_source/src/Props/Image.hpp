/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      Audio.hpp
Purpose:        Audio prop is the object that contains the data of the texture files we load in
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#pragma once

#include <Props/BaseProp.hpp>
#include <WIP/Texture.hpp>

#include <glm/glm.hpp>

namespace BE
{
namespace Prop
{

    class Image : public BaseProp
    {
    public:
        struct imageData
        {
            inline imageData operator=(imageData a) {
                if (a.texture != nullptr)
                {
                    spriteIndex = a.spriteIndex;
                    texture = a.texture;
                    spriteSize = a.spriteSize;
                }

                posOffest = a.posOffest;
                scaleOffest = a.scaleOffest;
                if (a.color.r != -1)
                {
                    color = a.color;
                }
                rotation = a.rotation;
                return a;
            }

            int spriteIndex;
            Texture* texture;
            glm::vec2 spriteSize;

            glm::vec3 posOffest; // [TEMPORARY] Just for testing purposes
            glm::vec2 scaleOffest; // [TEMPORARY] Just for testing purposes
            glm::vec4 color;
            float rotation;
        };

    public:
        PROP_HASH(Image)   // This macro generates our type hash we absolutely need it (It won't compile anyways if you don't add it)
        Image(std::string fileName_, std::string id_);
        ~Image() = default;

        void    getData(Json::Value& data_)     final;
        void    loadData()                      final;
        void    writeData(Json::Value& data_)   final;
        void    drawData()                      final;

        Texture*    getSprite(size_t id);
        bool        textureIsLoaded();

        std::string             imageFile;   /*!< The file that the image will be loaded from (ex: picture.png). */

    private:
        void    calculateSpriteCoord();

        Texture*                texData;  /*!< The abstraction of the loaded image */
        glm::vec2               spriteDm; /*!< Sprite dimensions */
        std::vector<glm::vec2>  spriteCoord; /*!< List of all sprites in the sprite sheet */
    };

}
}
