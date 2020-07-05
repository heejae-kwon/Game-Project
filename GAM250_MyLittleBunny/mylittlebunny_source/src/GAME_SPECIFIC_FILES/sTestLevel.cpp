/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      sTestLevel.cpp
Purpose:        To test emitter and particle
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/
#include <BunnyEngine.hpp>
#include <WIP/PropManager.hpp>
#include <Utilities/JsonWriter.hh>
#include <Utilities/JsonReader.hh>

#include <GAME_SPECIFIC_FILES/sTestLevel.hpp>
#include <GAME_SPECIFIC_FILES/sConfirmMenu.hpp>
#include <GAME_SPECIFIC_FILES/sWinScreen.hpp>
#include <GAME_SPECIFIC_FILES/sLoseScreen.hpp>
#include <GAME_SPECIFIC_FILES/logicFunctions.hh>


#include <WIP/HBRandom.hpp>


Stage::sTestLevel::sTestLevel()
	: BaseStage("sTestLevel.stg")
{
}


void
Stage::sTestLevel::start(std::string fileName_)
{
	loadProps(fileName_);
	loadStageFile(fileName_);

	//int hudNum = 0;

	_player = getActor("player");
	m_player.initData(getActor("player"));

	_camera = getActor("camera");
	
	BE::Core::Draw::instance()->setClearBufferColor(glm::vec3(24.f / 255.f, 24.f / 255.f, 48.f / 255.f));
	    
	LevelSetting1.max_enemyNum = 20;

	LevelSetting1.player = &m_player;
	LevelSetting1.SetPlanetList(_actorVec);
	LevelSetting1.GenerateEnemyList(_actorVec);
	LevelSetting1.SetEnemyList(_actorVec);
	//LevelSetting1.generateDone = true;

}

void
Stage::sTestLevel::resume()
{
}

void
Stage::sTestLevel::pause()
{
}

void
Stage::sTestLevel::update(float dt_)
{
	//for (auto & actor : _actorVec)
	//{
	//	if (actor->_name == "camera")
	//	{
	//		// logic::camera::cameraMoveLogic(actor.get(), dt);
	//	}
	//	else if (actor->_name == "player")
	//	{
	//		dt_;
	//	}
	//}

	//Hud bar

	// Update the Level Setting values

	LevelSetting1.GenerateEnemy(1, dt_);

	for (auto & planets : LevelSetting1.planetVector)
	{
		planets.Update(LevelSetting1, dt_);
	}
	for (auto & enemies : LevelSetting1.enemyVector)
	{
		//enemies.EnemyUpdate(_player);
		enemies.Update(LevelSetting1, dt_);
	}

	_camera->getComponent<BE::Component::Transform>()->position = -_player->getComponent<BE::Component::Transform>()->position;


	m_player.Update(LevelSetting1, dt_);

	if (BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_KP_PLUS))
	{
		BE::Core::Debugger::instance()->AddLog("[LOG][sLevel1::update()] KeyPad + pressed\n");
		BE::WindowAbst::instance()->resizeWindow(glm::vec2(1920, 1080));
	}
	if (BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_KP_MINUS))
	{
		BE::Core::Debugger::instance()->AddLog("[LOG][sLevel1::update()] KeyPad - pressed\n");
		BE::WindowAbst::instance()->resizeWindow(glm::vec2(1280, 720));
	}
	if (BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_ESCAPE))
	{
		BE::Engine::BunnyEngine::instance()->pushActiveStage(new sConfirmMenu);
	}
	if (BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_p))
	{
		for (auto & planets : LevelSetting1.planetVector)
		{
			planets.setHealth(500);
		}
	}
	if (BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_w))
	{

		BE::Engine::BunnyEngine::instance()->flushStages();
		BE::Engine::BunnyEngine::instance()->pushActiveStage(new Stage::sWinScreen);
	}

	WinCondition(LevelSetting1);
	LoseCondition(LevelSetting1);

}

void Stage::sTestLevel::WinCondition(LevelSetting levelSetting)
{
	if(levelSetting.deadEnemyNum >= 5)
	{
		BE::Engine::BunnyEngine::instance()->flushStages();
		BE::Engine::BunnyEngine::instance()->pushActiveStage(new Stage::sWinScreen);
	}
}

void Stage::sTestLevel::LoseCondition(LevelSetting levelSetting)
{
	if (levelSetting.deadPlanetNum >= 1)
	{
		BE::Engine::BunnyEngine::instance()->flushStages();
		BE::Engine::BunnyEngine::instance()->pushActiveStage(new Stage::sLoseScreen);
	}
}



