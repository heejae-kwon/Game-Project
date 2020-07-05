/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      CircleCollider.cpp
Purpose:        CircleCollider component, used in the Physics core
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#include <Components/CircleCollider.hpp>
#include <Core/Debugger.hpp>
#include <Utilities/JsonReader.hh>
#include <Utilities/JsonWriter.hh>
BE::Component::CircleCollider::CircleCollider(Actor * owner_)
    : BaseComponent(identifier), radius(1.f), ghost(false)
{
    type = Type::CIRCLE_COLLIDER;
    owner = owner_;
}

BE::Component::CircleCollider::~CircleCollider()
{
}

void
BE::Component::CircleCollider::getData(Json::Value & data_)
{
    std::string componentField = BE::Component::TypeStr[BE::Component::CIRCLE_COLLIDER];
    Json::Value componentData = data_["Actors"][owner->_name][componentField];

    radius = JsonReader::getFieldAsFloat(componentData["radius"]);
    ghost = JsonReader::getFieldAsBool(componentData["ghost"]);
}

void
BE::Component::CircleCollider::writeData(Json::Value & data_)
{
    std::string componentField = BE::Component::TypeStr[BE::Component::CIRCLE_COLLIDER];

    JsonWriter::addValue(data_["Actors"][owner->_name][componentField]["radius"], radius);
    JsonWriter::addValue(data_["Actors"][owner->_name][componentField]["ghost"], ghost);
}

void
BE::Component::CircleCollider::drawData()
{
    if (ImGui::CollapsingHeader("CircleCollider Component"))
    {
        ImGui::InputFloat("Radius", &radius, 1.f, 10.f);
        ImGui::Checkbox("Ghost", &ghost);
    }
}

void BE::Component::CircleCollider::updateCollision(CircleCollider * collider, bool newState_)
{
    for (size_t i = 0; i < collisionVec.size(); ++i)
    {
        if (collisionVec[i].collider == collider)
        {
            collisionVec[i].oldState = collisionVec[i].newState;
            collisionVec[i].newState = newState_;

            if (collisionVec[i].oldState == false && collisionVec[i].newState == false)
            {
                std::swap(collisionVec[i], collisionVec.back());
                collisionVec.pop_back();
            }
            return;
        }
    }
    if (newState_ == false)
        return;
    collision newCollision = {};
    newCollision.collider = collider;
    newCollision.oldState = false;
    newCollision.newState = newState_;
    collisionVec.push_back(newCollision);
}
