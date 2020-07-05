#pragma once
/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:    oEnemy.hpp
Purpose:       This file contain the enemy class
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


namespace Stage
{
	class Planet;

	/********************************************************

	Pre-definition of the Objects

	Enemy

	********************************************************/
	
	// Pre-definiton of the Enemy
	class Enemy : public Object
	{
	public:
		Enemy();
		Enemy(BE::Actor* rhs);
		~Enemy();

		void setEnemy(BE::Actor* rhs);
		void InitEnemy(void);
		void setEnemyNum(int i);
		void setPlanetNum(int i);

		void ActiveEnemy(void);
		void InactiveEnemy(void);
		void EnemyUpdate(LevelSetting & LvSetting, float dt);
		void Attack(float dt);
		void Growing(float dt);
		void Damage(LevelSetting & LvSetting, float dt);

		void SetGravity(std::vector<Planet>& planetVector, int size);
		const int GetPlanetNum(void) const ;

		void Movement(LevelSetting& lvSetting, float dt);
		void Update(LevelSetting& LvSetting, float dt);

		int       e_PlanetNum;
		float    e_damageMaxTimer;

	private:
		int		e_Growth;
		int       e_animConnection;
		// Timer
		float	e_LifeTimer;
		float	e_deadTimer;
		float	e_damageTimer;
        bool    particleSet = false;

		Planet* owner_Planet;
		BE::HBVec2 movDir;

	 BE::PropManager::propNamePair* sndHit;

	};

}
