/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:    oPlanet.cpp
Purpose:       This file contain Level setting codes.
Can be used C style with static functions or C++ with methods.
Language:     C++
Project:         GAM250
Author:         Name : Jihwan Oh
Email:            dkdkdkdudrn@gmail.com
date:			   2017.06.16
----------------------------------------------------------------------------*/
#include <BunnyEngine.hpp>
#include <WIP/PropManager.hpp>
#include <Utilities/JsonWriter.hh>
#include <Utilities/JsonReader.hh>

#include <GAME_SPECIFIC_FILES/LevelSetting.hpp>

#include <GAME_SPECIFIC_FILES\oPlanet.hpp>
#include <GAME_SPECIFIC_FILES/sConfirmMenu.hpp>
#include <GAME_SPECIFIC_FILES/sWinScreen.hpp>
#include <GAME_SPECIFIC_FILES/logicFunctions.hh>

namespace Stage {
	/***************************************************

	Real Definition of the Classses

	Planet

	****************************************************/
	// Real Definition of the Planet
	Planet::Planet() {}
	Planet::~Planet() {}
	Planet::Planet(BE::Actor* rhs) : isAttacked(false), enemyNum(0)
	{
		// Set variables from the parent
		owner = rhs;
		number = planetNum;
		++planetNum;
		condition = cond_WORKING;
		health = owner->getComponent<BE::Component::Gameplay>()->hp;
		max_health = static_cast<float>(health);
		type = type_PLANET;
		hpBar = nullptr;
		m_transform = owner->getComponent<BE::Component::Transform>();
		m_display = owner->getComponent<BE::Component::Display>();
		m_rigidbody = owner->getComponent<BE::Component::Rigidbody>();
		immortal = false;
	}
	void Planet::setPlanet(BE::Actor* rhs)
	{
		// Set variables from the parent
		owner = rhs;
		number = planetNum;
		++planetNum;
		condition = cond_WORKING;
		if (owner->getComponent<BE::Component::Gameplay>() != nullptr)
		{
			health = owner->getComponent<BE::Component::Gameplay>()->hp;
			max_health = static_cast<float>(health);
		}
		else
		{
			max_health = 100;
			health = 100;
		}
		type = type_PLANET;
		hpBar = nullptr;

		m_transform = owner->getComponent<BE::Component::Transform>();
		m_display = owner->getComponent<BE::Component::Display>();
		m_rigidbody = owner->getComponent<BE::Component::Rigidbody>();
		immortal = false;
	}

	void Planet::setPlanetNum(int i)
	{
		number = i;
	}

	void Planet::PlanetUpdate(LevelSetting& LvSetting)
	{
		healthRatio = static_cast<float>(health) / max_health;
		if (healthRatio > 1.f)
			healthRatio = 1.f;
		// condition 1
		if (health <= 0)
		{
			if (condition != cond_DEAD)
			{
				owner->getComponent<BE::Component::Display>()->spriteIndex += 1;
				++LvSetting.deadPlanetNum;
				condition = cond_DEAD;
				hpBar->_isActive = false;
			}
		}
		// condition 2
		else if (healthRatio <= 0.3f)
		{
			if (condition != cond_pBROKEN2)
			{
				owner->getComponent<BE::Component::Display>()->spriteIndex += 1;
				condition = cond_pBROKEN2;
				hpBar->getComponent<BE::Component::Display>()->textureColor = { 1, 0, 0, 1 };
			}
		}
		// condition 3
		else if (healthRatio <= 0.6f)
		{
			if (condition != cond_pBROKEN)
			{
				owner->getComponent<BE::Component::Display>()->spriteIndex += 1;
				condition = cond_pBROKEN;
				hpBar->getComponent<BE::Component::Display>()->textureColor = { 1, 1, 0, 1 };
			}
		}
	}
	void Planet::Update(LevelSetting& LvSetting, float dt)
	{
		PlanetUpdate(LvSetting);
		ShakeControl(dt);
		SetHPbar();
	}
	void Planet::ShakeControl(float dt)
	{
		if (Shaking)
		{
			ShakingTimer += dt;
			if (ShakingTimer >= 1)
			{
				Shaking = false;
				ShakingTimer = 0;
			}
		}
	}
	void Planet::SetHPbar(void)
	{
		//if(hpBar != nullptr)
		BE::Component::Transform * hpBarTransform = hpBar->getComponent<BE::Component::Transform>();
		hpBarTransform->scale.x = 4 * healthRatio;
		hpBarTransform->position.x = m_transform->position.x - 250 * ( 1 - healthRatio);
		/*
			green = 0.6, 1, 0, 1;
			yellow = 1, 1, 0, 1;
			red = 1, 0, 0, 1;
		*/
	}
	void Planet::ActivePlanet(void)
	{
		owner->_isActive = true;
	}
	void Planet::InactivPlanet(void)
	{
		owner->_isActive = false;
	}


}