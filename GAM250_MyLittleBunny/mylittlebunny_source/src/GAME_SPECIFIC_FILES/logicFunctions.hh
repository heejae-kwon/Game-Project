/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      logicFunctions.hh
Purpose:        Contains logic function that can be used in the different stages
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#pragma once
#include <BunnyEngine.hpp>
#include <Components/Components.hh>
#include <WIP/Keyboard.hpp>
#include <WIP/Gamepad.hpp>
#include <WIP/HBMath.hpp>

namespace logic
{
    namespace camera
    {
        static void cameraMoveLogic(BE::Actor* camera_, float dt_)
        {
            if (BE::Input::Keyboard::instance()->IsPressed(BE::KB::KeyCode::KEY_RIGHT) || BE::Input::Keyboard::instance()->IsPressed(BE::KB::KeyCode::KEY_a))
            {
                camera_->getComponent<BE::Component::Transform>()->position.x -= 150.f * dt_;
            }
            if (BE::Input::Keyboard::instance()->IsPressed(BE::KB::KeyCode::KEY_LEFT))
            {
                camera_->getComponent<BE::Component::Transform>()->position.x += 150.f * dt_;
            }
            if (BE::Input::Keyboard::instance()->IsPressed(BE::KB::KeyCode::KEY_UP))
            {
                if (BE::Input::Keyboard::instance()->IsPressed(BE::KB::KeyCode::KEY_LCTRL))
                {
                    camera_->getComponent<BE::Component::Camera>()->zoom -= .5f * dt_;
                }
                else
                {
                    camera_->getComponent<BE::Component::Transform>()->position.y += 150.f * dt_;
                }
            }
            if (BE::Input::Keyboard::instance()->IsPressed(BE::KB::KeyCode::KEY_DOWN))
            {
                if (BE::Input::Keyboard::instance()->IsPressed(BE::KB::KeyCode::KEY_LCTRL))
                {
                    camera_->getComponent<BE::Component::Camera>()->zoom += .5f * dt_;
                }
                else
                {
                    camera_->getComponent<BE::Component::Transform>()->position.y -= 150.f * dt_;

                }
            }
        }
    }


    namespace player
    {
        static void playerMoveLogic(BE::Actor* actor_, float dt_)
        {
            glm::vec2 leftStick = BE::Input::Gamepad::instance()->getLeftStick();
            glm::vec2 rightStick = BE::Input::Gamepad::instance()->getRightStick();

            BE::Core::Debugger::instance()->AddLog("left %.2f %.2f\n", leftStick.x, leftStick.y);
            //BE::Core::Debugger::instance()->AddLog("right %.2f %.2f\n", rightStick.x, rightStick.y);

            if (BE::Input::Keyboard::instance()->IsPressed(BE::KB::KeyCode::KEY_RIGHT) ||
                BE::Input::Keyboard::instance()->IsPressed(BE::KB::KeyCode::KEY_a) ||
                leftStick.x > 8000.f)
            {
                if (actor_->getComponent<BE::Component::Rigidbody>()->force.x < 3000.f)
                    actor_->getComponent<BE::Component::Rigidbody>()->force.x += 300000.f * dt_;
            }
            if (BE::Input::Keyboard::instance()->IsPressed(BE::KB::KeyCode::KEY_LEFT) ||
                leftStick.x < -8000.f)
            {
                if (actor_->getComponent<BE::Component::Rigidbody>()->force.x > -3000.f)
                    actor_->getComponent<BE::Component::Rigidbody>()->force.x -= 300000.f * dt_;
            }
            if (BE::Input::Keyboard::instance()->IsPressed(BE::KB::KeyCode::KEY_UP) ||
                leftStick.y > 8000.f)
            {
                if (actor_->getComponent<BE::Component::Rigidbody>()->force.y < 3000.f)
                    actor_->getComponent<BE::Component::Rigidbody>()->force.y += 300000.f * dt_;
            }
            if (BE::Input::Keyboard::instance()->IsPressed(BE::KB::KeyCode::KEY_DOWN) ||
                leftStick.y < -8000.f)
            {
                if (actor_->getComponent<BE::Component::Rigidbody>()->force.y > -3000.f)
                    actor_->getComponent<BE::Component::Rigidbody>()->force.y -= 300000.f * dt_;
            }
        }

        static void playerPlanetMoveLogic(BE::Actor* player_, float dt_)
        {
            BE::HBVec2 gravDir = { player_->getComponent<BE::Component::Rigidbody>()->gravity.x - player_->getComponent<BE::Component::Transform>()->position.x,
                player_->getComponent<BE::Component::Rigidbody>()->gravity.y - player_->getComponent<BE::Component::Transform>()->position.y };
            gravDir.Normalize();
            BE::HBVec2 movDir = gravDir;
            movDir.Rotate(BE::HBMath::DegreeToRadian(90));

            static float sum = 0.f;

            sum += dt_;
            BE::Core::Debugger::instance()->AddLog("dt %.5f\n", sum);

            //			if (BE::Input::Keyboard::instance()->IsPressed(BE::KB::KeyCode::KEY_UP))
            //{
            //    player_->getComponent<BE::Component::Rigidbody>()->force.x += (1500000.f * gravDir.x) * dt_;
            //    player_->getComponent<BE::Component::Rigidbody>()->force.y += (1500000.f * gravDir.y) * dt_;
            //}

            if (BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KeyCode::KEY_SPACE))
            {
                player_->getComponent<BE::Component::Rigidbody>()->force.x -= (50000000.f * gravDir.x) * dt_;
                player_->getComponent<BE::Component::Rigidbody>()->force.y -= (50000000.f * gravDir.y) * dt_;
            }

            if (BE::Input::Keyboard::instance()->IsPressed(BE::KB::KeyCode::KEY_RIGHT))
            {
                player_->getComponent<BE::Component::Rigidbody>()->force.x += (500000.f * movDir.x) * dt_;
                player_->getComponent<BE::Component::Rigidbody>()->force.y += (500000.f * movDir.y) * dt_;
            }
            if (BE::Input::Keyboard::instance()->IsPressed(BE::KB::KeyCode::KEY_LEFT))
            {
                player_->getComponent<BE::Component::Rigidbody>()->force.x -= (500000.f * movDir.x) * dt_;
                player_->getComponent<BE::Component::Rigidbody>()->force.y -= (500000.f * movDir.y) * dt_;
            }

            /*if (BE::Input::Keyboard::instance()->IsPressed(BE::KB::KeyCode::KEY_UP))
            {
            player_->getComponent<BE::Component::Transform>()->position.x -= 150.f * dt_ * gravDir.x;
            player_->getComponent<BE::Component::Transform>()->position.y -= 150.f * dt_ * gravDir.y;
            }
            if (BE::Input::Keyboard::instance()->IsPressed(BE::KB::KeyCode::KEY_DOWN))
            {
            player_->getComponent<BE::Component::Transform>()->position.x += 150.f * dt_ * gravDir.x;
            player_->getComponent<BE::Component::Transform>()->position.y += 150.f * dt_ * gravDir.y;
            }

            if (BE::Input::Keyboard::instance()->IsPressed(BE::KB::KeyCode::KEY_RIGHT))
            {
            player_->getComponent<BE::Component::Transform>()->position.x += 150.f * dt_ * movDir.x;
            player_->getComponent<BE::Component::Transform>()->position.y += 150.f * dt_ * movDir.y;
            }
            if (BE::Input::Keyboard::instance()->IsPressed(BE::KB::KeyCode::KEY_LEFT))
            {
            player_->getComponent<BE::Component::Transform>()->position.x -= 150.f * dt_ * movDir.x;
            player_->getComponent<BE::Component::Transform>()->position.y -= 150.f * dt_ * movDir.y;
            }*/
            /*player_->getComponent<BE::Component::Transform>()->position.x += 150.f * dt_ * gravDir.x;
            player_->getComponent<BE::Component::Transform>()->position.y += 150.f * dt_ * gravDir.y;*/

        }
    }

    namespace character
    {
        static void planetGravity(std::vector<BE::Actor*> planetVector_, BE::Actor* character_, float /*dt_*/)
        {
            if (!character_->getComponent<BE::Component::Rigidbody>())
            {
                BE::Core::Debugger::instance()->AddLog("-------------------------------------------\n");
                BE::Core::Debugger::instance()->AddLog("Charactor name '%s' do not have rigidbody \n", character_->_name.c_str());
                BE::Core::Debugger::instance()->AddLog("-------------------------------------------\n");
                return;
            }
            for (auto & planet : planetVector_)
            {
                BE::HBVec2 charPos = { character_->getComponent<BE::Component::Transform>()->position.x, character_->getComponent<BE::Component::Transform>()->position.y };
                BE::HBVec2 planetPos = { planet->getComponent<BE::Component::Transform>()->position.x, planet->getComponent<BE::Component::Transform>()->position.y };
                BE::HBVec2 recentGravity = { (charPos.x) - (character_->getComponent<BE::Component::Rigidbody>()->gravity.x),
                    (charPos.y) - (character_->getComponent<BE::Component::Rigidbody>()->gravity.y) };

                BE::HBVec2 planetGravity((planetPos.x) - (charPos.x), (planetPos.y) - (charPos.y));

                // Try to rotate the imange but rotation is int
                //character_->getComponent<BE::Component::Transform>()->rotation = atan2f(-planetGravity.y, -planetGravity.x) * (180 / 3.141592) - 90  % 360;

                if (planetGravity.Length() < recentGravity.Length())
                {
                    character_->getComponent<BE::Component::Rigidbody>()->gravity = planetPos;
                }
                //else if (planetGravity.Length() == recentGravity.Length())
                 //   BE::Core::Debugger::instance()->AddLog("Charactor name '%s' follow the '%s' \n", character_->_name.c_str(), planet->_name.c_str());
            }
        }


    }

    namespace spawner
    {
    }

    namespace actors
    {
        static float pointObj(BE::Actor* act1, BE::Actor* act2)
        {
            float result = 0;
            glm::vec3 act1Pos = act1->getComponent<BE::Component::Transform>()->position;
            glm::vec3 act2Pos = act2->getComponent<BE::Component::Transform>()->position;
            glm::vec3 distance = (act2Pos - act1Pos);

            //BE::Core::Debugger::instance()->AddLog("X value: %d\n", distance.length());

            result = ((distance.x) / (glm::length(distance)));
            result = (glm::acos(result));

            if (distance.y > 0)
            {
                //BE::Core::Debugger::instance()->AddLog("positive: %f\n", result);

                act1->getComponent<BE::Component::Transform>()->rotation = (glm::degrees(result));
                return result;

            }
            else
            {
                //BE::Core::Debugger::instance()->AddLog("negative: %f\n", -result);
                act1->getComponent<BE::Component::Transform>()->rotation = (glm::degrees(-result));
                return -result;

            }

        }
    }
}