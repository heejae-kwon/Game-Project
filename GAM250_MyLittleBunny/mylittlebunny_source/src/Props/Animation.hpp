/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      Animation.hpp
Purpose:        Animation prop is the object that contains all the animation data for the animations in the engine
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#pragma once

#include <Props/BaseProp.hpp>
#include <Props/Image.hpp>
#include <WIP/Texture.hpp>

#include <glm/glm.hpp>

#include <list>

namespace BE
{
    namespace Prop
    {
        class Animation : public BaseProp
        {
        public:
            struct keyFrame
            {
                keyFrame()
                {
                    duration = 0.f;
                    spriteIndex = 0;
                    transform[0] = 0.f;
                    transform[1] = 0.f;
                    transform[2] = 0.f;
                    scale[0] = 0.f;
                    scale[1] = 0.f;
                    color[0] = 1.f;
                    color[1] = 1.f;
                    color[2] = 1.f;
                    color[3] = 1.f;
                    rotation = 0;
                }
                float duration; //time before the next keyframe

                int spriteIndex;
                float transform[3];
                float scale[2];
                float color[4];
                int rotation;
            };

        public:
            PROP_HASH(Animation)   // This macro generates our type hash we absolutely need it (It won't compile anyways if you don't add it)
            Animation(std::string fileName_, std::string id_);
            ~Animation() = default;

            void    getData(Json::Value& data_)     final;
            void    loadData()                      final;
            void    writeData(Json::Value& data_)   final;
            void    drawData()                      final;

            std::pair<std::string, Prop::BaseProp*>*  updateProp(std::string propId_);
            Image::imageData            getFrame(float elapsedTime_, bool loop_);
            Prop::Image*                getTexture();
            void                        setTextureId(std::string propId_);

        private:
            void    updateFullTime();

            bool        spriteOverride;
            bool        colorOverride;
            bool        colorInterpolate;
            bool        transformOverride;
            bool        transformInterpolate;

            std::string                                 textureId;  // The id of the texture we are using
            std::pair<std::string, Prop::BaseProp*>*    texture;    // Pointer to a prop pair that contains a texture
            std::list<keyFrame>                         frameList;
        public:
            float                                       fullTime;
        private:
            bool                                        loop;

        };

    }
}
