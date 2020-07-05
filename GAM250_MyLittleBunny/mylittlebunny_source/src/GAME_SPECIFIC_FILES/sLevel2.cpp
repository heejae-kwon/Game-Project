#include <BunnyEngine.hpp>
#include <WIP/PropManager.hpp>
#include <Utilities/JsonWriter.hh>
#include <Utilities/JsonReader.hh>

#include <GAME_SPECIFIC_FILES/sLevel2.hpp>
#include <GAME_SPECIFIC_FILES/sConfirmMenu.hpp>
#include <GAME_SPECIFIC_FILES/sWinScreen.hpp>
#include <GAME_SPECIFIC_FILES/sLoseScreen.hpp>
#include <GAME_SPECIFIC_FILES/logicFunctions.hh>


#include <WIP/HBRandom.hpp>
namespace {
	const int STAR_MAX = 60;
}


Stage::sLevel2::sLevel2()
	: BaseStage("sLevel2.stg")
{
}


void
Stage::sLevel2::start(std::string fileName_)
{
	loadProps(fileName_);
	loadStageFile(fileName_);

	//int hudNum = 0;
	_hud = getActor("ArrowHUD");
	//_dangerPoint = getActor("");//one planet in group planet
	_player = getActor("player");
	_feverTime = getActor("Fever");
	m_player.initData(_player, 100000000.f, 2000000.f, 0.95f, 4000000.f);

	_waveAlarm = getActor("WaveAlarm");
	_camera = getActor("camera");
	m_camera.setActor(_camera);
	_backStar = getActor("BackStar");

	BE::Core::Draw::instance()->setClearBufferColor(glm::vec3(24.f / 255.f, 24.f / 255.f, 48.f / 255.f));

	//LevelSetting1.max_enemyNum = getActor("")
	LevelSetting1.player = &m_player;

	LevelSetting1.max_enemyNum = 30;
	//LevelSetting1.generateTime = 2;
	LevelSetting1.SetPlanetList(_actorVec);
	LevelSetting1.GenerateEnemyList(_actorVec);
	LevelSetting1.SetEnemyList(_actorVec);
	//LevelSetting1.generateDone = true;
	LevelSetting1.generateTime = 5;
	_1to3Button = getActor("1to3Button");
	_3to5Button = getActor("3to5Button");
	_superstandHUD = getActor("SuperStandHUD");
	_xKey = getActor("xHelp");
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
Stage::sLevel2::resume()
{
}

void
Stage::sLevel2::pause()
{
}

float
Stage::sLevel2::pointObj(BE::Actor* act1, BE::Actor* act2)
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
Stage::sLevel2::update(float dt_)
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


	//compass 
	{
		float arrowTime = 0.f;
		_hud->_isActive = false;
		Planet planetLife = LevelSetting1.planetVector[1];
		if (planetLife.GetCondition() == cond_pBROKEN)
		{
			_hud->_isActive = true;

			pointObj(_hud, _player);

			if((arrowTime+= dt_) > 2.f)
				_hud->_isActive = false;
		}
		
	}
	

	//Hud bar to change for special mode bunnuy
	int hudTexId = 5;
	if (LevelSetting1.deadEnemyNum > 2)
	{
		hudTexId -= static_cast<int>(LevelSetting1.deadEnemyNum / 2);
	}
	if (hudTexId > 0)
	{
		getActor("hud")->getComponent<BE::Component::Display>()->setTextureId("sprHUD", hudTexId);
		_superstandHUD->_isActive = true;
	}

	_feverTime->_isActive = false;
	//jihwan 
	if (hudTexId == 1)
	{
		float time = 0;
		m_player.powerUp();
		_xKey->_isActive = true;
		_feverTime->_isActive = true;
		if ((time += dt_) > 2.f)
			_feverTime->_isActive = false;
		//_superstandHUD->_isActive = true;
	}



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

	//camera shaking
	m_camera.setPosition(glm::vec3(-m_player.getAnchorPoint(), 1.0f));
	m_camera.Update(dt_);
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
	//if (BE::Input::Keyboard::instance()->IsPressed(BE::KB::KEY_s))
	//{
	//	m_player.powerUp();
	//}
	//if (BE::Input::Keyboard::instance()->IsPressed(BE::KB::KEY_d))
	//	m_player.powerDown();

	if (BE::Input::Keyboard::instance()->IsPressed(BE::KB::KEY_u))
		_camera->getComponent<BE::Component::Display>()->playAnim("animShaking", false);

	//WinCondition(LevelSetting1, dt_);
	//LoseCondition(LevelSetting1, dt_);
	if (LevelSetting1.deadEnemyNum >= LevelSetting1.max_enemyNum)
	{
		winTimer += dt_;

		//setMoveForce(CHANGE_MOVE_FORCE);
		//levelSetting.player->m_actor->getComponent<BE::Component::ParticleEmitter>()->m_change = true;
		LevelSetting1.player->m_actor->getComponent<BE::Component::ParticleEmitter>()->capacity = 100;
		LevelSetting1.player->m_actor->getComponent<BE::Component::ParticleEmitter>()->maxscale = 300;
		LevelSetting1.player->m_actor->getComponent<BE::Component::ParticleEmitter>()->maxvel = 500;
		LevelSetting1.player->m_actor->getComponent<BE::Component::ParticleEmitter>()->particleType = BE::ParticleType::FOUR;
		LevelSetting1.player->m_actor->getComponent<BE::Component::ParticleEmitter>()->textureId = "sprFireWork";

		if (winTimer >= 3)
		{
			BE::Engine::BunnyEngine::instance()->flushStages();
			BE::Engine::BunnyEngine::instance()->pushActiveStage(new Stage::sWinScreen);
		}
		return;
	}
	if (LevelSetting1.deadPlanetNum >= 3)
	{
		loseTimer += dt_;
		if (loseTimer >= 2)
		{
			BE::Engine::BunnyEngine::instance()->flushStages();
			BE::Engine::BunnyEngine::instance()->pushActiveStage(new Stage::sLoseScreen);
		}
		return;
	}
}

void Stage::sLevel2::WinCondition(LevelSetting& levelSetting, float dt)
{
	if(levelSetting.deadEnemyNum >= levelSetting.max_enemyNum)
	{
		winTimer += dt;

		//setMoveForce(CHANGE_MOVE_FORCE);
		//levelSetting.player->m_actor->getComponent<BE::Component::ParticleEmitter>()->m_change = true;
		levelSetting.player->m_actor->getComponent<BE::Component::ParticleEmitter>()->capacity = 100;
		levelSetting.player->m_actor->getComponent<BE::Component::ParticleEmitter>()->maxscale = 300;
		levelSetting.player->m_actor->getComponent<BE::Component::ParticleEmitter>()->maxvel = 500;
		levelSetting.player->m_actor->getComponent<BE::Component::ParticleEmitter>()->particleType = BE::ParticleType::FOUR;
		levelSetting.player->m_actor->getComponent<BE::Component::ParticleEmitter>()->textureId = "sprFireWork";

		if (winTimer >= 3)
		{
			BE::Engine::BunnyEngine::instance()->flushStages();
			BE::Engine::BunnyEngine::instance()->pushActiveStage(new Stage::sWinScreen);
		}
	}
}

void Stage::sLevel2::LoseCondition(LevelSetting& levelSetting, float dt)
{
	if (levelSetting.deadPlanetNum >= 3)
	{
		loseTimer += dt;
		if (loseTimer >= 2)
		{
			BE::Engine::BunnyEngine::instance()->flushStages();
			BE::Engine::BunnyEngine::instance()->pushActiveStage(new Stage::sLoseScreen);
		}
	}
}


void Stage::sLevel2::ShootPlayer(float dt)
{
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
