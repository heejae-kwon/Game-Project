/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      ParticleEmitter.cpp
Purpose:        ParticleEmitter component used by the Particle core
Language:       C++
Project:        GAM250
Author:         Name :  Wonjae Jung
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#include <Components/ParticleEmitter.hpp>
#include <Components/Transform.hpp>
#include <Core/Particle.hpp>
#include <Core/Debugger.hpp>
#include <Utilities/JsonReader.hh>
#include <Utilities/JsonWriter.hh>

#include <imgui\imgui.h>
#include <glm/glm.hpp>
#include "ParticleEmitter.hpp"

BE::Component::ParticleEmitter::ParticleEmitter(Actor* owner_)
    : BaseComponent(identifier), _texture(owner_), lifetime(0), loop(false)
{
    type = Type::PARTICLEEMITTER;
    owner = owner_;
    Core::Particle::instance()->registerActor(owner);
}

BE::Component::ParticleEmitter::~ParticleEmitter()
{
    Core::Particle::instance()->unregisterActor(owner);
}

void BE::Component::ParticleEmitter::getData(Json::Value & data_)
{
    std::string componentField = BE::Component::TypeStr[BE::Component::PARTICLEEMITTER];
    Json::Value componentData = data_["Actors"][owner->_name][componentField];

    //For texture
    _texture.setTextureId(JsonReader::getFieldAsString(componentData["textureId"]));
    _texture.spriteIndex = JsonReader::getFieldAsInt(componentData["spriteIndex"]);

    //For glm
    pos = BE::JsonReader::getFieldAsVec3(componentData["pos"]);
    size = BE::JsonReader::getFieldAsVec2(componentData["size"]);
    capacity = JsonReader::getFieldAsInt(componentData["capacity"]);
    m_particle.resize(capacity);

    maxscale = JsonReader::getFieldAsFloat(componentData["maxscale"]);
    minscale = JsonReader::getFieldAsFloat(componentData["minscale"]);
    maxvel = JsonReader::getFieldAsFloat(componentData["maxvel"]);
    minvel = JsonReader::getFieldAsFloat(componentData["minvel"]);
    lifetime = JsonReader::getFieldAsFloat(componentData["lifetime"]);
    particleType = stringToParticleEnum(JsonReader::getFieldAsString(componentData["particleType"]));
    ddType = static_cast<int>(particleType);
    loop = JsonReader::getFieldAsBool(componentData["loop"]);
}

void BE::Component::ParticleEmitter::writeData(Json::Value & data_)
{
    std::string componentField = BE::Component::TypeStr[BE::Component::PARTICLEEMITTER];

    JsonWriter::addValue(data_["Actors"][owner->_name][componentField]["textureId"], _texture.getTextureId());
    JsonWriter::addValue(data_["Actors"][owner->_name][componentField]["spriteIndex"], _texture.spriteIndex);

    //For glm
    std::vector<float> posArray = { pos.x, pos.y, pos.z };
    BE::JsonWriter::addFloatArray(data_["Actors"][owner->_name][componentField]["pos"], posArray);

    std::vector<float> sizeArray = { size.x, size.y };
    BE::JsonWriter::addFloatArray(data_["Actors"][owner->_name][componentField]["size"], sizeArray);

    JsonWriter::addValue(data_["Actors"][owner->_name][componentField]["capacity"], capacity);
    JsonWriter::addValue(data_["Actors"][owner->_name][componentField]["maxscale"], maxscale);
    JsonWriter::addValue(data_["Actors"][owner->_name][componentField]["minscale"], minscale);
    JsonWriter::addValue(data_["Actors"][owner->_name][componentField]["maxvel"], maxvel);
    JsonWriter::addValue(data_["Actors"][owner->_name][componentField]["minvel"], minvel);
    JsonWriter::addValue(data_["Actors"][owner->_name][componentField]["particleType"], ParticleTypeStr[particleType]);
    JsonWriter::addValue(data_["Actors"][owner->_name][componentField]["lifetime"], lifetime);
    JsonWriter::addValue(data_["Actors"][owner->_name][componentField]["loop"], loop);
}

void BE::Component::ParticleEmitter::drawData()
{
    if (ImGui::CollapsingHeader("Particle Component"))
    {
        ImGui::Indent();
        ImGui::PushID(1);
        _texture.drawData();
        ImGui::PopID();
        ImGui::Unindent();

        ImGui::Separator();

        ImGui::PushItemWidth(160);
        {
            {
                if (ImGui::InputInt("capacity", &capacity, 1, 10))
                {
                    if (capacity < 0)
                    {
                        capacity = 0;
                    }
                    if (capacity > 200)
                    {
                        capacity = 200;
                    }
                    m_particle.resize(capacity);
                }
            }
            ImGui::InputFloat("pos_X", &pos.x, 10.f, 50.f, 2);
            ImGui::InputFloat("pos_Y", &pos.y, 10.f, 50.f, 2);
            if (ImGui::InputFloat("Pos_Z", &pos.z, 0.5f, 2.0f, 2))
            {
                //Core::Particle::instance()->updateSort();
            }

            ImGui::InputFloat("size_X", &size.x, 10.f, 50.f, 2);
            ImGui::InputFloat("size_Y", &size.y, 10.f, 50.f, 2);

            ImGui::InputFloat("maxscale", &maxscale, 10.f, 50.f, 2);
            ImGui::InputFloat("minscale", &minscale, 10.f, 50.f, 2);
            ImGui::InputFloat("maxvel", &maxvel, 10.f, 50.f, 2);
            ImGui::InputFloat("minvel", &minvel, 10.f, 50.f, 2);
            if (ImGui::Combo("Particle Type", &ddType, "ONE\0TWO\0THREE\0FOUR\0\0"))
            {
                if (ddType == 0)
                {
                    particleType = ParticleType::ONE;
                }
                else if (ddType == 1)
                {
                    particleType = ParticleType::TWO;
                }
                else if (ddType == 2)
                {
                    particleType = ParticleType::THREE;
                }
                else if (ddType == 3)
                {
                    particleType = ParticleType::FOUR;
                }
            }

            ImGui::InputFloat("lifetime", &lifetime, 1.f, 50.f, 2);
            ImGui::Checkbox("Loop", &loop);
			ImGui::Checkbox("Fade", &fade);
        }
        ImGui::PopItemWidth();
    }
}

void BE::Component::ParticleEmitter::setCapacity(int capacity_)
{
    capacity = capacity_;
    if (capacity < 0)
    {
        capacity = 0;
    }
    if (capacity > 200)
    {
        capacity = 200;
    }
    m_particle.resize(capacity);
}

void BE::Component::ParticleEmitter::resetParticles()
{
    for (auto &particle : m_particle)
    {
        particle.life = lifetime;
    }
}

BE::ParticleType
BE::Component::ParticleEmitter::stringToParticleEnum(std::string str_)
{
    if (str_ == "ONE")
    {
        return ParticleType::ONE;
    }
    else if (str_ == "TWO")
    {
        return ParticleType::TWO;
    }
    else if (str_ == "THREE")
    {
        return ParticleType::THREE;
    }
    else if (str_ == "FOUR")
    {
        return ParticleType::FOUR;
    }

    return ParticleType();
}
