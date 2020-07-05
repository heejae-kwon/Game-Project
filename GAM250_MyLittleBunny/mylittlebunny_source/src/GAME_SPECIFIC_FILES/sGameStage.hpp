/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      sGameStage.cpp
Purpose:        Entry point of our program
Language:       C++
Project:        GAM250
Author:         Name : minji.kim, Stuat Sulaski
Email:          seraminji2146@gmail.com
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
#include <GAME_SPECIFIC_FILES\oCamera.hpp>


namespace
{

}

namespace Stage
{
    //!  The sGameStage class. 
    /*!
    The sGameStage class is a Stage.
    It contains its own vector of Actors and its own update function.
    At the moment it does not serve any purpose other than to be used to test out the engine
    */
    class sGameStage : public BE::Stage::BaseStage
    {
    public:
        sGameStage(std::string fileName_ = "");
        ~sGameStage() = default;

        BaseStage*  cpy() final
        {
            return (new sGameStage(fileName));
        }

        void    start(std::string fileName_ = "") final;

        void    resume() final;
        void    pause() final;

        void    update(float dt_) final;

        //start
        void generateStars();


        //startup
        void findStations();
        void findPlanets();

        // update
        void onInput();

		void updateSuperHUD(float dt_);
        void updateNumbers();
		void updateWaveNumbers(LevelSetting& levelSetting);
		void StationAnimation(float dt_);
    protected:
        //
    private:
		void shutdownSounds(void);
		void pauseSounds(void);
		void resumeSounds(void);


        //

    public:
        Player m_player;
//        std::vector<std::vector<BE::Actor*>> _clusters;
        std::vector<std::vector<Planet*>> _clusters;
        std::vector<BE::Actor*> _stations;
        LevelSetting levelsetting;

    protected:
        //
    private:
        //
        bool _mustExit;
        
        float winTimer;
		float loseTimer;
        BE::Component::Gameplay*  _stageConfig;

        BE::Actor*  _player;
        BE::Actor*  _camera;
        BE::Actor*  _1to3Button;
        BE::Actor*  _hud;
        BE::Actor*  _3to5Button;
        BE::Actor*  _superstandHUD;
        BE::Actor*  _xKey;
		BE::Actor*  _feverTime;
		BE::Actor*  _feverEX;
		BE::Actor*  _RocketHelper;
        BE::Actor*  _firstNumber;
        BE::Actor*  _secondNumber;
		BE::Actor*  _waveNumber;
        BE::Actor* _Arrow1;
        BE::Actor* _Arrow2;
		BE::Actor* _rule;
		BE::Actor* _CheatAvailableActor;
		BE::Actor* _GODMODEActor;
		BE::Actor* _GageBar;
		BE::Actor* _GageBound;
		BE::Actor* _GageBunny;
		BE::Actor* _firstPlanet;


        oCamera m_camera;

     	BE::PropManager::propNamePair* sndBackground;
	    BE::PropManager::propNamePair* sndPowerup;
	    BE::PropManager::propNamePair* sndStation;
					bool b_sndStation;
					bool b_restart;

		int increasingParticle;


        bool _startup;
		
		// Cheat Codes
		bool _cheatAvailable;
		bool _godmodeAvailable;
		bool _cheatEnemyDamage;

		bool _explainAkey;
		bool _explainHowtoKill;
        std::string fileName = "";
    };


}
