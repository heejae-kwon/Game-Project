/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      sTestLevel.hpp
Purpose:        This file contain the Options.
Can be used C style with static functions or C++ with methods.
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/
#pragma once

#include <BaseStage.hpp>
#include <Utilities/TimerManager.hpp>
#include <WIP/Keyboard.hpp>
#include <GAME_SPECIFIC_FILES\LevelSetting.hpp>
#include <GAME_SPECIFIC_FILES\oPlayer.hpp>
#include <GAME_SPECIFIC_FILES\oEnemy.hpp>
#include <GAME_SPECIFIC_FILES\oPlanet.hpp>


namespace
{

}

namespace Stage
{
    //!  The sTestLevel class. 
    /*!
     The sTestLevel class is a Stage.
     It contains its own vector of Actors and its own update function.
     At the moment it does not serve any purpose other than to be used to test out the engine
    */
	class sTestLevel : public BE::Stage::BaseStage
    {
    public:
        sTestLevel();
        ~sTestLevel() = default;

        BaseStage*  cpy() final
        {
            return (new sTestLevel());
        }

        void    start(std::string fileName_ = "") final;

        void    resume() final;
        void    pause() final;

        void    update(float dt_) final;
		void		WinCondition(LevelSetting levelSetting);
		void    LoseCondition(LevelSetting levelSetting);


	protected:
        //
    private:
        //

    public:
        //
    protected:
        //
    private:
        //
		BE::Actor*  _player;
		BE::Actor* _camera;
		Player m_player;
		
		LevelSetting LevelSetting1;

	};


}
