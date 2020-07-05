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

#include <Core/Event.hpp>
#include <Core/Debugger.hpp> // TEMPORARY
#include <EventTypes.hpp>
#include <Utilities/TimerManager.hpp>
#include <WIP/Keyboard.hpp>
#include <WIP/Mouse.hpp>
#include <WIP/Gamepad.hpp>

BE::Core::Event::Event()
    : BaseCore(), _shouldQuit(false)
{
    BaseCore::_coreStringId = "Event";
}

void
BE::Core::Event::startNewFrame()
{
    BaseCore::startNewFrame();  // You should ALWAYSE call the Core's base functions as we are extending the base functions
    {
        static bool gamePaused = false;
        WindowAbst::windowEvent event;
        while (WindowAbst::instance()->getNextEvent(&event))
        {
            _eventStack.push(event); // We add event to the stack so that it may be used later in the frame

            if (event.type == BE_WINDOWEVENT)
            {
                switch (event.window.event)
                {
                case BE_WINDOWEVENT_CLOSE:
                {
                    _shouldQuit = true;
                } break;
                case BE_WINDOWEVENT_MOVED:
                {
                    Core::Debugger::instance()->AddLog("Game paused\n");
                    TimerManager::instance()->pauseAll();
                    gamePaused = true;
                } break;

                case BE_WINDOWEVENT_FOCUS_LOST:
                {
                    _shouldPause = true;
                    _shouldUnpause = false;
                } break;
                case BE_WINDOWEVENT_FOCUS_GAINED:
                {
                    _shouldUnpause = true;
                    _shouldPause = false;
                } break;
                }
            }

            if (gamePaused == true)
            {
                TimerManager::instance()->startAll();
                gamePaused = false;
            }
        }
    }
    BaseCore::updateExecTime();
}

void
BE::Core::Event::update(float /*dt_*/)
{
    BaseCore::update();  // You should ALWAYSE call the Core's base functions as we are extending the base functions
    {
        winEventQueue events = getEventStack();
        while (events.size() > 0)
        {
            switch (events.front().type)
            {
            case (BE_KEYDOWN):
                Input::Keyboard::instance()->turnonKey(events.front().key.keysym.sym);
                break;
            case (BE_KEYUP):
                Input::Keyboard::instance()->turnoffKey(events.front().key.keysym.sym);
                break;
            case (BE_MOUSEBUTTONDOWN):
                Input::Mouse::instance()->turnonKey(events.front().button.button);
                break;
            case (BE_MOUSEBUTTONUP):
                Input::Mouse::instance()->turnoffKey(events.front().button.button);
                break;
            case (BE_MOUSEMOTION):
                Input::Mouse::instance()->setMousePosition(events.front().motion.x, events.front().motion.y);
                break;
            case (SDL_MOUSEWHEEL):
                Input::Mouse::instance()->nbrOfMouseScrolls += events.front().wheel.y;
                break;
            }
            events.pop();
        }
        Input::Gamepad::instance()->update();
    }
    BaseCore::updateExecTime();
}

void
BE::Core::Event::endOfFrame()
{
    BaseCore::endOfFrame();  // You should ALWAYSE call the Core's base functions as we are extending the base functions
    {
        Input::Keyboard::instance()->clearTrigger();
        Input::Gamepad::instance()->clearTrigger();
        Input::Mouse::instance()->clearTrigger();
        Input::Mouse::instance()->nbrOfMouseScrolls = 0;
        while (!_eventStack.empty())
        {
            _eventStack.pop();
        }
    }
    BaseCore::updateExecTime();
    BaseCore::flushExecTimeLog();
}

const bool *
BE::Core::Event::getQuitStateAddr() const
{
    return &(_shouldQuit);
}

const bool *
BE::Core::Event::getPauseStateAddr() const
{
    return &(_shouldPause);
}

const bool *
BE::Core::Event::getUnpauseStateAddr() const
{
    return &(_shouldUnpause);
}

BE::Core::Event::winEventQueue
BE::Core::Event::getEventStack() const
{
    return _eventStack;
}

void
BE::Core::Event::flushKeyboardEvents()
{
    winEventQueue newStack;

    while (_eventStack.size() > 0)
    {
        if (_eventStack.front().type != BE_KEYDOWN && _eventStack.front().type != BE_KEYUP)
        {
            newStack.push(_eventStack.front());
        }
        _eventStack.pop();
    }
    _eventStack = newStack;
}

void BE::Core::Event::flushMouseEvents()
{
    winEventQueue newStack;

    while (_eventStack.size() > 0)
    {
        if (_eventStack.front().type != BE_MOUSEBUTTONDOWN && _eventStack.front().type != BE_MOUSEBUTTONDOWN && _eventStack.front().type != SDL_MOUSEWHEEL)
        {
            newStack.push(_eventStack.front());
        }
        _eventStack.pop();
    }
    _eventStack = newStack;
}
