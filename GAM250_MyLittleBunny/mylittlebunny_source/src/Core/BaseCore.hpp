/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      BaseCore.hpp
Purpose:        BaseCore is the interface used by all other cores
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#pragma once

#include <Utilities\TimerManager.hpp>
#include <Actor.hpp>

#include <vector>
#include <stack>

namespace BE
{
namespace Core
{

    //!  The BunnyEngine's base Core class. 
    /*!
     The Core class is the base class for all the core parts of the Bunny Engine.
     Each one of the cores is a part of the engine that processes data (Actors or Events) every frame (AI, Physics, Rendering, Audio).
     This is where we have all the functionalities that must be available to all the cores of our engine.
     ex: performance tracking, error logging
    */
    class BaseCore
    {
    public:
        BaseCore(bool logExecTime_ = true);
        ~BaseCore() = default;

        virtual void    startNewFrame();    //!< This should be used to setup anything that is essential before data starts getting processed (ex: clearing the screen buffer).
        virtual void    update(float dt_ = 0.f);           //!< All the data get's processed in this funtrion (There will be a loop in this function for sure).
        virtual void    endOfFrame();       //!< Once all the data processing is done we call the final functions if needed (ex: flipping the screen buffer).

        void            startExecTimeLog(); //!< When you call this function the timer is reset and we stat recording exec time from the moment you call it.
        void            updateExecTime();   //!< Is called at the end of the three main functions, adds up the execution time of the core.
        void            flushExecTimeLog(); //!< Send exec time to logger and resets all variables related to logging to their original state.
        uint32_t        getExecTime();      //!< Returns the execution time of the previous frame in milliseconds

        virtual void    registerActor(Actor* actor_);       //!< Adds an actor to the core's _actorStack
        virtual void    unregisterActor(Actor* actor_);     //!< Remove an actor from the core's _actorStack

        std::vector<Actor*>&            getRegisteredActors();        //!< Returns the vector of actor pointers that are registered to this core
        std::vector<Actor*>::iterator   getActiveRegisteredActors();  //!< Returns the vector of actor pointers that are registered to this core and active
        uint32_t                        getActiveActorOffset();         //!< Returns a value that represents the number of actors that are considered as inactif

        /** Function used when stacking events.
        * Used when we stack stages, we store the number of actors currently active and then use that value as an offset
        * this way we know which actors are active and should be processed by the core.
        * This is used so that when we stack a stage (pause stage for example) the actors of the stages in the background still exist in memory but are not processed.
        * It is possible to mess around with this so that even when we push a new stage the actors from the previous stage are still processed.
        * ex: We make the pause stage the current stage but we would still like the the actors from the previous stage to still be drawn
        * so we get a bool as a param and if it is set to false, in the case of the draw core, it will not hide away the previous actors when pushNewOffset() is called.
        */
        void            pushNewOffset(bool keepCurrentActors_);
        void            popPreviousOffset();
    protected:
        //
    private:
        //

    public:
        //
    protected:
        std::string             _coreStringId;          /*!< A human readable string of the core's name */
        bool                    _logExecTime;           /*!< Should the core log it's execution time */
        Timer*                  _performanceTimer;      /*!< The timer used to calculate the execution time for each Core system of the engine */
        uint32_t                _currExecTimeMs;        /*!< The current accumulated execution time (accumulation of startNewFrame(), update() and endOfFrame() */
        uint32_t                _execTimeMs;            /*!< The accumulated execution time of the previous frame */

        std::vector<Actor*>     _actorVec;             /*!< List of actors that are registered with this core */
        std::stack<uint32_t>    _actorOffset;          /*!< This let's us limit what actors are processed by the core, this is used when stacking stages */
    private:
        //
    };
}
}
