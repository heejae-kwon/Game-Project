/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      BaseCore.cpp
Purpose:        BaseCore is the interface used by all other cores
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#include <Core/BaseCore.hpp>
#include <Core/Debugger.hpp>

BE::Core::BaseCore::BaseCore(bool logExecTime_) :
    _coreStringId("BaseCore"),
    _logExecTime(logExecTime_),
    _performanceTimer(TimerManager::instance()->createTimer()),
    _currExecTimeMs(0),
    _execTimeMs(0),
//    _actorVec({}),
    _actorOffset({ 0 })
{
}

void
BE::Core::BaseCore::startNewFrame()
{
    startExecTimeLog();
}

void
BE::Core::BaseCore::update(float /*dt_*/)
{
    startExecTimeLog();
}

void
BE::Core::BaseCore::endOfFrame()
{
    startExecTimeLog();

}

void
BE::Core::BaseCore::startExecTimeLog()
{
    if (this->_logExecTime == true)
    {
        _performanceTimer->update();
    }
}

void
BE::Core::BaseCore::updateExecTime()
{
    if (_logExecTime == true)
    {
        _currExecTimeMs += _performanceTimer->getMiliSecSinceUpdate();
    }
}

void
BE::Core::BaseCore::flushExecTimeLog()
{
    if (_logExecTime == true)
    {
//        Debugger::instance()->AddLog("[LOG][%s] Execution time %d/ms\n", _coreStringId.c_str(), _execTimeMs);
        _execTimeMs = _currExecTimeMs;
        _currExecTimeMs = 0;
    }
}

void
BE::Core::BaseCore::registerActor(Actor* actor_)
{
//    Debugger::instance()->AddLog("[LOG][%s][REGISTER] Actor [%s]\n", _coreStringId.c_str(), actor_->_name.c_str());

    _actorVec.push_back(actor_);
}

void
BE::Core::BaseCore::unregisterActor(Actor* actor_)
{
    for (size_t i = 0; i < _actorVec.size(); ++i)
    {
        if (_actorVec[i] == actor_)
        {
//            Debugger::instance()->AddLog("[LOG][%s][UNREGISTER] Actor [%s]\n", _coreStringId.c_str(), actor_->_name.c_str());

            if (_actorVec[i] != _actorVec.back())
            {
                std::swap(_actorVec[i], _actorVec.back());    // We move the pointer to the end of the vector
            }
            _actorVec.pop_back();                          // and then remove it from the vector
            return;
        }
    }
}

std::vector<BE::Actor*>&
BE::Core::BaseCore::getRegisteredActors()
{
    return _actorVec;
}

std::vector<BE::Actor*>::iterator
BE::Core::BaseCore::getActiveRegisteredActors()
{
    return _actorVec.begin() + _actorOffset.top();
}

uint32_t
BE::Core::BaseCore::getActiveActorOffset()
{
    return _actorOffset.top();
}

uint32_t
BE::Core::BaseCore::getExecTime()
{
    return _execTimeMs;
}

void
BE::Core::BaseCore::pushNewOffset(bool keepCurrentActors_)
{
    if (keepCurrentActors_ == true)
    {
        _actorOffset.push(_actorOffset.top());
    }
    else
    {
        _actorOffset.push(static_cast<uint32_t>(_actorVec.size()));
    }
}

void
BE::Core::BaseCore::popPreviousOffset()
{
    if (_actorOffset.size() > 0)
    {
        _actorOffset.pop();
    }
}
