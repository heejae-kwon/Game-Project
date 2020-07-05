#pragma once
/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:    LevelSetting.hpp
Purpose:       States of the each stages which contain the informations
					   such as number of objects.
Can be used C style with static functions or C++ with methods.
Language:     C++
Project:         GAM250
Author:         Name : Jihwan Oh
Email:            dkdkdkdudrn@gmail.com
date:			   2017.06.16
----------------------------------------------------------------------------*/
#include <Actor.hpp>
#include <memory>

#include <BaseStage.hpp>
#include <Utilities/TimerManager.hpp>
#include <WIP/Keyboard.hpp>
#include <WIP\HBRandom.hpp>
#include <Components/Components.hh>
#include <GAME_SPECIFIC_FILES\Objects.hpp>
#include <GAME_SPECIFIC_FILES\oPlanet.hpp>
#include <GAME_SPECIFIC_FILES\oEnemy.hpp>
#include <GAME_SPECIFIC_FILES\oPlayer.hpp>



namespace Stage
{
	/****************************************

	Class LevelSetting
	for the Basic Setting Value or Objects	
	of each Level 

	*****************************************/
	class LevelSetting
	{
	public:
		LevelSetting();
		~LevelSetting();

		void GenerateEnemyList(std::vector<std::unique_ptr<BE::Actor>>& ActorList);
		void GenerateHPbar(std::vector<std::unique_ptr<BE::Actor>>& ActorList);
		void SetPlanetList(std::vector<std::unique_ptr<BE::Actor>>& ActorList);
		void SetEnemyList(std::vector<std::unique_ptr<BE::Actor>>& ActorList);

		void GenerateEnemy(float term, float dt);
		
		//float m_dt = 0;

		// Definition variables in Level2
        int start_enemyNum = 0;
        int step_enemyNum = 0;
        int numberOfRounds = 0;
        int max_enemyNum = 0;
		 int max_enemyHealth = 10;
		 int max_planetNum = 0;
		// Global in Stage namespace
		int playerNum = 1;// the number of the player
		int planetNum = 1;// the number of the planet
		int enemyNum = 1; // the number of the enemy

		int deadEnemyNum = 0;
		int deadPlanetNum = 0;
		int powerupCount = 0;

		float   generateTime = 0;
		int     generateNum = 0;

		int waveConditionNum = 0;
		int enemyNum_perWave = 0;
		float waveBreakTime = 0;

		float waveAlarmTime = 0;

		Player* player;
		//BE::Actor* player;
		std::vector<Planet> planetVector;

		std::vector<Enemy> enemyVector;
		BE::Actor*  _waveAlarm;

//		bool generateDone = false;


	private:
		
	};

}
