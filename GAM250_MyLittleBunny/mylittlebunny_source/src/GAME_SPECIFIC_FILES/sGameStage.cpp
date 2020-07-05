/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      sGameStage.cpp
Purpose:        Entry point of our program
Language:       C++
Project:        GAM250
Author:         Name : minji.kim, Stuat Sulaski, Wonjae Jung(particle)
Email:          seraminji2146@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#include <BunnyEngine.hpp>
#include <WIP/PropManager.hpp>
#include <Utilities/JsonWriter.hh>
#include <Utilities/JsonReader.hh>
#include <Abstractions/RenderAbst.hpp>
#include <GAME_SPECIFIC_FILES/LevelSetting.hpp>

#include <GAME_SPECIFIC_FILES/sGameStage.hpp>
#include <GAME_SPECIFIC_FILES/sHowtoPlay.hpp>
#include <GAME_SPECIFIC_FILES/sESCMenu.hpp>
#include <GAME_SPECIFIC_FILES/sHowtoKill.hpp>
#include <GAME_SPECIFIC_FILES/sHowtoPowerup.hpp>
#include <GAME_SPECIFIC_FILES/sConfirmMenu.hpp>
#include <GAME_SPECIFIC_FILES/sWinScreen.hpp>
#include <GAME_SPECIFIC_FILES/sLoseScreen.hpp>
#include <GAME_SPECIFIC_FILES/sRocketDestinationSelect.hpp>
#include <GAME_SPECIFIC_FILES/logicFunctions.hh>
#include <GAME_SPECIFIC_FILES/inputAbstraction.hh>


#include <WIP/HBRandom.hpp>
namespace {
    const int  STAR_MAX = 40;
    const int SUPER_NUMBER = 10;
    const float SUPER_DURATION = 10.f;
}


Stage::sGameStage::sGameStage(std::string fileName_)
    : BaseStage((fileName_ == "") ? "sLevel1.stg" : fileName_.c_str()), _mustExit(false), _startup(false), winTimer(0), loseTimer(0),
				b_sndStation(false), b_restart(false)
{
    fileName = (fileName_ == "") ? "sLevel1.stg" : fileName_;
}


void
Stage::sGameStage::start(std::string fileName_)
{
    loadProps(fileName_);
    loadStageFile(fileName_);

    // Setting the background color
    BE::Core::Draw::instance()->setClearBufferColor(glm::vec3(0.f, 0.f, 0.f));

    // "Getting" actos for use in the stage
    {
        _stageConfig = getActor("_LevelSetting")->getComponent<BE::Component::Gameplay>();
        // Setting level settings
        if (_stageConfig != nullptr)
        {
            levelsetting._waveAlarm = getActor("WaveAlarm");

            levelsetting.start_enemyNum = _stageConfig->startingNbrEnemies;
            levelsetting.waveConditionNum = levelsetting.start_enemyNum;
            levelsetting.step_enemyNum = _stageConfig->numberEnemyStep;
            levelsetting.numberOfRounds = _stageConfig->numberOfRounds;
            levelsetting.max_enemyNum += levelsetting.start_enemyNum;
            int enemy_perWave = 0;
            for (int i = 0; i < levelsetting.numberOfRounds; ++i) {
                levelsetting.max_enemyNum += enemy_perWave;
                enemy_perWave += levelsetting.step_enemyNum;
            }
            levelsetting.player = &m_player;
            levelsetting.SetPlanetList(_actorVec);
            levelsetting.GenerateHPbar(_actorVec);
            levelsetting.GenerateEnemyList(_actorVec);
            levelsetting.SetEnemyList(_actorVec);
            levelsetting.generateTime = 5;

            BE::Actor *maxRound = getActor("waveNumber");
            maxRound->getComponent<BE::Component::Display>()->spriteIndex = _stageConfig->numberOfRounds + 1;
        }

        _hud = getActor("hud");

		_firstPlanet = getActor("planet1-1");
		_GageBar = getActor("GageBar");
        _GageBound = getActor("GageBound");
        _GageBunny = getActor("GageBunny");
        _player = getActor("player");
        _camera = getActor("camera");
        _feverTime = getActor("Fever");
        _superstandHUD = getActor("SuperStandHUD");

        _xKey = getActor("xHelp");
        _Arrow2 = getActor("ArrowHUD2");

        _firstNumber = getActor("firstNumber");
        _secondNumber = getActor("secondNumber");
        _waveNumber = getActor("leftWaveNumber");
        _waveNumber->getComponent<BE::Component::Display>()->spriteIndex = 1;

        _CheatAvailableActor = getActor("CheatAvailable");
		_GODMODEActor = getActor("GODMODE");
        _cheatAvailable = false;
		_godmodeAvailable = false;
        _cheatEnemyDamage = false;
        _explainAkey = false;
        _explainHowtoKill = false;
        _rule = getActor("ruleHUD");
        //When level is started always rule is displayed
        _rule->_isActive = true;
    }

    // Initialising the game actors
    {
        m_player.initData(_player, 100000000.f, 2000000.f, 0.95f, 4000000.f);
        m_camera.setActor(_camera);
    }

    generateStars(); // Generates the stary background

    //Init Sounds
    sndBackground = BE::PropManager::instance()->lookupValue("sndBG1");
    sndPowerup = BE::PropManager::instance()->lookupValue("sndSpecial");
    sndStation = BE::PropManager::instance()->lookupValue("sndStation");

	m_player.flytoDestination(_firstPlanet, 1 / 600.f);
	_player->getComponent<BE::Component::Transform>()->scale = { 0.8, 0.8 };
	_player->getComponent<BE::Component::CircleCollider>()->radius = 200;
}

void
Stage::sGameStage::resume()
{
				_mustExit = false;
				resumeSounds();

				if (sndBackground->second->type == BE::Prop::AUDIO)
				{
								bool New = static_cast<BE::Prop::Audio*>(sndBackground->second)->b_mute;
								if (New != b_restart) {
												static_cast<BE::Prop::Audio*>(sndBackground->second)->stop();
												static_cast<BE::Prop::Audio*>(sndBackground->second)->play();
								}
								b_restart = New;
				}
}

void
Stage::sGameStage::pause()
{
    pauseSounds();
}

void
Stage::sGameStage::update(float dt_)
{
    //static int i = 0;
    //m_player.TailParticle(i++);
	if(increasingParticle < 200)
		m_player.TailParticle(++increasingParticle);
	
    //Display & Hide the Rule
    //This code SHOULD be placed in top.
    if (_rule->_isActive == true) {
        _player->_isActive = false;

        if (Input::isTriggered(Input::JUMP) || BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_RETURN)) {
            _rule->_isActive = false;
            _player->_isActive = true;
        }
        return;
    }

    //play the backGround music
    //Maybe it should stop when Win particles are active


    if (!_startup) {
        _startup = true;
        if (sndBackground->second->type == BE::Prop::AUDIO) {
            static_cast<BE::Prop::Audio*>(sndBackground->second)->play();
        }
        findStations();
        findPlanets();
    }

    onInput(); // Everything that is triggered by an input is in here
    if (_mustExit)
    {
        return;
    }

    // Calling update functions of game actors
    {
        levelsetting.GenerateEnemy(1, dt_);
        for (auto & planets : levelsetting.planetVector)
        {
            planets.Update(levelsetting, dt_);
        }

        if (levelsetting.deadPlanetNum != levelsetting.max_planetNum)
            for (auto & enemies : levelsetting.enemyVector)
            {
                enemies.Update(levelsetting, dt_);
            }

        m_camera.setPosition(glm::vec3(-m_player.getAnchorPoint(), 1.0f));
        m_camera.Update(dt_);
        m_player.Update(levelsetting, dt_);
    }

    updateNumbers();
    updateWaveNumbers(levelsetting);
    updateSuperHUD(dt_);
    StationAnimation(dt_);
    //WinCondition(levelsetting, dt_);
    //LoseCondition(levelsetting, dt_);
    //Win Condition
    if (levelsetting.deadEnemyNum >= levelsetting.max_enemyNum)
    {
        winTimer += dt_;

        //setMoveForce(CHANGE_MOVE_FORCE);
        //levelSetting.player->m_actor->getComponent<BE::Component::ParticleEmitter>()->m_change = true;
        //BE::Component::ParticleEmitter *particleEmitter = levelsetting.player->m_actor->getComponent<BE::Component::ParticleEmitter>();
		BE::Component::ParticleEmitter *particleEmitter = levelsetting.player->m_actor->getComponent<BE::Component::ParticleEmitter>();
        particleEmitter->setCapacity(100);
        particleEmitter->size.x = 100;
        particleEmitter->size.y = 100;
        particleEmitter->maxscale = 500;
        particleEmitter->maxvel = 500;
        particleEmitter->lifetime = 1.5f;
        particleEmitter->particleType = BE::ParticleType::FOUR;
        particleEmitter->_texture.setTextureId("sprFireWork");
        particleEmitter->loop = true;
        //particleEmitter->resetParticles();


        if (winTimer >= 3) {
            //Stop Background sound

												shutdownSounds();

            BE::Engine::BunnyEngine* engine = BE::Engine::BunnyEngine::instance();
            if (!_stageConfig->isFinalLevel)
            {
				increasingParticle = 0;
                std::string nextLevelName = _stageConfig->nextLevelName;
                engine->popActiveStage();
                engine->pushActiveStage(new Stage::sGameStage(nextLevelName));
            }
            else
            {
                engine->flushStages();
                engine->pushActiveStage(new Stage::sWinScreen);
            }
            return;
        }
		
    }
    //Lose Condition
    if (levelsetting.deadPlanetNum >= 3) {
        loseTimer += dt_;
		BE::Component::ParticleEmitter *particleEmitter = levelsetting.player->m_actor->getComponent<BE::Component::ParticleEmitter>();
		particleEmitter->setCapacity(100);
		particleEmitter->size.x = 100;
		particleEmitter->size.y = 100;
		particleEmitter->maxscale = 500;
		particleEmitter->maxvel = 500;
		particleEmitter->lifetime = 1.5f;
		particleEmitter->particleType = BE::ParticleType::THREE;
		particleEmitter->_texture.setTextureId("sprParticle");
		particleEmitter->loop = true;

        if (loseTimer >= 2) {
            //Stop Background sound

												shutdownSounds();

            BE::Engine::BunnyEngine::instance()->flushStages();
            BE::Engine::BunnyEngine::instance()->pushActiveStage(new Stage::sLoseScreen);
            return;
        }
    }

	if (_cheatAvailable)
	{
		
		// Jump to the other Stage
		if (BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_1))
		{
			//Stop Background sound
			shutdownSounds();

			BE::Engine::BunnyEngine* engine = BE::Engine::BunnyEngine::instance();
			engine->popActiveStage();
			engine->pushActiveStage(new Stage::sGameStage("sLevel1.stg"));
		}
		else if (BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_2))
		{
			//Stop Background sound
			shutdownSounds();

			BE::Engine::BunnyEngine* engine = BE::Engine::BunnyEngine::instance();
			engine->popActiveStage();
			engine->pushActiveStage(new Stage::sGameStage("sLevel1-1.stg"));
		}
		else if (BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_3))
		{
			//Stop Background sound
			shutdownSounds();

			BE::Engine::BunnyEngine* engine = BE::Engine::BunnyEngine::instance();
			engine->popActiveStage();
			engine->pushActiveStage(new Stage::sGameStage("sLevel2-2.stg"));
		}
		else if (BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_4))
		{
			//Stop Background sound
			shutdownSounds();

			BE::Engine::BunnyEngine* engine = BE::Engine::BunnyEngine::instance();
			engine->popActiveStage();
			engine->pushActiveStage(new Stage::sGameStage("sLevel2.stg"));
		}
		else if (BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_5))
		{
			//Stop Background sound
			shutdownSounds();

			BE::Engine::BunnyEngine* engine = BE::Engine::BunnyEngine::instance();
			engine->popActiveStage();
			engine->pushActiveStage(new Stage::sGameStage("sLevel3.stg"));
		}
		else if (BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_6))
		{
			//Stop Background sound
			shutdownSounds();

			BE::Engine::BunnyEngine* engine = BE::Engine::BunnyEngine::instance();
			engine->popActiveStage();
			engine->pushActiveStage(new Stage::sGameStage("sLevel4.stg"));
		}
		if (BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_0))
		{
			//Stop Background sound
			shutdownSounds();

			BE::Engine::BunnyEngine* engine = BE::Engine::BunnyEngine::instance();
			engine->flushStages();
			engine->pushActiveStage(new Stage::sWinScreen);
			return;
		}
		if (BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_9))
		{
			//Stop Background sound
			shutdownSounds();

			BE::Engine::BunnyEngine* engine = BE::Engine::BunnyEngine::instance();
			engine->flushStages();
			engine->pushActiveStage(new Stage::sLoseScreen);
			return;
		}

	}
		
}

void Stage::sGameStage::generateStars()
{
    for (int starNum = 0; starNum <= STAR_MAX; ++starNum)
    {
        std::stringstream StarName;
        StarName << "BackStar" << starNum;
        BE::Actor* actor = BE::Engine::BunnyEngine::instance()->getActiveStage()->addActor(BE::Actor::createActor(StarName.str(), true));

        actor->getComponent<BE::Component::Transform>()->position = glm::vec3(BE::HBRandom::GetInt(-600, 600), BE::HBRandom::GetInt(-300, 300), -9);
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

void Stage::sGameStage::StationAnimation(float dt_)
{
    for (auto & station : _stations)
    {
        BE::Component::Display* stationDisplay = station->getComponent<BE::Component::Display>();
															static float sndStationTime = 0;
								if (b_sndStation == true) {
												sndStationTime += dt_;
								}
        if (BE::Core::Physics::instance()->Collision(_player, station) != BE::Core::Physics::CS_NoCollision)
        {
												if (stationDisplay->spriteIndex == 1)
												{
																stationDisplay->playAnim("animRocketLauncher", false);
																stationDisplay->spriteIndex = 2;
																if (sndStation->second->type == BE::Prop::AUDIO && b_sndStation == false) {
																				static_cast<BE::Prop::Audio*>(sndStation->second)->play();
																				b_sndStation = true;
																}
												}
        }
        else
        {
            stationDisplay->animPlaying = false;
												if (stationDisplay->spriteIndex == 2) {
																				stationDisplay->spriteIndex = 1;
																if (sndStation->second->type == BE::Prop::AUDIO && sndStationTime >= 1.5f) {
																				static_cast<BE::Prop::Audio*>(sndStation->second)->stop();
																				b_sndStation = false;
																				sndStationTime = 0;
																}
												}
        }
    }
}


void Stage::sGameStage::pauseSounds(void)
{
				//Stop Background sound
				if (sndBackground->second->type == BE::Prop::AUDIO) {
								static_cast<BE::Prop::Audio*>(sndBackground->second)->pause();
				}
				if (sndPowerup->second->type == BE::Prop::AUDIO) {
								static_cast<BE::Prop::Audio*>(sndPowerup->second)->pause();
				}
				if (sndStation->second->type == BE::Prop::AUDIO) {
								static_cast<BE::Prop::Audio*>(sndStation->second)->pause();
				}

				m_player.pauseSounds();
}

void Stage::sGameStage::resumeSounds(void)
{
								//Stop Background sound
				if (sndBackground->second->type == BE::Prop::AUDIO) {
								static_cast<BE::Prop::Audio*>(sndBackground->second)->resume();
				}
				if (sndPowerup->second->type == BE::Prop::AUDIO) {
								static_cast<BE::Prop::Audio*>(sndPowerup->second)->resume();
				}
				if (sndStation->second->type == BE::Prop::AUDIO) {
								static_cast<BE::Prop::Audio*>(sndStation->second)->resume();
				}

				//player's
				m_player.resumeSounds();
}

void Stage::sGameStage::shutdownSounds(void)
{
				//Stop Background sound
				if (sndBackground->second->type == BE::Prop::AUDIO) {
								static_cast<BE::Prop::Audio*>(sndBackground->second)->stop();
				}
				if (sndPowerup->second->type == BE::Prop::AUDIO) {
								static_cast<BE::Prop::Audio*>(sndPowerup->second)->stop();
				}
				if (sndStation->second->type == BE::Prop::AUDIO) {
								static_cast<BE::Prop::Audio*>(sndStation->second)->stop();
				}

				m_player.shutdownSounds();
}


void Stage::sGameStage::findStations()
{
    std::vector<BE::Actor*> stationVec;

    for (size_t i = 0; i < _actorVec.size(); ++i)
    {
        if (_actorVec[i]->_name.find("station") != std::string::npos)
        {
            stationVec.push_back(_actorVec[i].get());
        }
    }

    size_t stationId = 1;
    for (size_t i = 0; i < stationVec.size();)
    {
        std::stringstream stationName;
        stationName << "station" << stationId;
        if (stationVec[i]->_name == stationName.str())
        {
            _stations.push_back(stationVec[i]);
            ++stationId;
            i = 0;
        }
        else
        {
            ++i;
        }
    }
}

void Stage::sGameStage::findPlanets()
{
    std::vector<Planet*> planetVec;


    for (size_t i = 0; i < levelsetting.planetVector.size(); ++i)
    {
        if (levelsetting.planetVector[i].GetOwner()->_name.find("planet") != std::string::npos)
        {
            planetVec.push_back(&levelsetting.planetVector[i]);
        }
    }

    size_t clusterId = 0;
    size_t planetId;
    for (size_t sortedPlanets = 0; sortedPlanets < planetVec.size(); )
    {
        ++clusterId;
        planetId = 1;
        _clusters.push_back(std::vector<Planet*>());
        for (size_t i = 0; i < planetVec.size();)
        {
            std::stringstream planetName;
            planetName << "planet" << clusterId << "-" << planetId;
            if (levelsetting.planetVector[i].GetOwner()->_name == planetName.str())
            {
                _clusters[clusterId - 1].push_back(&levelsetting.planetVector[i]);
                ++planetId;
                ++sortedPlanets;
                i = 0;
            }
            else
            {
                ++i;
            }
        }
    }
}


void Stage::sGameStage::onInput()
{
    // Cheat Codes
    {
        _CheatAvailableActor->_isActive = _cheatAvailable;
        if (BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_F10))
        {
            // Switch the Cheat Code
            _cheatAvailable = !_cheatAvailable;
        }
        if (_cheatAvailable) // Use cheat code
        {
            // Set Planet's health to 500
            if (BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_p))
            {
                for (auto & planets : levelsetting.planetVector)
                {
                    planets.setHealth(500);
                }
            }

			
            // Set Player power maximum.
            if (BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_o))
                levelsetting.player->m_powerGage = 100;

			if (BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_g))
			{
				_godmodeAvailable = !_godmodeAvailable;
				_GODMODEActor->_isActive = _godmodeAvailable;
				for (auto & planets : levelsetting.planetVector)
				{
					planets.immortal = _godmodeAvailable;
				}
			}

		
            if (BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_i))
            {
                if (_cheatEnemyDamage)
                    for (auto & enemies : levelsetting.enemyVector)
                    {
                        enemies.e_damageMaxTimer = 0.5f;
                    }
                else
                    for (auto & enemies : levelsetting.enemyVector)
                    {
                        enemies.e_damageMaxTimer = 2.f;
                    }
                _cheatEnemyDamage = !_cheatEnemyDamage;
            }

        }
    }

    if (Input::isTriggered(Input::START))
    {
								pauseSounds();
								if (sndBackground->second->type == BE::Prop::AUDIO)
								{
												b_restart = static_cast<BE::Prop::Audio*>(sndBackground->second)->b_mute;
								}
        BE::Engine::BunnyEngine::instance()->pushActiveStage(new sESCMenu(fileName));
    }

    if (Input::isTriggered(Input::POS_ACTION))
    {
        for (auto & station : _stations)
        {
            if (m_player.m_movestate == Player::MoveState::STAND && BE::Core::Physics::instance()->Collision(_player, station) != BE::Core::Physics::CS_NoCollision)
            {

                BE::Engine::BunnyEngine::instance()->pushActiveStage(new Stage::sRocketDestinationSelect(this));
                _mustExit = true;

                return;
            }
        }
    }


}

void Stage::sGameStage::updateSuperHUD(float dt_)
{
    //Hud bar to change for special mode bunnuy
    int hudTexId = 5;
    //   if (levelsetting.deadEnemyNum > 2)
    hudTexId -= static_cast<int>(levelsetting.powerupCount / 2);


    // Set the bar size with player's energe
    float gageRatio = m_player.m_powerGage / 10.f;

    if (gageRatio >= 1.f) {
        gageRatio = 1.f;
        _xKey->_isActive = true;
    }
	if (gageRatio <= 0.f)
		gageRatio = 0.f;

    BE::Component::Transform * superBarTransform = _GageBar->getComponent<BE::Component::Transform>();
    superBarTransform->scale.y = gageRatio;
    superBarTransform->position.y =
        _GageBound->getComponent<BE::Component::Transform>()->position.y - 200 * (1 - gageRatio);

    //if (hudTexId > 0) {
    //    _hud->getComponent<BE::Component::Display>()->setTextureId("sprHUD", hudTexId);
    //    //_superstandHUD->_isActive = true;
    //}
	if (_stageConfig->nextLevelName == "sLevel1-1.stg")
	{
		if(!_explainHowtoKill)
			for (auto & enemies : levelsetting.enemyVector)
			{
				if (enemies.GetCondition() == cond_WORKING)
				{
					_explainHowtoKill = true;
					BE::Engine::BunnyEngine::instance()->pushActiveStage(new sHowtoKill);
				}
			}
	}
    if (_stageConfig->nextLevelName == "sLevel2-2.stg")
    {
        if (gageRatio >= 1.f && _explainAkey == false)
        {
            _explainAkey = true;
            BE::Engine::BunnyEngine::instance()->pushActiveStage(new sHowtoPowerup);
        }
    }

    static float time = 0;
    static bool super = false;
    //Condtion that when SUPER is started
	if (gageRatio == 1.f ) {

		
		_GageBunny->getComponent<BE::Component::Display>()->playAnim("animGage", true);
		_feverTime->_isActive = true;


	}
    if (gageRatio >= 1.f && Input::isTriggered(Input::SUPER) && super == false) {

        m_player.powerUp();

        //Play the PowerUp sound
        if (sndPowerup->second->type == BE::Prop::AUDIO) {
            static_cast<BE::Prop::Audio*>(sndPowerup->second)->play();
        }
        super = true;
    }

    if (super == true)
    {
        levelsetting.player->m_powerGage -= dt_ /*/ SUPER_DURATION*/;
        time += dt_;
    }
    //End condition of SUPER
    if (time > SUPER_DURATION) {
        _feverTime->_isActive = false;
        _xKey->_isActive = false;
        _GageBunny->getComponent<BE::Component::Display>()->stopAnim();
        m_player.powerDown();
        time = 0;
        levelsetting.powerupCount = 0;
        //Stop the PowerUp sound
        if (sndPowerup->second->type == BE::Prop::AUDIO) {
            static_cast<BE::Prop::Audio*>(sndPowerup->second)->stop();
        }
        super = false;
    }
}


void Stage::sGameStage::updateNumbers()
{
    int i = 0;
    for (auto & enemies : levelsetting.enemyVector)
    {
        if (enemies.GetOwner()->_isActive)
        {
            ++i;
        }
    }
    if (i >= 10)
    {
        int j = i % 10;
        _secondNumber->getComponent<BE::Component::Display>()->spriteIndex = j + 1;
        i = i / 10;
        _firstNumber->getComponent<BE::Component::Display>()->spriteIndex = i + 1;
    }
    else
    {
        _firstNumber->getComponent<BE::Component::Display>()->spriteIndex = 1;
        _secondNumber->getComponent<BE::Component::Display>()->spriteIndex = i + 1;
    }
}

void Stage::sGameStage::updateWaveNumbers(LevelSetting& levelSetting)
{
    static bool oldAlarmState = false;

    if ((levelSetting._waveAlarm->_isActive == true) && (levelSetting._waveAlarm->_isActive != oldAlarmState))
    {
        _waveNumber->getComponent<BE::Component::Display>()->spriteIndex += 1;
    };

    oldAlarmState = levelSetting._waveAlarm->_isActive;
}
