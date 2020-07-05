/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      Transform.hpp
Purpose:        Transform component that is required for every actor as it used by most cores
Language:       C++
Project:        GAM200
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#pragma once

#include <Components/BaseComponent.hpp>

#include <glm\glm.hpp>
#include <json\json.h>


namespace BE
{
namespace Component
{

    class Transform : public BaseComponent
    {
    public:
        COMPONENT_HASH(Transform)   // This macro generates our type hash we absolutely need it (It won't compile anyways if you don't add it)
        Transform(Actor* owner_);
        ~Transform();

        void    getData(Json::Value& data_)     final;
        void    writeData(Json::Value& data_)   final;
        void    drawData()                      final;

        // Saved data
        glm::vec3   position;   // position of the actor
        glm::vec2   size;       // size in pixel
        glm::vec2   scale;      // a multiplier of size
        float       rotation;   // the rotation of the actor
    };

}
}
