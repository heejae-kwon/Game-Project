/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      Timer.hh
Purpose:        Timer functions used for all timing in the engine
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#pragma once

#include <cstdint> //uint32_t
#include <memory>

namespace BE
{
    //!  Timer class. 
    /*!
     The Timer class is a simple object that can be used to calculat elapsed time.
    */

    class __declspec(dllexport)  Timer
    {
        friend class TimerManager;

    public:
        ~Timer() = default;

        void            start();            //!< Starts the timer if it was paused and does nothing if it wasn't.
        void            pause();            //!< Pauses the timer when called.
        void            reset();            //!< Resets all the member variables to their initial values. As it's name implies we reset the timer.
        void            update();           //!< If the timer isn't paused then we update the _lastUpdate and _currentUpdate variables.
        bool            isPaused();         //!< Returns true if the timer is currently paused and false if not.

        void            updatePauseTime();

        float           getSecSinceUpdate();        //!< Returns the amount of seconds that have elapsed since the previous update() call.
        float           getSecSinceStart();         //!< Returns the amount of seconds that have elapsed since the previous reset() call.
        uint32_t        getMiliSecSinceUpdate();    //!< Returns the amount of milliseconds that have elapsed since the previous update() call.
        uint32_t        getMiliSecSinceStart();     //!< Returns the amount of milliseconds that have elapsed since the previous reset() call.

    protected:
        Timer();                        //!< Timer's constructor is private as I do not wish for the user to instantiate Timers willy nilly
    private:
        //

    public:
        //
    protected:
        //
    private:
        bool            _isPaused;          /*!< Value set to true when the timer has been paused. */

        uint32_t        _startTime;         /*!< Time since initialization or since we last called reset(). */
        uint32_t        _currentUpdate;     /*!< The value of the previous update. */
        uint32_t        _currentPauseTime;  /*!< Amount of time since pause was started. */
        uint32_t        _totalPauseTime;    /*!< Accumulated time of pause. Is reset to 0 when reset() is called. */
    };
}
