/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      TimerManager.hh
Purpose:        Factory that creates timer that can be used in our engine
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#pragma once

#include <Utilities/Timer.hpp>

#include <vector>
#include <memory> //smart_ptr

namespace BE
{
    //!  TimerManager class. 
    /*!
     The TimeManager class is a singleton that can be used to manage N number of Timer objects.
     It's main goal is to have a simple way of controlling these timers that are used extensively in "Cores" for example (Animation, Physics...)
     The timers should be stored in a preallocated list
    */

    class TimerManager
    {
        // All type redefinitions go here
    protected:
        using TimerManagerSmartPtr = std::unique_ptr<TimerManager>;
        using TimerSmartPtr = std::unique_ptr<Timer>;

    public:
        static TimerManager*        instance()  //!< Returns an instance of the class
        {
            static TimerManagerSmartPtr instance(new TimerManager());
            return instance.get();
        }
        ~TimerManager() = default;

        Timer*                      createTimer();      //!< Returns a shared pointer to a Timer object
        void                        destroyTimers();    //!< Empties the list and since all the elements are shared pointers they don't need to be deleted

        void                        startAll(); //!< Starts all existing timers that are stored in the vector container
        void                        pauseAll(); //!< Pauses all existing timers that are stored in the vector container
        void                        resetAll(); //!< Starts all existing timers that are stored in the vector container
    protected:
        //
    private:
        TimerManager() = default;   //!< TimerManager's constructor is private as it is a Singleton and should only be accessed through the instance() function

    public:
        //
    protected:
        //
    private:
        std::vector<TimerSmartPtr>  _timerVec;  /*!< The vector container that stores the unique pointers to all active timers in our game */
    };
}
