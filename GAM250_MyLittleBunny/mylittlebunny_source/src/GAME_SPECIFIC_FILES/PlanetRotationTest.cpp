/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      PlanetRotationTest.cpp
Purpose:        testing a planet rotation with using mouse.
Language:       C++
Project:        GAM250
Author:         Name : Stuat Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/
#include "PlanetRotationTest.hpp"

#include "inputAbstraction.hh"

#include <glm/gtc/matrix_transform.hpp>

Stage::PlanetRotationTest::PlanetRotationTest() :
    BaseStage("PlanetRotationTest.stg"), _isOnPlanet(false), _playerRotation(0.f), _currentPlanet(nullptr)
{
}

void
Stage::PlanetRotationTest::start(std::string fileName_)
{
    loadProps(fileName_);
    loadStageFile(fileName_);

    _player = getActor("player");
    if (_player)
    {
        _playerTransform = _player->getComponent<BE::Component::Transform>();
        _playerCollider = _player->getComponent<BE::Component::CircleCollider>();
    }
    _planet1 = getActor("planet1");
    if (_planet1)
    {
        _planet1Transform = _planet1->getComponent<BE::Component::Transform>();
        _planet1Collider = _planet1->getComponent<BE::Component::CircleCollider>();
    }
    _planet2 = getActor("planet2");
    if (_planet2)
    {
        _planet2Transform = _planet2->getComponent<BE::Component::Transform>();
        _planet2Collider = _planet2->getComponent<BE::Component::CircleCollider>();
    }
}

void
Stage::PlanetRotationTest::resume()
{
}

void
Stage::PlanetRotationTest::pause()
{
}

void
Stage::PlanetRotationTest::update(float dt_)
{
    if (_player && _planet1 && _planet2)
    {
        int leftIsTriggered = (int)Input::isTriggered(Input::Actions::LEFT);
        int rightIsTriggered = (int)Input::isTriggered(Input::Actions::RIGHT);
        int upIsTriggered = (int)Input::isTriggered(Input::Actions::UP);
        int downIsTriggered = (int)Input::isTriggered(Input::Actions::DOWN);
        int jumpIsTriggered = (int)Input::isPressed(Input::Actions::JUMP);

        int leftIsDown = (int)Input::isPressed(Input::Actions::LEFT);
        int rightIsDown = (int)Input::isPressed(Input::Actions::RIGHT);

        if (leftIsDown)
        {
            _playerTransform->scale.x = 1;
        }
        else if (rightIsDown)
        {
            _playerTransform->scale.x = -1;
        }


        if (!_isOnPlanet)
        {
            setMovement(leftIsTriggered, rightIsTriggered, upIsTriggered, downIsTriggered);
            smoothRotation(dt_);
            if (jumpIsTriggered)
            {
                _directionForce.x -= (_directionForce.x > 0) ? (_directionForce.x / 10.f) : (_directionForce.x / 10.f);
                _directionForce.y -= (_directionForce.y > 0) ? (_directionForce.y / 10.f) : (_directionForce.y / 10.f);
            }

            _playerTransform->position.x += _directionForce.x * BASE_SPEED_MULTIPLIER * dt_;
            _playerTransform->position.y += _directionForce.y * BASE_SPEED_MULTIPLIER * dt_;

            if (BE::Core::Physics::instance()->Collision(_player, _planet1) == BE::Core::Physics::CS_Start)
            {
                _currentPlanet = _planet1;
                _currentPlanetTransform = _planet1Transform;
                _currentPlanetCollider = _planet1Collider;
            }
            else if (BE::Core::Physics::instance()->Collision(_player, _planet2) == BE::Core::Physics::CS_Start)
            {
                _currentPlanet = _planet2;
                _currentPlanetTransform = _planet2Transform;
                _currentPlanetCollider = _planet2Collider;
            }

            if (_currentPlanet != nullptr &&
                BE::Core::Physics::instance()->Collision(_player, _currentPlanet) == BE::Core::Physics::CS_Start)
            {
                _isOnPlanet = true;

                glm::vec3 relativePositon = _playerTransform->position - _currentPlanetTransform->position;
                _playerRotation = -glm::degrees(glm::atan(relativePositon.x, relativePositon.y));

                glm::mat4 translationPlanet;

                glm::vec3 planetTop = glm::vec3(_currentPlanetTransform->position.x, _currentPlanetTransform->position.y + _currentPlanetCollider->radius + _playerCollider->radius, 0.f);

                {
                    translationPlanet = glm::translate(translationPlanet, _currentPlanetTransform->position); // Move origin of rotation to center of quad
                    translationPlanet = glm::rotate(translationPlanet, glm::radians(_playerRotation), glm::vec3(0.0f, 0.0f, 1.0f)); // Then rotate
                    translationPlanet = glm::translate(translationPlanet, -_currentPlanetTransform->position); // Move origin back

                    translationPlanet = glm::translate(translationPlanet, planetTop);
                }

                _playerTransform->position = (glm::vec3)(translationPlanet * glm::vec4(1.f, 1.f, 1.f, 1.f));
                _playerTransform->rotation = _playerRotation;
            }
        }
        else if (_isOnPlanet)
        {

            _playerRotation -= rightIsDown * (BASE_SPEED_MULTIPLIER / 3.f) * dt_;
            _playerRotation += leftIsDown  * (BASE_SPEED_MULTIPLIER / 3.f) * dt_;

            glm::mat4 translationPlanet;

            glm::vec3 planetTop = glm::vec3(_currentPlanetTransform->position.x, _currentPlanetTransform->position.y + _currentPlanetCollider->radius + _playerCollider->radius, 0.f);

            {
                translationPlanet = glm::translate(translationPlanet, _currentPlanetTransform->position); // Move origin of rotation to center of quad
                translationPlanet = glm::rotate(translationPlanet, glm::radians(_playerRotation), glm::vec3(0.0f, 0.0f, 1.0f)); // Then rotate
                translationPlanet = glm::translate(translationPlanet, -_currentPlanetTransform->position); // Move origin back

                if (jumpIsTriggered)
                {
                    _isOnPlanet = false;

                    planetTop = glm::vec3(_currentPlanetTransform->position.x, _currentPlanetTransform->position.y + _currentPlanetCollider->radius + (_playerCollider->radius * 2), 0.f);
                    _directionForce.x = 0.f;
                    _directionForce.y = 0.f;
                }

                translationPlanet = glm::translate(translationPlanet, planetTop);
            }

            //            translationPlanet = glm::rotate(translationPlanet, glm::radians(_playerRotation), glm::vec3(.0f, .0f, 1.0f));

            _playerTransform->position = (glm::vec3)(translationPlanet * glm::vec4(1.f, 1.f, 1.f, 1.f));
            _playerTransform->rotation = _playerRotation;

        }
    }
    else
    {
        static bool messageNotSent = true;

        if (messageNotSent)
        {
            messageNotSent = false;
            BE::Core::Debugger::instance()->AddLog("[ERROR][%s] At least one of the actors was not retrieved properly.\n", __func__);
        }
    }
}

static int
getClosestAngleDir(float angle1_, float angle2_)
{
    double diff1 = (int(angle2_ - angle1_) + 180) % 360 - 180;
    diff1 = diff1 < -180 ? diff1 + 360 : diff1;

    return diff1 > 0 ? 1 : -1;
}

void
Stage::PlanetRotationTest::smoothRotation(float dt_)
{
    if (_playerTransform->rotation != _rotationTarget) // Please help me with these maths
    {
        static float _cooldown = 0.f;

        _cooldown -= dt_;
        if (_cooldown <= 0.f)
        {
            _cooldown = 0.01f;
            float currentRotation = _playerTransform->rotation;
            float rotDistance;
            float rotMoveDistance = 12.f;

            rotDistance = currentRotation - _rotationTarget;

            rotDistance = abs(rotDistance);
            int rotSign = getClosestAngleDir(currentRotation, _rotationTarget);

            if (rotDistance < rotMoveDistance)
            {
                currentRotation = _rotationTarget;
            }
            else
            {
                currentRotation += rotMoveDistance * rotSign;
            }

            if (currentRotation > 180)
            {
                currentRotation = (currentRotation - 360);
            }
            else if (currentRotation < -180)
            {
                currentRotation = (currentRotation + 360);
            }

            _playerTransform->rotation = currentRotation;
        }
    }
}

void Stage::PlanetRotationTest::setMovement(int left_, int right_, int up_, int down_)
{
    // Movement
    {
        if (right_ || left_)
        {
            _directionForce.x = (float)(-left_ + right_);
        }
        if (up_ || down_)
        {
            _directionForce.y = (float)(-down_ + up_);
        }
    }
    // Rotation
    {
        if (_directionForce.x > 0 && _directionForce.y > 0)
        {
            _rotationTarget = -45;
        }
        else if (_directionForce.x > 0 && _directionForce.y < 0)
        {
            _rotationTarget = -135;
        }
        else if (_directionForce.x < 0 && _directionForce.y > 0)
        {
            _rotationTarget = 45;
        }
        else if (_directionForce.x < 0 && _directionForce.y < 0)
        {
            _rotationTarget = 135;
        }
        else if (_directionForce.x > 0)
        {
            _rotationTarget = -90;
        }
        else if (_directionForce.x < 0)
        {
            _rotationTarget = 90;
        }
        else if (_directionForce.y > 0)
        {
            _rotationTarget = 0;
        }
        else if (_directionForce.y < 0)
        {
            _rotationTarget = 180;
        }
    }
}
