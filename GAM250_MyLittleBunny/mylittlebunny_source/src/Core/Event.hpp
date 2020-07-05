/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      Event.hpp
Purpose:        Event is the core in charge of receiving and passing out events to the rest of the cores
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#pragma once

#include <Core/BaseCore.hpp>
#include <Abstractions/WindowAbst.hpp>

#include <queue>

namespace BE
{
namespace Core
{

    //!  The BunnyEngine's Event Core class. 
    /*!
     The Event class is in charge of handling all the events we receive from the OS.
     It also stores the events it receives in case other parts of the engine need to check what events we have received (ex: ImGuiAbst)
    */
    class Event : public BaseCore
    {
        // All type redefinitions go here
    protected:
        using EventSmartPtr = std::unique_ptr<Event>;
    public:
        using winEventQueue = std::queue<WindowAbst::windowEvent>;

    public:
        static Event*   instance() //!< Returns an instance of the class
        {
            static EventSmartPtr instance(new Event());
            return instance.get();
        }
        ~Event() = default;

        // These 3 should be automatically called every loop
        void            startNewFrame() final;  //!< This should be used to setup anything that is essential before data starts getting processed (ex: clearing the screen buffer)
        void            update(float dt_ = 0.f)        final;  //!< All the data get's processed in this funtrion (There will be a loop in this function for sure)
        void            endOfFrame()    final;  //!< Once all the data processing is done we call the final functions if needed (ex: flipping the screen buffer)

        const bool*     getQuitStateAddr() const;   //!< Returns the address to the _shouldQuit variable so that it's state can be tracked outside of the Event core
        const bool*     getPauseStateAddr() const;   //!< Returns the address to the _shouldPause variable so that it's state can be tracked outside of the Event core
        const bool*     getUnpauseStateAddr() const;   //!< Returns the address to the _shouldPause variable so that it's state can be tracked outside of the Event core
        winEventQueue   getEventStack() const;      //!< Returns a copy of the _eventStack variable

        void            flushKeyboardEvents();  //!< Removes all keypress events from the stack, so that the gameLogic doesn't process a keypress that was not meant for it
        void            flushMouseEvents();  //!< Removes all mouse press events from the stack, so that the gameLogic doesn't process a keypress that was not meant for it

    protected:
        //
    private:
        Event(); //!< Event's constructor is private as it is a Singleton and should only be accessed through the instance() function

    public:
        //
    protected:
        //
    private:
        bool            _shouldQuit;    /*!< Is true if program has received any variant of the QUIT event from the OS or the user*/
        bool            _shouldPause;    /*!< Is true if program has received any variant of the LOST_FOCUS event from the OS or the user*/
        bool            _shouldUnpause;    /*!< Is true if program has received any variant of the GAINED_FOCUS event from the OS or the user*/
        winEventQueue   _eventStack;    /*!< Stores all the events we have received this frame for reference by other parts of the engine if needed*/
    };
}
}
