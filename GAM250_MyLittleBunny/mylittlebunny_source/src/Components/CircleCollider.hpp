/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      CircleCollider.hpp
Language:      C++
Project:         GAM250
Author:         Name : HeeJae Kwon
Email:            sfhy33@gmail.com
Creation date:   2017.06.16
----------------------------------------------------------------------------*/
#pragma once

#include <Components/BaseComponent.hpp>
//#include <WIP/Pair.hpp>

#include <glm\glm.hpp>
#include <json\json.h>

#include <vector>

namespace BE
{
    namespace Component
    {
        class CircleCollider : public BaseComponent
        {
        public:
            COMPONENT_HASH(CircleCollider)
            CircleCollider(Actor* owner_);
            ~CircleCollider();

            void    getData(Json::Value& data_)     final;
            void    writeData(Json::Value& data_)   final;
            void    drawData()                      final;

            float radius;
			bool ghost;

            struct collision
            {
                bool oldState;
                bool newState;
                CircleCollider *collider;
            };

            std::vector<collision> collisionVec;

            void updateCollision(CircleCollider* collider, bool newState_);
        };

    }
}
