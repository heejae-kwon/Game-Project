#pragma once
/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:    oPlanet.hpp
Purpose:       This file contain the planet class
Can be used C style with static functions or C++ with methods.
Language:     C++
Project:         GAM250
Author:         Name : Jihwan Oh
Email:            dkdkdkdudrn@gmail.com
date:			   2017.06.16
----------------------------------------------------------------------------*/
#include <BaseStage.hpp>
#include <Utilities/TimerManager.hpp>
#include <WIP/Keyboard.hpp>

#include <GAME_SPECIFIC_FILES/Objects.hpp>
namespace
{
	

}

namespace Stage
{
	
	/********************************************************

	Pre-definition of the Objects

	Planet

	********************************************************/
	// Pre-definiton of the Enemy
	class Planet : public Object
	{
	public:
		Planet();
		Planet(BE::Actor* rhs);
		~Planet();

		void setPlanet(BE::Actor* rhs);
		void setPlanetNum(int i);
		void ActivePlanet(void);
		void InactivPlanet(void);
		void PlanetUpdate(LevelSetting& LvSetting);
		//BE::Actor * GetPlanet(void);


		void Update(LevelSetting& LvSetting, float dt);

		void ShakeControl(float dt);
		void SetHPbar(void);

		bool Shaking = false;
		bool immortal = false;
		float ShakingTimer = 0;
		float max_health;
		bool isAttacked;
		int enemyNum;

		float healthRatio;
		BE::Actor* hpBar;
		BE::Component::Transform* barTransform;
	private:
	};
}
