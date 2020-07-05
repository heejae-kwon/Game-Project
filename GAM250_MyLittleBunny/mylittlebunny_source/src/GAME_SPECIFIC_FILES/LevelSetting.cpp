/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:    LevelSetting.cpp
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
namespace {
}

namespace Stage {

	LevelSetting::LevelSetting()
	{
	}

	LevelSetting::~LevelSetting()
	{
	}

	void LevelSetting::GenerateEnemyList(std::vector<std::unique_ptr<BE::Actor>>& ActorList)
	{
			for (; enemyNum <= max_enemyNum; ++enemyNum)
			{
				std::stringstream EnemyName;
				EnemyName << "enemy" << enemyNum; // set enemy name with number
				BE::Engine::BunnyEngine::instance()->getActiveStage()->addActor(BE::Actor::createActor(EnemyName.str(), true));
		
				BE::Actor* actor = ActorList.back().get();
				// Add Transform
				actor->getComponent<BE::Component::Transform>()->position = glm::vec3(enemyNum * 30 + ((enemyNum % 2 == 0) ? -4000 : 4000) , enemyNum * 10 + ((enemyNum % 2 == 0) ? -3000 : 3000), 0.f);

				// Add Display
				actor->addComponent<BE::Component::Display>();
				actor->getComponent<BE::Component::Display>()->setTextureId("sprEnemy1");

				// Add Circle Collider
				actor->addComponent<BE::Component::CircleCollider>();
				actor->getComponent<BE::Component::CircleCollider>()->radius = 75;
				actor->getComponent<BE::Component::CircleCollider>()->ghost = true;

				// Add Rigidbody
				actor->addComponent<BE::Component::Rigidbody>();
				actor->getComponent<BE::Component::Rigidbody>()->setMass(5.5f);
				actor->getComponent<BE::Component::Rigidbody>()->gravityscale = 10000.f;/*
				actor->getComponent<BE::Component::Rigidbody>()->friction_static = 0.5f;
				actor->getComponent<BE::Component::Rigidbody>()->friction_dynamic = 0.4f;*/


				// Add ParticleEmitter
				actor->addComponent<BE::Component::ParticleEmitter>();
                /*
				actor->getComponent<BE::Component::ParticleEmitter>()->textureId = "sprParticle";
				actor->getComponent<BE::Component::ParticleEmitter>()->spriteIndex = 0;
				actor->getComponent<BE::Component::ParticleEmitter>()->capacity = 100;
				actor->getComponent<BE::Component::ParticleEmitter>()->pos.x = 0;
				actor->getComponent<BE::Component::ParticleEmitter>()->pos.y = 0;
				actor->getComponent<BE::Component::ParticleEmitter>()->pos.z = 0;
				actor->getComponent<BE::Component::ParticleEmitter>()->maxscale = 100;
				actor->getComponent<BE::Component::ParticleEmitter>()->minscale = 0;
				actor->getComponent<BE::Component::ParticleEmitter>()->maxvel = 100;
				actor->getComponent<BE::Component::ParticleEmitter>()->minvel = 0;
				actor->getComponent<BE::Component::ParticleEmitter>()->size.x = 10;
				actor->getComponent<BE::Component::ParticleEmitter>()->size.y = 10;
				actor->getComponent<BE::Component::ParticleEmitter>()->lifetime = 4;

				actor->getComponent<BE::Component::ParticleEmitter>()->particleType = BE::ParticleType::THREE;
				*/

				actor->_isActive = false;
			}
	}

	void LevelSetting::GenerateHPbar(std::vector<std::unique_ptr<BE::Actor>>& ActorList)
	{
		for (auto  &planet : planetVector)
		{
			std::stringstream barName;
			/*Bar 1***********************************************/
			barName << planet.GetOwner()->_name <<"hpBar";
			BE::Engine::BunnyEngine::instance()->getActiveStage()->addActor(BE::Actor::createActor(barName.str(), true));

			BE::Actor* actor = ActorList.back().get();
			// Add Transform
			BE::Component::Transform *  b_transform = actor->getComponent<BE::Component::Transform>();
			
			b_transform->position
				= planet.GetOwner()->getComponent<BE::Component::Transform>()->position;
			b_transform->position.z = 5;
			b_transform->scale = { 4, 5 };

			// Add Display
			actor->addComponent<BE::Component::Display>();

			BE::Component::Display * b_display = actor->getComponent<BE::Component::Display>();
			b_display->setTextureId("sprHPbar");
			b_display->textureColor = { 0.6, 1, 0, 1 };

			planet.hpBar = actor;
			//planet.barTransform = actor->getComponent<BE::Component::Transform>();

			/*Bar 2***********************************************/
			barName << "Back";
			BE::Engine::BunnyEngine::instance()->getActiveStage()->addActor(BE::Actor::createActor(barName.str(), true));

			BE::Actor* actor2 = ActorList.back().get();
			// Add Transform
			b_transform = actor2->getComponent<BE::Component::Transform>();

			b_transform->position
				= planet.GetOwner()->getComponent<BE::Component::Transform>()->position;
			b_transform->position.z = 4;
			b_transform->scale = { 4.2, 7 };

			// Add Display
			actor2->addComponent<BE::Component::Display>();
			
			b_display = actor2->getComponent<BE::Component::Display>();
			b_display->setTextureId("sprHPbar");
			b_display->textureColor = { 0, 0, 0, 1 };

		}
	}

	void LevelSetting::SetPlanetList(std::vector<std::unique_ptr<BE::Actor>>& ActorList)
	{
        planetVector.resize(0);
		for (auto & actor : ActorList)
		{
			if (actor->_name.find("planet") != std::string::npos)
			{
				Planet planet;

				planet.setPlanet(actor.get());
				planet.setNumber(planetNum);
				++planetNum;
				std::cout << actor->_name << std::endl;
				planetVector.push_back(planet);
				++max_planetNum;
			}
		}
	}

	void LevelSetting::SetEnemyList(std::vector<std::unique_ptr<BE::Actor>>& ActorList)
	{
		BE::HBRandom::Seed();
		int i = 0;
		for (auto & actor : ActorList)
		{
			if (actor->_name.find("enemy") != std::string::npos)
			{
				Enemy enemy;
				//actor.get()->getComponent
				enemy.setEnemy(actor.get());
				enemy.setNumber(i);
				BE::Core::Debugger::instance()->AddLog("Enemy Number is %d\n", enemy.GetNumber());
				enemy.setPlanetNum(BE::HBRandom::GetInt(1, max_planetNum));
				BE::Core::Debugger::instance()->AddLog("SetPlanetNumber with %d\n", enemy.GetPlanetNum());
				enemy.setHealth(max_enemyHealth);
				enemy.Inactive();
				enemyVector.push_back(enemy);
				++i;
			}
		}
	}


	void LevelSetting::GenerateEnemy(float term, float dt)
	{
		//if (enemyVector.empty())
		//	return;
		waveAlarmTime += dt;
		if ( waveAlarmTime > 2 && waveAlarmTime < 4)
			_waveAlarm->_isActive = true;
		else
			_waveAlarm->_isActive = false;


		if (generateTime >= term && generateNum < max_enemyNum && generateNum < waveConditionNum && waveAlarmTime >4) 
		{
			generateTime = 0;
			enemyVector[generateNum].SetGravity(planetVector, max_planetNum);
			enemyVector[generateNum].ActiveEnemy();
			BE::Core::Debugger::instance()->AddLog("Enemy%d is generated\n", generateNum);
			++generateNum;
		}
		//wave state is start
		else if(deadEnemyNum == waveConditionNum)
        {
			waveBreakTime += dt;

			if(waveBreakTime > 3)
				_waveAlarm->_isActive = true;
		}
		//wave waiting time
		if (waveBreakTime > 5)
        {
			_waveAlarm->_isActive = false;
			enemyNum_perWave += step_enemyNum;
			waveConditionNum += enemyNum_perWave;
			waveBreakTime = 0;
		}

		generateTime += dt;
	}
}