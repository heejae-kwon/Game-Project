/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      Gameplay.cpp
Purpose:        Gameplay component used for the level generation
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#include <Components/Gameplay.hpp>
#include <Core/Debugger.hpp>
#include <Utilities/JsonReader.hh>
#include <Utilities/JsonWriter.hh>

BE::Component::Gameplay::Gameplay(Actor * owner_) :
    BaseComponent(identifier)
{
    type = Type::GAMEPLAY;
    owner = owner_;
}

BE::Component::Gameplay::~Gameplay()
{
}

void
BE::Component::Gameplay::getData(Json::Value & data_)
{
    std::string componentField = BE::Component::TypeStr[BE::Component::GAMEPLAY];
    Json::Value componentData = data_["Actors"][owner->_name][componentField];

    hp = JsonReader::getFieldAsInt(componentData["hp"]);

    numberOfRounds = JsonReader::getFieldAsInt(componentData["numberOfRounds"]);
    startingNbrEnemies = JsonReader::getFieldAsInt(componentData["startingNbrEnemies"]);
    numberEnemyStep = JsonReader::getFieldAsInt(componentData["numberEnemyStep"]);

    isFinalLevel = JsonReader::getFieldAsBool(componentData["isFinalLevel"]);
    if (!isFinalLevel)
    {
        nextLevelName = JsonReader::getFieldAsString(componentData["nextLevelName"]);
    }
}

void
BE::Component::Gameplay::writeData(Json::Value & data_)
{
    std::string componentField = BE::Component::TypeStr[BE::Component::GAMEPLAY];

    JsonWriter::addValue(data_["Actors"][owner->_name][componentField]["hp"], hp);

    JsonWriter::addValue(data_["Actors"][owner->_name][componentField]["numberOfRounds"], numberOfRounds);
    JsonWriter::addValue(data_["Actors"][owner->_name][componentField]["startingNbrEnemies"], startingNbrEnemies);
    JsonWriter::addValue(data_["Actors"][owner->_name][componentField]["numberEnemyStep"], numberEnemyStep);

    JsonWriter::addValue(data_["Actors"][owner->_name][componentField]["isFinalLevel"], isFinalLevel);
    if (!isFinalLevel)
    {
        JsonWriter::addValue(data_["Actors"][owner->_name][componentField]["nextLevelName"], nextLevelName);
    }
}

void
BE::Component::Gameplay::drawData()
{
    if (ImGui::CollapsingHeader("Gameplay Component"))
    {
        ImGui::PushItemWidth(160);
        {

            ImGui::InputInt("Hp", &hp, 1, 5);
            ImGui::Separator();
            if (ImGui::InputInt("Number of rounds", &numberOfRounds, 1, 2))
            {
                if (numberOfRounds < 0)
                {
                    numberOfRounds = 0;
                }
            }
            if (ImGui::InputInt("Number of starting enemies", &startingNbrEnemies, 1, 2))
            {
                if (startingNbrEnemies < 0)
                {
                    startingNbrEnemies = 0;
                }
            }
            if (ImGui::InputInt("Number of new enemies each round", &numberEnemyStep, 1, 2))
            {
                if (numberEnemyStep < 0)
                {
                    numberEnemyStep = 0;
                }
            }
            ImGui::Checkbox("Is final stage", &isFinalLevel);
            if (!isFinalLevel)
            {
                static char buf1[32] = "";
                // Modify texture id
                ImGui::PushItemWidth(160);
                {
                    ImGui::Text("Next level name: %s\n", nextLevelName.c_str());
                    if (ImGui::InputText("##texture id", buf1, 32, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CharsNoBlank))
                    {
                        nextLevelName = buf1;
                        buf1[0] = '\0';
                    }
                }
                ImGui::PopItemWidth();
            }
        }
        ImGui::PopItemWidth();
    }
}