/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      inputAbstraction.hh
Purpose:        Input abstraction to simplify keyboard and gamepad input checking
Language:       C++
Project:        GAM250
Author:         Name : Stuat Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#pragma once
#include <WIP/Keyboard.hpp>
#include <WIP/Gamepad.hpp>

namespace Input
{
    enum Actions {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        JUMP,
        POS_ACTION,
        NEG_ACTION,
        SUPER,
        START
    };

    enum InputType {
        KEYBOARD,
        GAMEPAD
    };

    struct ActionKeys
    {
        BE::KB::KeyCode kb;
        BE::GP::KeyCode gp;
    };

    bool isPressed(Actions action_, InputType* inputType_ = nullptr);
    bool isTriggered(Actions action_, InputType* inputType_ = nullptr);
}