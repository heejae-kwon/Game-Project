/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      Camera.hpp
Purpose:        Camera component, any actor with this component will be used as a camera
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#pragma once

#include <Components/BaseComponent.hpp>

#include <json\json.h>

namespace BE
{
namespace Component
{

    class Camera : public BaseComponent
    {
    public:
        COMPONENT_HASH(Camera)
            Camera(Actor* owner_);
        ~Camera();

        void    getData(Json::Value& data_)     final;
        void    writeData(Json::Value& data_)   final;
        void    drawData()                      final;

        float  zoom;
    };

}
}
