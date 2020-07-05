/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      WindowAbst.hpp
Purpose:        The abstraction for the window library we use (in this case SDL)
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#pragma once

#include <sdl\SDL.h>
#include <glm/glm.hpp>

#include <memory>

namespace BE
{
    //!  WindowAbst(raction) class. 
    /*!
    WindowAbst is our window abstraction class.
    It serves as an interface of sorts between our engine and the application layer that handles the windowing.
    This keeps things nice and seperate and makes it easier if we ever want to change the application library that we are using.
    This class is used for creating, modifying and destroying our window.
    */
    class WindowAbst
    {
        // All type redefinitions should be at the start of a class
    protected:
        using WindowAbstSmartPtr = std::unique_ptr<WindowAbst>;
    public:
        using windowPtr = SDL_Window*;          // This way if we ever switch out our application library (SDL, SFML, GLFW...) then we won't have to change the window type everywhere.
        using graphicContext = SDL_GLContext;   // This way if we ever switch out our application library (SDL, SFML, GLFW...) then we won't have to change the window type everywhere.
        using windowEvent = SDL_Event;          // This way if we ever switch out our application library (SDL, SFML, GLFW...) then we won't have to change the window type everywhere.
        using displayData = SDL_DisplayMode;

    public:
        static WindowAbst*  instance()  //!< Returns an instance of the class
        {
            static WindowAbstSmartPtr instance(new WindowAbst());
            return instance.get();
        }
        ~WindowAbst();

        windowPtr           createWindow();                         //!< Creates a new window context if _windowInstance is equal to nullptr otherwise it returns _windowInstance.
        void                destroyWindow();                        //!< Destorys the window and sets _windoInstance to nullptr.
        void                resizeWindow(glm::ivec2 windowSize_);
        void                setFullscreen(bool isActive_);
        void                resetWindow();

        windowPtr           getWindowPtr() const;                   //!< Returns _windowInstance.

        void                flipWindowBuffer();                     //!< Flips the windows backbuffer which display a new frame to our window.
        bool                getNextEvent(windowEvent* event_);      //!< Returns true if an event was received and stores it in the event_ variable and false if no event was received

        void                setMouseState(bool isActive_);
    protected:
        //
    private:
        WindowAbst();    //!< ImGuiAbst's constructor is private as it is a Singleton and should only be accessed through the instance() function.

    public:
        glm::ivec2          _windowSize;
    protected:
        //
    private:
        windowPtr           _windowInstance;    /*!< The pointer to our current window*/
        graphicContext      _context;           /*!< The pointer to our window's opengl context used. We store it only to be able to destroy it correctly later*/
        displayData         _displayData;
    };
}