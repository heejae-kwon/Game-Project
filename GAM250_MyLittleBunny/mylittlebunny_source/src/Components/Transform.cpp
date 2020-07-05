/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      Transform.cpp
Purpose:        Transform component that is required for every actor as it used by most cores
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#include <Components/Transform.hpp>
#include <Core/Debugger.hpp>
#include <Utilities/JsonReader.hh>
#include <Utilities/JsonWriter.hh>

#include <imgui\imgui.h>

BE::Component::Transform::Transform(Actor* owner_)
    : BaseComponent(identifier), position{ 0.f }, size{ 0.f }, scale{ 1.f }, rotation(0)
{
    type = Type::TRANSFORM;
    owner = owner_;
    Core::Debugger::instance()->registerActor(owner); // For the entity logger
}

BE::Component::Transform::~Transform()
{
    Core::Debugger::instance()->unregisterActor(owner); // For the entity logger
}

void
BE::Component::Transform::getData(Json::Value& data_)
{
    std::string componentField = BE::Component::TypeStr[BE::Component::TRANSFORM];
    Json::Value componentData = data_["Actors"][owner->_name][componentField];

    position = BE::JsonReader::getFieldAsVec3(componentData["position"]);
    size = BE::JsonReader::getFieldAsVec2(componentData["size"]);
    scale = BE::JsonReader::getFieldAsVec2(componentData["scale"]);
    rotation = BE::JsonReader::getFieldAsFloat(componentData["rotation"]);
}

void
BE::Component::Transform::writeData(Json::Value& data_)
{
    std::string componentField = BE::Component::TypeStr[BE::Component::TRANSFORM];

    std::vector<float> posArray = { position.x, position.y, position.z };
    BE::JsonWriter::addFloatArray(data_["Actors"][owner->_name][componentField]["position"], posArray);

    std::vector<float> sizeArray = { size.x, size.y };
    BE::JsonWriter::addFloatArray(data_["Actors"][owner->_name][componentField]["size"], sizeArray);

    std::vector<float> scaleArray = { scale.x, scale.y };
    BE::JsonWriter::addFloatArray(data_["Actors"][owner->_name][componentField]["scale"], scaleArray);

    BE::JsonWriter::addValue(data_["Actors"][owner->_name][componentField]["rotation"], rotation);
}

void
BE::Component::Transform::drawData()
{
    if (ImGui::CollapsingHeader("Transform Component"))
    {
        ImGui::PushItemWidth(160);
        {
            ImGui::InputFloat("Position X", &position.x, 1.f, 10.f, 2);
            ImGui::InputFloat("Position Y", &position.y, 1.f, 10.f, 2);
            if (ImGui::InputFloat("Position Z", &position.z, 1.f, 10.f, 2))
            {
                Core::Draw::instance()->updateSort();
            }
            ImGui::InputFloat("Size pxWidth", &size.x, 0.5f, 2.0f, 2);
            ImGui::InputFloat("Size pxHeight", &size.y, 0.5f, 2.0f, 2);
            ImGui::InputFloat("Scale X", &scale.x, 0.05f, 0.2f, 2);
            ImGui::InputFloat("Scale Y", &scale.y, 0.05f, 0.2f, 2);
            ImGui::InputFloat("Rotation", &rotation, 1, 5, 2);
        }
        ImGui::PopItemWidth();
    }
}
