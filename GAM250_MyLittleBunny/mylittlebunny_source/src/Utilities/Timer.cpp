/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      Timer.cpp
Purpose:        Timer functions used for all timing in the engine
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#include <Utilities\Timer.hpp>
#include <Utilities/BagOfGoodies.hh>

BE::Timer::Timer()
    : _isPaused(false),
      _startTime(BE::BoG::getTick()),
      _currentUpdate(BE::BoG::getTick()),
      _currentPauseTime(0),
      _totalPauseTime(0)
{

}

void
BE::Timer::start()
{
    if (_isPaused == true)
    {
        updatePauseTime();
        _totalPauseTime += _currentPauseTime;
        _currentPauseTime = 0;
        _currentUpdate = BE::BoG::getTick();

        _isPaused = false;
    }
}

void
BE::Timer::pause()
{
    _isPaused = true;
    _currentPauseTime = BE::BoG::getTick() - _currentUpdate;
}

void
BE::Timer::reset()
{
    uint32_t tick = BE::BoG::getTick();

    _startTime = tick;
    _currentUpdate = tick;
    _currentPauseTime = 0;
    _totalPauseTime = 0;
}

void
BE::Timer::update()
{
    if (_isPaused == false)
    {
        _currentUpdate = BE::BoG::getTick();
    }
}

bool
BE::Timer::isPaused()
{
    return _isPaused;
}

void
BE::Timer::updatePauseTime()
{
    _currentPauseTime = BE::BoG::getTick() - _currentUpdate;
}

float
BE::Timer::getSecSinceUpdate()
{
    if (_isPaused == true)
    {
        updatePauseTime();
    }

    uint32_t tick = BE::BoG::getTick();
    uint32_t time = (tick - _currentPauseTime) - _currentUpdate;
    float newTime = time / 1000.0f;

    return (newTime); // We get the current time and then substract the old time and the pause time and then divide it to get a second.
}

float
BE::Timer::getSecSinceStart()
{
    if (_isPaused == true)
    {
        updatePauseTime();
    }

    uint32_t tick = BE::BoG::getTick();
    uint32_t time = (tick - (_totalPauseTime + _currentPauseTime)) - _startTime;
    float newTime = time / 1000.0f;

    return (newTime);
}

uint32_t
BE::Timer::getMiliSecSinceUpdate()
{
    if (_isPaused == true)
    {
        updatePauseTime();
    }

    uint32_t tick = BE::BoG::getTick();
    uint32_t time = (tick - _currentPauseTime) - _currentUpdate;

    return (time); // We get the current time and then substract the old time and the pause time and then divide it to get a second.
}

uint32_t
BE::Timer::getMiliSecSinceStart()
{
    if (_isPaused == true)
    {
        updatePauseTime();
    }

    uint32_t tick = BE::BoG::getTick();
    uint32_t time = (tick - (_totalPauseTime + _currentPauseTime)) - _startTime;

    return (time);
}

