/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      Gamepad.cpp
Purpose:        Handles state of the gamepad
Language:       C++
Project:        GAM200
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#include "Gamepad.hpp"

#include <windows.h>
#include <xinput.h>

BE::Input::Gamepad::Gamepad()
    : keyIsPressed(arraySize), keyIsTriggered(arraySize)
{
    up = false;
    down = false;
    left = false;
    right = false;
    start = false;
    back = false;
    leftShoulder = false;
    rightShoulder = false;
    buttonA = false;
    buttonB = false;
    buttonX = false;
    buttonY = false;
}

void
BE::Input::Gamepad::turnonKey(int key)
{
    for (size_t i = 0; i < keyIsPressed.size(); ++i)
    {
        if (IsPressed(static_cast<GP::KeyCode>(key)))
        {
            return;
        }
        if (keyIsPressed[i] == GP::KeyCode::BUTTON_UNKNOWN)
        {
            keyIsPressed[i] = static_cast<GP::KeyCode>(key);
            keyIsTriggered[i] = static_cast<GP::KeyCode>(key);
            return;
        }
    }
}

void
BE::Input::Gamepad::turnoffKey(int key)
{
    for (size_t i = 0; i < keyIsPressed.size(); ++i)
    {
        if (keyIsPressed[i] == key)
        {
            keyIsPressed[i] = GP::KeyCode::BUTTON_UNKNOWN;
            return;
        }
    }
}

void BE::Input::Gamepad::setXValue(float value_)
{
    leftStick.x = value_;
}

void BE::Input::Gamepad::setYValue(float value_)
{

    leftStick.y = value_;

}

glm::vec2 BE::Input::Gamepad::getLeftStick()
{
    return leftStick;
}

glm::vec2 BE::Input::Gamepad::getRightStick()
{
    return rightStick;
}

bool
BE::Input::Gamepad::IsPressed(GP::KeyCode key)
{
    switch (key)
    {
    case GP::KeyCode::BUTTON_A:
        return buttonA;
    case GP::KeyCode::BUTTON_B:
        return buttonB;
    case GP::KeyCode::BUTTON_X:
        return buttonX;
    case GP::KeyCode::BUTTON_Y:
        return buttonY;
    case GP::KeyCode::BUTTON_START:
        return start;
    case GP::KeyCode::BUTTON_BACK:
        return back;
    case GP::KeyCode::BUTTON_DPAD_UP:
        return up;
    case GP::KeyCode::BUTTON_DPAD_DOWN:
        return down;
    case GP::KeyCode::BUTTON_DPAD_LEFT:
        return left;
    case GP::KeyCode::BUTTON_DPAD_RIGHT:
        return right;
    default:
        return false;
    }
}

bool
BE::Input::Gamepad::IsTriggered(GP::KeyCode key)
{
    switch (key)
    {
    case GP::KeyCode::BUTTON_A:
        return (buttonA && !trigButtonA);
    case GP::KeyCode::BUTTON_B:
        return (buttonB && !trigButtonB);
    case GP::KeyCode::BUTTON_X:
        return (buttonX && !trigButtonX);
    case GP::KeyCode::BUTTON_Y:
        return (buttonY && !trigButtonY);
    case GP::KeyCode::BUTTON_START:
        return (start && !trigStart);
    case GP::KeyCode::BUTTON_BACK:
        return (back && !trigBack);
    case GP::KeyCode::BUTTON_DPAD_UP:
        return (up && !trigUp);
    case GP::KeyCode::BUTTON_DPAD_DOWN:
        return (down && !trigDown);
    case GP::KeyCode::BUTTON_DPAD_LEFT:
        return (left && !trigLeft);
    case GP::KeyCode::BUTTON_DPAD_RIGHT:
        return (right && !trigRight);
    default:
        return false;
    }
}

void
BE::Input::Gamepad::clearTrigger()
{
    trigUp = up;
    trigDown = down;
    trigLeft = left;
    trigRight = right;
    trigStart = start;
    trigBack = back;
    trigLeftShoulder = leftShoulder;
    trigRightShoulder = rightShoulder;
    trigButtonA = buttonA;
    trigButtonB = buttonB;
    trigButtonX = buttonX;
    trigButtonY = buttonY;
}

void BE::Input::Gamepad::update()
{
    XINPUT_STATE controllerState;
    if (XInputGetState(0, &controllerState) == 0L)
    {
        XINPUT_GAMEPAD *pad = &controllerState.Gamepad;
        up = (pad->wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0;
        down = (pad->wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0;
        left = (pad->wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0;
        right = (pad->wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0;
        start = (pad->wButtons & XINPUT_GAMEPAD_START) != 0;
        back = (pad->wButtons & XINPUT_GAMEPAD_BACK) != 0;
        leftShoulder = (pad->wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0;
        rightShoulder = (pad->wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0;
        buttonA = (pad->wButtons & XINPUT_GAMEPAD_A) != 0;
        buttonB = (pad->wButtons & XINPUT_GAMEPAD_B) != 0;
        buttonX = (pad->wButtons & XINPUT_GAMEPAD_X) != 0;
        buttonY = (pad->wButtons & XINPUT_GAMEPAD_Y) != 0;

        leftStick.x = pad->sThumbLX;
        leftStick.y = pad->sThumbLY;

        if (leftStick.x > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  && !right)
        {
            right = true;
        }
        if (leftStick.x < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  && !left)
        {
            left = true;
        }
        if (leftStick.y > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  && !up)
        {
            up = true;
        }
        if (leftStick.y < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  && !down)
        {
            down = true;
        }

        rightStick.x = pad->sThumbRX;
        rightStick.y = pad->sThumbRY;
    }
}
