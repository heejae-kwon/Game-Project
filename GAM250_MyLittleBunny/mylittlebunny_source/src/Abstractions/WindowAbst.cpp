/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      WindowAbst.cpp
Purpose:        The abstraction for the window library we use (in this case SDL)
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#include <Abstractions/WindowAbst.hpp>
#include <Abstractions/RenderAbst.hpp>
#include <Core/Debugger.hpp>
#include <Utilities/BagOfGoodies.hh>

#include <sstream>
#include <cassert>

BE::WindowAbst::WindowAbst()
    : _windowSize(1280, 720), _windowInstance(nullptr)
{
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
    {
        std::stringstream errMsg;

        errMsg << "SDL could not initialise!SDL_Error: " << SDL_GetError();
        BoG::emergencyMessageLogger(errMsg.str());
        assert(1 == 0);
    }

    // Get current display mode of all displays.
    for (int i = 0; i < SDL_GetNumVideoDisplays(); ++i) {

        int should_be_zero = SDL_GetCurrentDisplayMode(i, &_displayData);

        if (should_be_zero != 0)
        {
            // In case of error...
            SDL_Log("Could not get display mode for video display #%d: %s", i, SDL_GetError());
        }
        else
        {
            // On success, print the current display mode.
            SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz.", i, _displayData.w, _displayData.h, _displayData.refresh_rate);
        }

    }
}

BE::WindowAbst::~WindowAbst()
{
    destroyWindow();
    //Quit SDL subsystems
    SDL_Quit();

}

BE::WindowAbst::windowPtr
BE::WindowAbst::createWindow()
{
    if (_windowInstance == nullptr)
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

        //Create window
        _windowInstance = SDL_CreateWindow("My Little Bunny",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            _windowSize.x, _windowSize.y,
            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        if (_windowInstance == NULL)
        {
            std::stringstream errMsg;

            errMsg << "Window could not be created! SDL_Error: " << SDL_GetError();
            BoG::emergencyMessageLogger(errMsg.str());
            assert(1 == 0);
        }
        else
        {
            _context = SDL_GL_CreateContext(_windowInstance);
            if (_context == NULL)
            {
                std::stringstream errMsg;

                errMsg << "GlContext Failed to create! SDL_Error: " << SDL_GetError();

                BoG::emergencyMessageLogger(errMsg.str());
                assert(1 == 0);
            }
        }
    }
    return _windowInstance;
}

void
BE::WindowAbst::destroyWindow()
{
    if (_context != NULL)
    {
        SDL_GL_DeleteContext(_context);
        _context = NULL;
    }
    if (_windowInstance != nullptr)
    {
        SDL_DestroyWindow(_windowInstance);
        _windowInstance = nullptr;
    }
}

void
BE::WindowAbst::resizeWindow(glm::ivec2 windowSize_)
{
    SDL_SetWindowSize(_windowInstance, windowSize_.x, windowSize_.y);
    _windowSize = windowSize_;
    SDL_SetWindowPosition(_windowInstance, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    RenderAbst::instance()->createOpenGlContext();
}

void BE::WindowAbst::setFullscreen(bool isActive_)
{
    if (isActive_)
    {
        SDL_SetWindowFullscreen(_windowInstance, SDL_WINDOW_FULLSCREEN);
    }
    else
    {
        SDL_SetWindowFullscreen(_windowInstance, false);
    }
}

void BE::WindowAbst::resetWindow()
{
//    SDL_SetWindowFullscreen(_windowInstance, true);
//    SDL_SetWindowSize(_windowInstance, _windowSize.x, _windowSize.y);
    SDL_SetWindowFullscreen(_windowInstance, false);
//    SDL_SetWindowSize(_windowInstance, _windowSize.x, _windowSize.y);
//    RenderAbst::instance()->createOpenGlContext();
    SDL_SetWindowPosition(_windowInstance, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

BE::WindowAbst::windowPtr
BE::WindowAbst::getWindowPtr() const
{
    return _windowInstance;
}

void BE::WindowAbst::flipWindowBuffer()
{
    SDL_GL_SwapWindow(_windowInstance);
}

bool
BE::WindowAbst::getNextEvent(windowEvent* event_)
{
    return SDL_PollEvent(event_) != 0;
}

void
BE::WindowAbst::setMouseState(bool isActive_)
{
    SDL_ShowCursor(isActive_);
}

