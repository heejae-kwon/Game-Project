#pragma once
/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:    sHowtoPlay.hpp
Purpose:       This file contain the How to play stage class.
Can be used C style with static functions or C++ with methods.
Language:     C++
Project:         GAM250
Author:         Name : Jihwan Oh, Wonjae Jung(Gamepad)
Email:            dkdkdkdudrn@gmail.com, wonjae0925@gmail.com
date:			   2017.06.16
----------------------------------------------------------------------------*/
#include <BunnyEngine.hpp>
#include <BaseStage.hpp>
#include <Utilities/TimerManager.hpp>
#include <GAME_SPECIFIC_FILES\oPlayer.hpp>

namespace Stage
{
    //!  The sHowtoPlay class. 
    /*!
     The sHowtoPlay class is a Stage.
     It contains its own vector of Actors and its own update function.
     It is used as a popup when trying to do a destructive action (quitting game, returning to menu)
     NOTE: Currently, there is no way of knowing what the "result" of the ActionConfirm was. So that will need to be adressed
    */
    class sHowtoPlay : public BE::Stage::BaseStage
    {
    public:
        sHowtoPlay();
        ~sHowtoPlay() = default;

        BaseStage*  cpy() final
        {
            return (new sHowtoPlay());
        }

        void    start(std::string fileName_ = "") final;

        void    resume() final;
        void    pause() final;

        void    update(float dt_) final;


		enum InPutState2
		{
			KEYBOARD, GAMEPAD
		};
    protected:
        //
    private:
        //
		void movementControl();

    public:
        //
    protected:
        //
    private:
        //
		BE::Actor*  _infoSign;
		BE::Actor*  _infoSignGamePad;
	


		InPutState2 m_inputstate;
    };
}