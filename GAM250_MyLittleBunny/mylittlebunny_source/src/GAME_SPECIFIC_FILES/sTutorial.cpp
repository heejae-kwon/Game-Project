/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      sTutorial.cpp
Purpose:        To test background and the planet
Language:       C++
Project:        GAM250
Author:         Name : minji.kim
Email:          seraminji2146@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/
#include <BunnyEngine.hpp>
#include <WIP/PropManager.hpp>
#include <Utilities/JsonWriter.hh>
#include <Utilities/JsonReader.hh>

#include <GAME_SPECIFIC_FILES/sTutorial.hpp>
#include <GAME_SPECIFIC_FILES/sConfirmMenu.hpp>
#include <GAME_SPECIFIC_FILES/sLegacyMenu.hpp>
#include <GAME_SPECIFIC_FILES/sWinScreen.hpp>
#include <GAME_SPECIFIC_FILES/sLoseScreen.hpp>
#include <GAME_SPECIFIC_FILES/logicFunctions.hh>


#include <WIP/HBRandom.hpp>
namespace {
	const int STAR_MAX = 60;
}

Stage::sTutorial::sTutorial()
	: BaseStage("sTutorial.stg")
{
}


void
Stage::sTutorial::start(std::string fileName_)
{
	loadProps(fileName_);
	loadStageFile(fileName_);

	//int hudNum = 0;
	hud = getActor("Star");
	_player = getActor("player");
	m_player.initData(_player, 100000000.f, 2000000.f, 0.95f, 4000000.f);

	_camera = getActor("camera");

	_backStar = getActor("BackStar");

	BE::Core::Draw::instance()->setClearBufferColor(glm::vec3(24.f / 255.f, 24.f / 255.f, 48.f / 255.f));

	//LevelSetting1.max_enemyNum = getActor("")
	LevelSetting1.player = &m_player;

	LevelSetting1.max_enemyNum = 0;

	LevelSetting1.generateTime = 2;
	LevelSetting1.SetPlanetList(_actorVec);
	LevelSetting1.GenerateEnemyList(_actorVec);
	LevelSetting1.SetEnemyList(_actorVec);
	//LevelSetting1.generateDone = true;
	LevelSetting1.generateTime = 5;
	_1to3Button = getActor("1to3Button");
	_3to5Button = getActor("3to5Button");
	_superstandHUD = getActor("SuperStandHUD");
	_FinalDestination = getActor("planet4");
	winTimer = 0;
	loseTimer = 0;

	for (int starNum = 0; starNum <= STAR_MAX; ++starNum)
	{
		std::stringstream StarName;
		StarName << "BackStar" << starNum;
		BE::Actor* actor = BE::Engine::BunnyEngine::instance()->getActiveStage()->addActor(BE::Actor::createActor(StarName.str(), true));

		actor->getComponent<BE::Component::Transform>()->position = glm::vec3(BE::HBRandom::GetInt(-600, 600), BE::HBRandom::GetInt(-300, 300), -5);
		glm::vec2 scaleRange((BE::HBRandom::GetInt(2, 5) / 100.f));
		actor->getComponent<BE::Component::Transform>()->scale = scaleRange;
		actor->addComponent<BE::Component::Display>();
		actor->getComponent<BE::Component::Display>()->drawType = BE::Component::Display::HUD;
		actor->getComponent<BE::Component::Display>()->setTextureId("sprTwinkle");
		if (starNum % 2 == 0)
		{
			actor->getComponent<BE::Component::Display>()->playAnim("animBackgroundStar", true, (float)((starNum * starNum) / STAR_MAX));
		}
	}
}

void
Stage::sTutorial::resume()
{
}

void
Stage::sTutorial::pause()
{
}

float
Stage::sTutorial::pointObj(BE::Actor* act1, BE::Actor* act2)
{
	float result = 0;
	glm::vec3 act1Pos = act1->getComponent<BE::Component::Transform>()->position;
	glm::vec3 act2Pos = act2->getComponent<BE::Component::Transform>()->position;
	glm::vec3 distance = (act2Pos - act1Pos);

	//BE::Core::Debugger::instance()->AddLog("X value: %d\n", distance.length());

	result = ((distance.x) / (glm::length(distance)));
	result = (glm::acos(result));

	if (distance.y > 0)
	{
		//BE::Core::Debugger::instance()->AddLog("positive: %f\n", result);

		act1->getComponent<BE::Component::Transform>()->rotation = (glm::degrees(result));
		return result;

	}
	else
	{
		//BE::Core::Debugger::instance()->AddLog("negative: %f\n", -result);
		act1->getComponent<BE::Component::Transform>()->rotation = (glm::degrees(-result));
		return -result;

	}

}

void
Stage::sTutorial::update(float dt_)
{

	//compass 
	pointObj(hud, _player);

	//Hud bar
	int hudTexId = 5;
	if (LevelSetting1.deadEnemyNum > 2)
	{
		hudTexId -= static_cast<int>(LevelSetting1.deadEnemyNum / 2);
	}
	if (hudTexId > 0)
	{
		getActor("hud")->getComponent<BE::Component::Display>()->setTextureId("sprHUD", hudTexId);
		_superstandHUD->_isActive = false;
	}
	//jihwan 
	if (hudTexId == 1)
	{
		m_player.powerUp();
		_superstandHUD->_isActive = true;
	}

	int planHudId1 = 3;
	{
		Planet planets1 = LevelSetting1.planetVector.front();
		if (planets1.GetCondition() == cond_WORKING)
		{
			planHudId1 -= static_cast<int>(LevelSetting1.deadPlanetNum / 3);
			getActor("LightHud1")->getComponent<BE::Component::Display>()->spriteIndex = 3;
		}
		else if (planets1.GetCondition() == cond_pBROKEN)
		{
			planHudId1 -= static_cast<int>(LevelSetting1.deadPlanetNum / 3);
			getActor("LightHud1")->getComponent<BE::Component::Display>()->spriteIndex = 2;
		}
		else if (planets1.GetCondition() == cond_DEAD)
		{
			planHudId1 -= static_cast<int>(LevelSetting1.deadPlanetNum / 3);

			getActor("LightHud1")->getComponent<BE::Component::Display>()->spriteIndex = 1;
		}
	}

	int planHudId2 = 3;
	{
		Planet planets2 = LevelSetting1.planetVector.front();
		if (planets2.GetCondition() == cond_WORKING)
		{
			planHudId2 -= static_cast<int>(LevelSetting1.deadPlanetNum / 3);
			getActor("LightHud2")->getComponent<BE::Component::Display>()->spriteIndex = 3;
		}
		else if (planets2.GetCondition() == cond_pBROKEN)
		{
			planHudId2 -= static_cast<int>(LevelSetting1.deadPlanetNum / 3);
			getActor("LightHud2")->getComponent<BE::Component::Display>()->spriteIndex = 2;
		}
		else if (planets2.GetCondition() == cond_DEAD)
		{
			planHudId2 -= static_cast<int>(LevelSetting1.deadPlanetNum / 3);

			getActor("LightHud2")->getComponent<BE::Component::Display>()->spriteIndex = 1;
		}
	}

	/*int planHudId3 = 3;
	{
	Planet planets3 = LevelSetting1.planetVector.front();
	if (planets3.GetCondition() == cond_WORKING)
	{
	planHudId3 -= static_cast<int>(LevelSetting1.deadPlanetNum / 3);
	getActor("LightHud3")->getComponent<BE::Component::Display>()->spriteIndex = 3;
	}
	else if (planets3.GetCondition() == cond_pBROKEN)
	{
	planHudId3 -= static_cast<int>(LevelSetting1.deadPlanetNum / 3);
	getActor("LightHud3")->getComponent<BE::Component::Display>()->spriteIndex = 2;
	}
	else if (planets3.GetCondition() == cond_DEAD)
	{
	planHudId3 -= static_cast<int>(LevelSetting1.deadPlanetNum / 3);

	getActor("LightHud3")->getComponent<BE::Component::Display>()->spriteIndex = 1;
	}
	}*/






	LevelSetting1.GenerateEnemy(1, dt_);
	ShootPlayer(dt_);
	/*for (auto & planets : _planetVectors)
	{
	planets.Update(LevelSetting1, dt_);
	}*/
	for (auto & planets : LevelSetting1.planetVector)
	{
		planets.Update(LevelSetting1, dt_);
	}
	/*for (auto & enemies : _enemyVectors)
	{
	enemies.EnemyUpdate(_player);
	enemies.Update(LevelSetting1, dt_);
	}*/
	for (auto & enemies : LevelSetting1.enemyVector)
	{
		//enemies.EnemyUpdate(_player);
		enemies.Update(LevelSetting1, dt_);
	}

	_camera->getComponent<BE::Component::Transform>()->position = -_player->getComponent<BE::Component::Transform>()->position;


	m_player.Update(LevelSetting1, dt_);

	if (BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_UP))
	{
		BE::Core::Debugger::instance()->AddLog("[LOG][sLevel1::update()] KeyPad 'UP' pressed\n");

	}

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
	/*if (BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_w))
	{

	BE::Engine::BunnyEngine::instance()->flushStages();
	BE::Engine::BunnyEngine::instance()->pushActiveStage(new Stage::sWinScreen);
	}*/
	if (BE::Input::Keyboard::instance()->IsPressed(BE::KB::KEY_s))
		m_player.powerUp();
	if (BE::Input::Keyboard::instance()->IsPressed(BE::KB::KEY_d))
		m_player.powerDown();

	if (BE::Input::Keyboard::instance()->IsPressed(BE::KB::KEY_u))
		_camera->getComponent<BE::Component::Display>()->playAnim("animShaking", false);

	//WinCondition(LevelSetting1, dt_);
	//LoseCondition(LevelSetting1, dt_);

	// Wincondition
	if (BE::Core::Physics::instance()->Collision(_player, _FinalDestination) == BE::Core::Physics::CS_OnCollision)
	{
		BE::Engine::BunnyEngine::instance()->flushStages();
		BE::Engine::BunnyEngine::instance()->pushActiveStage(new Stage::sLegacyMenu);
		return;
	}

	// Lose condition
	if (LevelSetting1.deadPlanetNum >= 3)
	{
		loseTimer += dt_;

		LevelSetting1.player->m_actor->getComponent<BE::Component::ParticleEmitter>()->setCapacity(100);
		LevelSetting1.player->m_actor->getComponent<BE::Component::ParticleEmitter>()->maxscale = 300;
		LevelSetting1.player->m_actor->getComponent<BE::Component::ParticleEmitter>()->maxvel = 500;
		LevelSetting1.player->m_actor->getComponent<BE::Component::ParticleEmitter>()->particleType = BE::ParticleType::TWO;

		if (loseTimer >= 2)
		{
			BE::Engine::BunnyEngine::instance()->flushStages();
			BE::Engine::BunnyEngine::instance()->pushActiveStage(new Stage::sLoseScreen);
			return;
		}
	}
}

void Stage::sTutorial::WinCondition(LevelSetting /*levelSetting*/)
{
	if(BE::Core::Physics::instance()->Collision(_player, _FinalDestination) == BE::Core::Physics::CS_OnCollision)
	{
		BE::Engine::BunnyEngine::instance()->flushStages();
		BE::Engine::BunnyEngine::instance()->pushActiveStage(new Stage::sLegacyMenu);
		return;
	}
}

void Stage::sTutorial::LoseCondition(LevelSetting levelSetting)
{
	if (levelSetting.deadPlanetNum >= 1)
	{
		BE::Engine::BunnyEngine::instance()->flushStages();
		BE::Engine::BunnyEngine::instance()->pushActiveStage(new Stage::sLoseScreen);
		return;
	}
}
//
//void Stage::sTutorial::ControlHelper(void)
//{
//	// Arrow key
//	if (BE::Core::Physics::instance()->Collision(_player, _ArrowkeyHelp) == BE::Core::Physics::CS_OnCollision)
//		_ArrowkeyHelp->_isActive = true;
//	else
//		_ArrowkeyHelp->_isActive = false;
//
//	// Spacebar
//	if (BE::Core::Physics::instance()->Collision(_player, _SpacebarHelp) == BE::Core::Physics::CS_OnCollision)
//		_SpacebarHelp->_isActive = true;
//	else
//		_SpacebarHelp->_isActive = false;
//
//	// Akey
//	/*if (BE::Core::Physics::instance()->Collision(_player, _AkeyHelp) == BE::Core::Physics::CS_OnCollision
//		 && m_TutorialEnemy.GetOwner()->_isActive == true)
//		_AkeyHelp->_isActive = true;
//	else
//		_AkeyHelp->_isActive = false;
//*/
//	// Upkey
//	if (BE::Core::Physics::instance()->Collision(_player, _UpkeyHelp) == BE::Core::Physics::CS_OnCollision
//		&& m_GeneratedEnemy->GetCondition() == cond_eFixed)
//		_UpkeyHelp->_isActive = true;
//	else
//		_UpkeyHelp->_isActive = false;
//}
//
//void Stage::sTutorial::CreateButton(float dt)
//{
//	if (m_GeneratedEnemy->GetCondition() == cond_eFixed)
//	{
//		_ShootButton->_isActive = true;
//		_EnemyExplanation->_isActive = true;
//	}
//
//	if (_EnemyExplanation->_isActive == true)
//		explanationTimer += dt;
//
//	if (explanationTimer >= 10)
//		_EnemyExplanation->_isActive = false;
//}
//
void Stage::sTutorial::ShootPlayer(float dt)
{
	/*if (BE::Core::Physics::instance()->Collision(_player, _ShootButton) == BE::Core::Physics::CS_OnCollision
		&& BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_UP))
	{
		m_player.flytoOtherPlanet("Finalplanet3", TutorialSetting, dt);
		BE::Core::Debugger::instance()->AddLog("player and button collide\n");
	}*/
	if (_1to3Button == nullptr)
		return;

	if (BE::Core::Physics::instance()->Collision(_player, _1to3Button) == BE::Core::Physics::CS_OnCollision
		&& (BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_UP) || BE::Input::Gamepad::instance()->IsPressed(BE::GP::BUTTON_DPAD_UP)))
	{
		m_player.flytoOtherPlanet("planet2", LevelSetting1, dt);
		BE::Core::Debugger::instance()->AddLog("player and button collide\n");
	}

	if (_3to5Button == nullptr)
		return;

	if (BE::Core::Physics::instance()->Collision(_player, _3to5Button) == BE::Core::Physics::CS_OnCollision
		&& (BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_UP) || BE::Input::Gamepad::instance()->IsPressed(BE::GP::BUTTON_DPAD_UP)))
	{
		m_player.flytoOtherPlanet("planet4", LevelSetting1, dt);
		BE::Core::Debugger::instance()->AddLog("player and button collide\n");
	}
}



