/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      Camera.cpp
Purpose:        Camera component, any actor with this component will be used as a camera
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski, Wonjae Jung
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#pragma once

#include <Components/Camera.hpp>
#include <Core/Draw.hpp>
#include <Core/Debugger.hpp>
#include <Utilities/JsonReader.hh>
#include <Utilities/JsonWriter.hh>

BE::Component::Camera::Camera(Actor* owner_)
    : BaseComponent(identifier), zoom(1.f)
{
    type = Type::CAMERA;
    owner = owner_;
    Core::Draw::instance()->addCamera(owner);
}

BE::Component::Camera::~Camera()
{
    Core::Draw::instance()->removeCurrentCamera();
}

void
BE::Component::Camera::getData(Json::Value& data_)
{
    std::string componentField = BE::Component::TypeStr[BE::Component::CAMERA];
    Json::Value componentData = data_["Actors"][owner->_name][componentField];

    zoom = JsonReader::getFieldAsFloat(componentData["zoom"]);
}

void
BE::Component::Camera::writeData(Json::Value& data_)
{
    std::string componentField = BE::Component::TypeStr[BE::Component::CAMERA];

    JsonWriter::addValue(data_["Actors"][owner->_name][componentField]["zoom"], zoom);
}

void
BE::Component::Camera::drawData()
{
    if (ImGui::CollapsingHeader("Camera Component"))
    {
        ImGui::PushItemWidth(160);
        {
            ImGui::InputFloat("Zoom", &zoom, 0.1f, 0.5f);
        }
        ImGui::PopItemWidth();
    }
}
