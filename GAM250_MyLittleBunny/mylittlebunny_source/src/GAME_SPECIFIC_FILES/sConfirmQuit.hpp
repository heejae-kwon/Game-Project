#pragma once
/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:    sConfirmQuit.hpp
Purpose:       This file contain the Confirm Quit's stage class.
such as number of objects.
Can be used C style with static functions or C++ with methods.
Language:     C++
Project:         GAM250
Author:         Name : Jihwan Oh
Email:            dkdkdkdudrn@gmail.com
date:			   2017.06.16
----------------------------------------------------------------------------*/
#include <BunnyEngine.hpp>
#include <BaseStage.hpp>
#include <Utilities/TimerManager.hpp>

namespace Stage
{
    //!  The sConfirmQuit class. 
    /*!
     The sConfirmQuit class is a Stage.
     It contains its own vector of Actors and its own update function.
     It is used as a popup when trying to do a destructive action (quitting game, returning to menu)
     NOTE: Currently, there is no way of knowing what the "result" of the ActionConfirm was. So that will need to be adressed
    */
    class sConfirmQuit : public BE::Stage::BaseStage
    {
    public:
        sConfirmQuit();
        ~sConfirmQuit() = default;

        BaseStage*  cpy() final
        {
            return (new sConfirmQuit());
        }

        void    start(std::string fileName_ = "") final;

        void    resume() final;
        void    pause() final;

        void    update(float dt_) final;
    protected:
        //
    private:
        //

    public:
        //
    protected:
        //
    private:
        float       _elapsedTime;   /*!< [TEMPORARY] Used for testing purposes, to check if state stacking works.*/
    };
}