/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      sRocketDestinationSelect.hpp
Purpose:        A stage that is used when selecting which planet to fly to in the game menu
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#pragma once

#include <BaseStage.hpp>
#include <GAME_SPECIFIC_FILES/sLegacyMenu.hpp>
#include <Utilities/TimerManager.hpp>
#include <WIP/Keyboard.hpp>
#include <GAME_SPECIFIC_FILES\LevelSetting.hpp>
#include <GAME_SPECIFIC_FILES\oPlayer.hpp>
#include <GAME_SPECIFIC_FILES\oEnemy.hpp>
#include <GAME_SPECIFIC_FILES\oPlanet.hpp>
#include <GAME_SPECIFIC_FILES\oCamera.hpp>


namespace
{

}

namespace Stage
{
    //!  The sRocketDestMenu class. 
    /*!
    The sRocketDestMenu class is a Stage.
    It contains its own vector of Actors and its own update function.
    At the moment it does not serve any purpose other than to be used to test out the engine
    */
    class sRocketDestMenu : public BE::Stage::BaseStage
    {
    public:
        sRocketDestMenu(sLegacyMenu *stage_ = nullptr);
        ~sRocketDestMenu() = default;

        BaseStage*  cpy() final
        {
            return (new sRocketDestMenu(_previousStage));
        }

        void    start(std::string fileName_ = "") final;

        void    resume() final;
        void    pause() final;

        void    update(float dt_) final;


        void onInput(float dt_);

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
        bool _mustExit;

        BE::Actor*  _player;

        Player      *m_player;

        sLegacyMenu *_previousStage;
        size_t _selectedStation;

        size_t currentPlanetIndex;
    };


}
