/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      Rigidbody.cpp
Language:      C++
Project:         GAM250
Author:         Name : HeeJae Kwon
Email:            sfhy33@gmail.com
Creation date:   2017.06.16
----------------------------------------------------------------------------*/
#include <Components/Rigidbody.hpp>
#include <WIP/Physics.hpp>
#include <Core/Debugger.hpp>
#include <Utilities/JsonReader.hh>
#include <Utilities/JsonWriter.hh>

BE::Component::Rigidbody::Rigidbody(Actor* owner_)
    : BaseComponent(identifier),
    restitution(0),
    friction_static(0),
    friction_dynamic(0),
    vel(0),
    rotvel(0),
    force(0),
    torque(0),
    inertia(0),
    mass(0),
    gravityscale(0),
    gravity(0),
    staticstate(false)
{
    type = Type::RIGIDBODY;
    owner = owner_;
    Core::Physics::instance()->registerActor(owner);
}

BE::Component::Rigidbody::~Rigidbody()
{
    Core::Physics::instance()->unregisterActor(owner);
}

void
BE::Component::Rigidbody::getData(Json::Value & data_)
{
    std::string componentField = BE::Component::TypeStr[BE::Component::RIGIDBODY];
    Json::Value componentData = data_["Actors"][owner->_name][componentField];

    restitution = JsonReader::getFieldAsFloat(componentData["restitution"]);
    friction_static = JsonReader::getFieldAsFloat(componentData["friction_static"]);
    friction_dynamic = JsonReader::getFieldAsFloat(componentData["friction_dynamic"]);

    vel.x = JsonReader::getFieldAsFloat(componentData["vel_x"]);
    vel.y = JsonReader::getFieldAsFloat(componentData["vel_y"]);

    rotvel = JsonReader::getFieldAsFloat(componentData["rotvel"]);

    force.x = JsonReader::getFieldAsFloat(componentData["force_x"]);
    force.y = JsonReader::getFieldAsFloat(componentData["force_y"]);

    torque = JsonReader::getFieldAsFloat(componentData["torque"]);

    setInertia(JsonReader::getFieldAsFloat(componentData["inertia"]));
    setMass(JsonReader::getFieldAsFloat(componentData["mass"]));

    gravityscale = JsonReader::getFieldAsFloat(componentData["gravityscale"]);
    gravity.x = JsonReader::getFieldAsFloat(componentData["gravity_x"]);
    gravity.y = JsonReader::getFieldAsFloat(componentData["gravity_y"]);

    staticstate = JsonReader::getFieldAsBool(componentData["staticstate"]);
}

void
BE::Component::Rigidbody::writeData(Json::Value & data_)
{
    std::string componentField = BE::Component::TypeStr[BE::Component::RIGIDBODY];

    JsonWriter::addValue(data_["Actors"][owner->_name][componentField]["restitution"], restitution);
    JsonWriter::addValue(data_["Actors"][owner->_name][componentField]["friction_static"], friction_static);
    JsonWriter::addValue(data_["Actors"][owner->_name][componentField]["friction_dynamic"], friction_dynamic);
    JsonWriter::addValue(data_["Actors"][owner->_name][componentField]["vel_x"], vel.x);
    JsonWriter::addValue(data_["Actors"][owner->_name][componentField]["vel_y"], vel.y);
    JsonWriter::addValue(data_["Actors"][owner->_name][componentField]["rotvel"], rotvel);
    JsonWriter::addValue(data_["Actors"][owner->_name][componentField]["force_x"], force.x);
    JsonWriter::addValue(data_["Actors"][owner->_name][componentField]["force_y"], force.y);
    JsonWriter::addValue(data_["Actors"][owner->_name][componentField]["torque"], torque);
    JsonWriter::addValue(data_["Actors"][owner->_name][componentField]["inertia"], inertia);
    JsonWriter::addValue(data_["Actors"][owner->_name][componentField]["mass"], mass);
    JsonWriter::addValue(data_["Actors"][owner->_name][componentField]["gravity_x"], gravity.x);
    JsonWriter::addValue(data_["Actors"][owner->_name][componentField]["gravity_y"], gravity.y);
    JsonWriter::addValue(data_["Actors"][owner->_name][componentField]["gravityscale"], gravityscale);
    JsonWriter::addValue(data_["Actors"][owner->_name][componentField]["staticstate"], staticstate);
}

void
BE::Component::Rigidbody::drawData()
{
    if (ImGui::CollapsingHeader("RigidBody Component"))
    {
        ImGui::PushItemWidth(160);
        {
            ImGui::Checkbox("Static State", &staticstate);
            ImGui::InputFloat("Restitution", &restitution, 10.f, 50.f, 2);
            //ImGui::InputInt("Restitution", &restitution, 1, 5);
            ImGui::InputFloat("Friction_static", &friction_static, 10.f, 50.f, 2);
            ImGui::InputFloat("Friction_dynamic", &friction_dynamic, 1.f, 50.f, 2);

            ImGui::InputFloat("Velocity_X", &vel.x, 10.f, 50.f, 2);
            ImGui::InputFloat("Velocity_Y", &vel.y, 10.f, 50.f, 2);
            ImGui::InputFloat("Rot_velocity", &rotvel, 10.f, 50.f, 2);
            ImGui::InputFloat("Force_X", &force.x, 10.f, 50.f, 2);
            ImGui::InputFloat("Force_Y", &force.y, 10.f, 50.f, 2);

            ImGui::InputFloat("Torque", &torque, 10.f, 50.f, 2);
            ImGui::InputFloat("Inertia", &inertia, 1.f, 50.f, 2);
            ImGui::InputFloat("Mass", &mass, 1.f, 50.f, 2);
            setInvInertia();
            setInvMass();

            ImGui::InputFloat("Gravity_X", &gravity.x, 10.f, 50.f, 2);
            ImGui::InputFloat("Gravity_Y", &gravity.y, 10.f, 50.f, 2);

            ImGui::InputFloat("Gravityscale", &gravityscale, 10.f, 50.f, 2);
        }
        ImGui::PopItemWidth();
    }
}

void BE::Component::Rigidbody::setInertia(float input) {
    inertia = input;
    setInvInertia();
}

const float BE::Component::Rigidbody::getInertia(void) const {
    return inertia;
}

void BE::Component::Rigidbody::setMass(float input) {
    mass = input;
    setInvMass();
}

void BE::Component::Rigidbody::setInvInertia(void) {
    if (inertia != 0) {
        inv_inertia = 1 / inertia;
    }
    else {
        inv_inertia = 0;
    }
}

void BE::Component::Rigidbody::setInvMass(void) {
    if (mass != 0) {
        inv_mass = 1 / mass;
    }
    else {
        inv_mass = 0;
    }
}

const float BE::Component::Rigidbody::getMass(void) const {
    return mass;
}

const float BE::Component::Rigidbody::getInvInertia(void) const {
    return inv_inertia;
}

const float BE::Component::Rigidbody::getInvMass(void) const {
    return inv_mass;
}
