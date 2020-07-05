/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      Camera.cpp
Purpose:        camera movement
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/
#include "oCamera.hpp"

Stage::oCamera::oCamera(BE::Actor * rhs) :
    cameraActor(rhs)
{
}

void Stage::oCamera::Update(float dt_)
{
    if (shakeTime > 0)
    {
        static float _cooldown = 0.f;

        _cooldown -= dt_;
        if (_cooldown <= 0.f)
        {
            static bool leftShake = true;

            _cooldown = 0.05f;

            if (leftShake)
            {
                srand(static_cast<unsigned int>(shakeTime * dt_ * 1000));
                positionOffset.x = static_cast<float>((rand() % shakeMaxValue) * shakeStrength.x);
                srand(static_cast<unsigned int>(shakeTime * dt_ * 2000));
                positionOffset.y = static_cast<float>((rand() % shakeMaxValue) * shakeStrength.y);
                leftShake = false;
            }
            else
            {
                srand(static_cast<unsigned int>(shakeTime * dt_ * 1000));
                positionOffset.x = static_cast<float>(-((rand() % shakeMaxValue) * shakeStrength.x));
                srand(static_cast<unsigned int>(shakeTime * dt_ * 2000));
                positionOffset.y = static_cast<float>(-((rand() % shakeMaxValue) * shakeStrength.y));
                leftShake = true;
            }
            --shakeTime;
        }
    }
    else
    {
        positionOffset = glm::vec2(0.f);
    }

    currentPosition += positionOffset;
    if (moveToPosition != currentPosition)
    {
        static float _cooldown = 0.f;

        _cooldown -= dt_;

        float xDistance;
        float yDistance;
        int xSign;
        int ySign;
        float xMoveDistance = 5.f;
        float yMoveDistance = 5.f;

        xDistance = currentPosition.x - moveToPosition.x;
        yDistance = currentPosition.y - moveToPosition.y;

        xSign = (xDistance < 0.f) ? 1 : -1;
        ySign = (yDistance < 0.f) ? 1 : -1;

        xDistance = abs(xDistance);
        yDistance = abs(yDistance);

        if (yDistance != 0 && xDistance > yDistance)
        {
            float per = xMoveDistance * 100 / xDistance;

            yMoveDistance = (per * yDistance) / 100.f;
        }
        else if (xDistance != 0 && yDistance > xDistance)
        {
            float per = yMoveDistance * 100 / yDistance;

            xMoveDistance = (per * xDistance) / 100;
        }

        if (xDistance + yDistance > 100.f)
        {
            xSign *= static_cast<int>((xDistance + yDistance) / 5.f);
            ySign *= static_cast<int>((xDistance + yDistance) / 5.f);
        }

        if (moveToPosition.x != currentPosition.x)
        {
            if (xDistance < xMoveDistance)
            {
                currentPosition.x = moveToPosition.x;
            }
            else
            {
                currentPosition.x += (xMoveDistance * xSign) / 50.f;
            }
        }
        if (moveToPosition.y != currentPosition.y)
        {
            if (yDistance < yMoveDistance)
            {
                currentPosition.y = moveToPosition.y;
            }
            else
            {
                currentPosition.y += (yMoveDistance * ySign) / 50.f;
            }
        }
        cameraActor->getComponent<BE::Component::Transform>()->position = glm::vec3(currentPosition, 1.0f);
    }
}

void Stage::oCamera::setActor(BE::Actor * rhs_)
{
    cameraActor = rhs_;
}

void Stage::oCamera::setPosition(glm::vec2 pos_)
{
    moveToPosition = pos_;
}

void Stage::oCamera::setCameraShake(int time_, glm::vec2 strength_, int maxValue_)
{
    shakeTime = time_;
    shakeStrength = strength_;
    shakeMaxValue = maxValue_;
}

void Stage::oCamera::cameraShake(int x_, int y_)
{
    currentPosition.x += x_;
    currentPosition.y += y_;
}
