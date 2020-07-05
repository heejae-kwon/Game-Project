/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      sLegacyMenu.cpp
Purpose:        Create class for the menu.
Language:       C++
Project:        GAM250
Author:         Name : wonjae.jung
Email:          wonjae0925@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/
#pragma once

#include <BaseStage.hpp>
#include <Utilities/TimerManager.hpp>

#include <GAME_SPECIFIC_FILES\LevelSetting.hpp>
#include <GAME_SPECIFIC_FILES\oPlayer.hpp>
#include <GAME_SPECIFIC_FILES\oEnemy.hpp>
#include <GAME_SPECIFIC_FILES\oPlanet.hpp>

namespace Stage
{
    //!  The sLegacyMenu class. 
    /*!
     The sLegacyMenu class is a Stage.
     It's main goal is to illustrate how to create scenes with the new engine.
    */
    class sLegacyMenu : public BE::Stage::BaseStage
    {
    public:
        sLegacyMenu();
        ~sLegacyMenu() = default;

        BaseStage*  cpy() final
        {
            return (new sLegacyMenu());
        }

        void    start(std::string fileName_ = "") final;

        void    resume() final;
        void    pause() final;

        void    update(float dt_) final;
    protected:
        //
    private:
        //startup
        void findStations();
        void findPlanets();
								
								void shutdownSounds(void);
								void pauseSounds(void);
								void resumeSounds(void);

    public:
        Player m_player;
        std::vector<std::vector<BE::Actor*>> _clusters;
        std::vector<BE::Actor*> _stations;

    protected:
        //
    private:
        bool _startup;

        BE::Actor*  _starCursor;
        BE::Actor*  _teamLogo;
		BE::Actor*  _backStar;
		BE::Actor*  _camera;
		BE::Actor*  _player;
        BE::Actor*  _tutorialSign;
		BE::Actor*  _startSign;
		BE::Actor*  _creditSign;
        BE::Actor*  _infoSign;
		BE::Actor*  _infoSignGamePad;
		BE::Actor*  _startSignButtonA;
		BE::Actor*  _creditSignButtonA;

		BE::Actor* _mainPlanet;
		BE::Actor* _startPlanet;
		BE::Actor* _optionPlanet;
		BE::Actor* _creditPlanet;
		BE::Actor* _exitPlanet;

		BE::Component::Display* _mainPlanetDisplay;

		BE::PropManager::propNamePair* _menuMusicStart;
		bool b_menuMusicStart;
		bool b_menuMusicRestart;
		bool b_sndPause;

	    BE::PropManager::propNamePair* sndStation;
					bool b_sndStation;


		LevelSetting MenuLvSetting;

		int buttonNum;
		int increasingParticle; 
    };
}

