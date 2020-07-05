/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      Gameplay.hpp
Purpose:        Gameplay component used for the level generation
Language:       C++
Project:        GAM250
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

    class Gameplay : public BaseComponent
    {
    public:
        COMPONENT_HASH(Gameplay)
        Gameplay(Actor* owner_);
        ~Gameplay();

        void    getData(Json::Value& data_)     final;
        void    writeData(Json::Value& data_)   final;
        void    drawData()                      final;

        int hp;

        int numberOfRounds;
        int startingNbrEnemies;
        int numberEnemyStep;

        bool isFinalLevel;
        std::string nextLevelName;
    };

}
}
