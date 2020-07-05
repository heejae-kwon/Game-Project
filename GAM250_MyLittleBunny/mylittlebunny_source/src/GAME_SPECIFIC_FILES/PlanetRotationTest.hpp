/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      PlanetRotationTest.hh
Purpose:        tesing planet rotation which inheritance from the base stage.
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/
#pragma once

#include <BunnyEngine.hpp>
#include <BaseStage.hpp>
#include <Utilities/TimerManager.hpp>

#define BASE_SPEED_MULTIPLIER (int)500

namespace Stage
{
    //!  The PlanetRotationTest class. 
    /*!
    The PlanetRotationTest class is a test Stage.
    Andrew is using it to test character movement.
    */
    class PlanetRotationTest : public BE::Stage::BaseStage
    {
    public:
        PlanetRotationTest();
        ~PlanetRotationTest() = default;

        BaseStage*  cpy() final
        {
            return (new PlanetRotationTest());
        }

        void    start(std::string fileName_ = "") final;

        void    resume() final;
        void    pause() final;

        void    update(float dt_) final;
    protected:
        //
    private:
        //
        BE::Actor *_player;
        BE::Component::Transform        *_playerTransform;
        BE::Component::CircleCollider   *_playerCollider;

        BE::Actor *_currentPlanet;
        BE::Component::Transform        *_currentPlanetTransform;
        BE::Component::CircleCollider   *_currentPlanetCollider;

        BE::Actor *_planet1;
        BE::Component::Transform        *_planet1Transform;
        BE::Component::CircleCollider   *_planet1Collider;
        BE::Actor *_planet2;
        BE::Component::Transform        *_planet2Transform;
        BE::Component::CircleCollider   *_planet2Collider;


        bool _isOnPlanet;

        float _playerRotation;
        float _rotationTarget;
        glm::vec2 _directionForce;
    public:
        //
    protected:
        //
    private:
        void smoothRotation(float dt_);
        void setMovement(int left_, int right_, int up_, int down_);
    };
}