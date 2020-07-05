/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      Mouse.cpp
Purpose:        Handles state of the mouse
Language:       C++
Project:        GAM200
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#include "Mouse.hpp"

BE::Input::Mouse::Mouse()
    : keyIsPressed(arraySize), keyIsTriggered(arraySize),  mousePos{0, 0}
{
    for (auto & key : keyIsPressed)
    {
        key = MS::KeyCode::KEY_UNKNOWN;
    }
    for (auto & key : keyIsTriggered)
    {
        key = MS::KeyCode::KEY_UNKNOWN;
    }
}

void
BE::Input::Mouse::turnonKey(int key)
{
    for (size_t i = 0; i < keyIsPressed.size(); ++i)
    {
        if (IsPressed(static_cast<MS::KeyCode>(key)))
        {
            return;
        }
        if (keyIsPressed[i] == MS::KeyCode::KEY_UNKNOWN)
        {
            keyIsPressed[i] = static_cast<MS::KeyCode>(key);
            keyIsTriggered[i] = static_cast<MS::KeyCode>(key);
            return;
        }
    }
}

void
BE::Input::Mouse::turnoffKey(int key)
{
    for (size_t i = 0; i < keyIsPressed.size(); ++i)
    {
        if (keyIsPressed[i] == key)
        {
            keyIsPressed[i] = MS::KeyCode::KEY_UNKNOWN;
            return;
        }
    }
}

void
BE::Input::Mouse::setMousePosition(int x, int y)
{
    mousePos.x = x;
    mousePos.y = y;
}

glm::vec2
BE::Input::Mouse::getMousePosition()
{
    return  glm::vec2(mousePos.x, mousePos.y);
}

bool
BE::Input::Mouse::IsPressed(MS::KeyCode key)
{
    for (size_t i = 0; i < keyIsPressed.size(); ++i)
    {
        if (static_cast<MS::KeyCode>(key) == MS::KeyCode::KEY_ANY)
        {
            if (keyIsPressed[i] != MS::KeyCode::KEY_UNKNOWN)
            {
                return true;
            }
        }
        else if (keyIsPressed[i] == key)
        {
            return true;
        }
    }
    return false;
}

bool
BE::Input::Mouse::IsTriggered(MS::KeyCode key)
{
    for (size_t i = 0; i < keyIsTriggered.size(); ++i)
    {
        if (static_cast<MS::KeyCode>(key) == MS::KeyCode::KEY_ANY)
        {
            if (keyIsTriggered[i] != MS::KeyCode::KEY_UNKNOWN)
            {
                return true;
            }
        }
        else if (keyIsTriggered[i] == key)
        {
            return true;
        }
    }
    return false;
}

void
BE::Input::Mouse::clearTrigger()
{
    for (size_t i = 0; i < keyIsTriggered.size(); ++i)
    {
        keyIsTriggered[i] = MS::KeyCode::KEY_UNKNOWN;
    }
}
