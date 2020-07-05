/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      Keyboard.cpp
Purpose:        Handles state of the keyboard
Language:       C++
Project:        GAM200
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#include "Keyboard.hpp"

BE::Input::Keyboard::Keyboard()
    : keyIsPressed(arraySize), keyIsTriggered(arraySize)
{
    for (auto & key : keyIsPressed)
    {
        key = KB::KeyCode::KEY_UNKNOWN;
    }
    for (auto & key : keyIsTriggered)
    {
        key = KB::KeyCode::KEY_UNKNOWN;
    }
}

void
BE::Input::Keyboard::turnonKey(int key)
{
    for (size_t i = 0; i < keyIsPressed.size(); ++i)
    {
        if (IsPressed(static_cast<KB::KeyCode>(key)))
        {
            return;
        }
        if (keyIsPressed[i] == KB::KeyCode::KEY_UNKNOWN)
        {
            keyIsPressed[i]     = static_cast<KB::KeyCode>(key);
            keyIsTriggered[i]   = static_cast<KB::KeyCode>(key);
            return;
        }
    }
}

void
BE::Input::Keyboard::turnoffKey(int key)
{
    for (size_t i = 0; i < keyIsPressed.size(); ++i)
    {
        if (keyIsPressed[i] == key)
        {
            keyIsPressed[i] = KB::KeyCode::KEY_UNKNOWN;
            return;
        }
    }
}

bool
BE::Input::Keyboard::IsPressed(KB::KeyCode key)
{
    for (size_t i = 0; i < keyIsPressed.size(); ++i)
    {
        if (static_cast<KB::KeyCode>(key) == KB::KeyCode::KEY_ANY)
        {
            if (keyIsPressed[i] != KB::KeyCode::KEY_UNKNOWN)
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
BE::Input::Keyboard::IsTriggered(KB::KeyCode key)
{
    for (size_t i = 0; i < keyIsTriggered.size(); ++i)
    {
        if (static_cast<KB::KeyCode>(key) == KB::KeyCode::KEY_ANY)
        {
            if (keyIsTriggered[i] != KB::KeyCode::KEY_UNKNOWN)
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
BE::Input::Keyboard::clearTrigger()
{
    for (size_t i = 0; i < keyIsTriggered.size(); ++i)
    {
        keyIsTriggered[i] = KB::KeyCode::KEY_UNKNOWN;
    }
}
