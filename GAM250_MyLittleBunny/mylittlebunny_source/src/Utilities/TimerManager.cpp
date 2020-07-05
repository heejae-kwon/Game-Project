/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      TimerManager.cpp
Purpose:        Factory that creates timer that can be used in our engine
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#include <Utilities/TimerManager.hpp>

BE::Timer*
BE::TimerManager::createTimer()
{
    TimerSmartPtr newTimer = std::unique_ptr<Timer>(new Timer());
    _timerVec.push_back(std::move(newTimer));

    return (_timerVec.back().get());
}

void
BE::TimerManager::destroyTimers()
{
    while (_timerVec.size() > 0)
    {
        _timerVec.pop_back();
    }
}

void
BE::TimerManager::startAll()
{
    for (auto& timer : _timerVec)
    {
        timer->start();
    }
}

void
BE::TimerManager::pauseAll()
{
    for (auto& timer : _timerVec)
    {
        timer->pause();
    }
}

void BE::TimerManager::resetAll()
{
    for (auto& timer : _timerVec)
    {
        timer->reset();
    }
}
