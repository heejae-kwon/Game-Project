/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      inputAbstraction.cpp
Purpose:        Input abstraction to simplify keyboard and gamepad input checking
Language:       C++
Project:        GAM200
Author:         Name : Stuat Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#include "inputAbstraction.hh"

static Input::ActionKeys
actionToKey(Input::Actions action_)
{
    Input::ActionKeys retVal;

    switch (action_)
    {
    case(Input::Actions::LEFT):
    {
        retVal.kb = BE::KB::KEY_LEFT;
        retVal.gp = BE::GP::BUTTON_DPAD_LEFT;
    } break;
    case(Input::Actions::RIGHT):
    {
        retVal.kb = BE::KB::KEY_RIGHT;
        retVal.gp = BE::GP::BUTTON_DPAD_RIGHT;
    } break;
    case(Input::Actions::UP):
    {
        retVal.kb = BE::KB::KEY_UP;
        retVal.gp = BE::GP::BUTTON_DPAD_UP;
    } break;
    case(Input::Actions::DOWN):
    {
        retVal.kb = BE::KB::KEY_DOWN;
        retVal.gp = BE::GP::BUTTON_DPAD_DOWN;
    } break;
    case(Input::Actions::JUMP):
    {
        retVal.kb = BE::KB::KEY_SPACE;
        retVal.gp = BE::GP::BUTTON_B;
    } break;
    case(Input::Actions::POS_ACTION):
    {
        retVal.kb = BE::KB::KEY_s;
        retVal.gp = BE::GP::BUTTON_X;
    } break;
    case(Input::Actions::NEG_ACTION):
    {
        retVal.kb = BE::KB::KEY_SPACE;
        retVal.gp = BE::GP::BUTTON_B;
    } break;
    case(Input::Actions::SUPER):
    {
        retVal.kb = BE::KB::KEY_a;
        retVal.gp = BE::GP::BUTTON_A;
    } break;
    case(Input::Actions::START):
    {
        retVal.kb = BE::KB::KEY_ESCAPE;
        retVal.gp = BE::GP::BUTTON_START;
    } break;
    default:
    {
        retVal.kb = BE::KB::KEY_UNKNOWN;
        retVal.gp = BE::GP::BUTTON_UNKNOWN;
    } break;

    }

    return retVal;
}

bool
Input::isPressed(Actions action_, InputType* inputType_)
{
    ActionKeys keys = actionToKey(action_);
    if (BE::Input::Keyboard::instance()->IsPressed(keys.kb))
    {
        if (inputType_ != nullptr)
        {
            *inputType_ = KEYBOARD;
        }
        return true;
    }
    else if (BE::Input::Gamepad::instance()->IsPressed(keys.gp))
    {
        if (inputType_ != nullptr)
        {
            *inputType_ = GAMEPAD;
        }
        return true;
    }
    return false;
}

bool
Input::isTriggered(Actions action_, InputType* inputType_)
{
    ActionKeys keys = actionToKey(action_);
    if (BE::Input::Keyboard::instance()->IsTriggered(keys.kb))
    {
        if (inputType_ != nullptr)
        {
            *inputType_ = KEYBOARD;
        }
        return true;
    }
    else if (BE::Input::Gamepad::instance()->IsTriggered(keys.gp))
    {
        if (inputType_ != nullptr)
        {
            *inputType_ = GAMEPAD;
        }
        return true;
    }
    return false;
}
