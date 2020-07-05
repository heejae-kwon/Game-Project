/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      BagOfGoodies.hh
Purpose:        A collection of useful functions that can be used anywhere in the engine
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#pragma once

#include <sdl\SDL.h>
#include <glm/glm.hpp>

#include <string>

namespace BE
{
    namespace BoG
    {
        inline uint32_t getTick() { return SDL_GetTicks(); }    //!< Function that returns the current tick/time

        void    emergencyMessageLogger(std::string errorMsg_);  //!< This is our emergency message logger for when something goes wrong even before our Debugger Core has the chance to get up and running

        glm::vec4    getMouseCoord();
    }
}