#pragma once
/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:    Objects.hpp
Purpose:       This file contain the Object class, which is basis for
					   other planets and enemies.
such as number of objects.
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
#include <Components/Components.hh>




namespace
{
	// Definition variables in Level2
	const int max_enemyNum = 10;

	// type of units
	const int type_PLAYER = 0;
	const int type_ENEMY = 1;
	const int type_PLANET = 2;
	// condition of units
	const int cond_WORKING = 0;
	const int cond_DEAD = 1;
	const int cond_PROTECTED = 2; // for plant

	// condition of player
	const int cond_plFlying = 3;

	// condition of planet
	const int cond_pBROKEN = 3;
	const int cond_pBROKEN2 = 4;

	// condition for enemy
	const int cond_eFlying  = 3;
	const int cond_eFixed   = 4;
	
	// Global in Stage namespace
	int	 playerNum = 1;// the number of the player
	int	 planetNum = 1;// the number of the planet
	int    enemyNum = 1; // the number of the enemy

	int     deadEnemyNum = 0;
}

namespace Stage
{
	class LevelSetting;

	/********************************************************

	Pre-definition of the Objects

	Object
	Player
	Enemy
	Planet

	********************************************************/
	class Object
	{
	public:
		Object() {};
		~Object() {};
		// Basic Setter functions
		void setNumber(int i) { number = i; }				// set number function
		void setHealth(int i) { health = i; }					// set health function 
		void setType(int i) { type = i; }							// set type of Object

		// Basic Getter functions
		const int GetType(void) { return type; }						// get type of Object
		const int GetNumber(void) { return number; }			// get number of Object
		const int GetHealth(void) { return health; }				// get health of Object
		const int GetCondition(void) { return condition; }				// get condition of Object
		BE::Actor* GetOwner(void) { return owner; }  // get actor of Object

		// in/decrease health
		void IncreaseHealth(int i) { health -= i; }
		void DecreaseHealth(int i) { health -= i;  }
		
		void Active(void)
		{
			owner->_isActive = true;
		}
		void Inactive(void)
		{
			owner->_isActive = false;
		}

		//virtual void Update(float dt) = 0;					// Object must have the Update function for role
		virtual void Update(LevelSetting& LvSetting, float dt) = 0;					// Object must have the Update function for role

	protected:
		// each variables in here are could different defending on the type
		int number;
		int health;
		int type;
		int condition;

		BE::Actor* owner;
		BE::Component::Transform*				m_transform;
		BE::Component::Rigidbody*				m_rigidbody;
		BE::Component::Display*					m_display;
		BE::Component::CircleCollider*		    m_collider;
		BE::Component::ParticleEmitter*		    m_particle;
	private:
	};


}
