/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      sLegancyMenu.cpp
Purpose:        To update the menu as a tutorial with the star background
Language:       C++
Project:        GAM250
Author:         Name : minji.kim
Email:          seraminji2146@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/
#include <BunnyEngine.hpp>
#include <WIP/PropManager.hpp>
#include <WIP/Keyboard.hpp>

#include <GAME_SPECIFIC_FILES/sGameStage.hpp>
#include <GAME_SPECIFIC_FILES/sLegacyMenu.hpp>
#include <GAME_SPECIFIC_FILES/sConfirmQuit.hpp>
#include <GAME_SPECIFIC_FILES/sHowtoPlay.hpp>
#include <GAME_SPECIFIC_FILES/sOption.hpp>
#include <GAME_SPECIFIC_FILES/sCredit.hpp>
#include <GAME_SPECIFIC_FILES/sTutorial.hpp>
#include <GAME_SPECIFIC_FILES/logicFunctions.hh>
#include <GAME_SPECIFIC_FILES/inputAbstraction.hh>
#include <GAME_SPECIFIC_FILES/sRocketDestMenu.hpp>

namespace {
    const int STAR_MAX = 60;
}

Stage::sLegacyMenu::sLegacyMenu()
    : BaseStage("sLegacyMenu.stg"), _startup(false), b_menuMusicStart(false), 
				b_sndStation(false), b_sndPause(false) ,b_menuMusicRestart(false)
{
}

void
Stage::sLegacyMenu::start(std::string fileName_) {
    loadProps(fileName_);
    loadStageFile(fileName_);

    _backStar = getActor("BackStar");
    _camera = getActor("camera");

    MenuLvSetting.max_enemyNum = 0;
    MenuLvSetting.SetPlanetList(_actorVec);
    _player = getActor("player");
    //m_player.initData(getActor("player"), 30000000.f, 1000000.f, 0.95f, 4000000.f);
    m_player.initData(_player, 100000000.f, 2000000.f, 0.95f, 4000000.f);

    buttonNum = 1;
    BE::Core::Draw::instance()->setClearBufferColor(glm::vec3(24.f / 255.f, 24.f / 255.f, 48.f / 255.f));

    _mainPlanet = getActor("planet1-1");
    _startPlanet = getActor("planet2-1");
    _optionPlanet = getActor("planet1-2");
    _creditPlanet  = getActor("planet3-1");
    _tutorialSign = getActor("tutorialSign");
	_exitPlanet = getActor("planet1-3");
    _startSign = getActor("startSign");
    _creditSign = getActor("creditSign");
    _infoSign = getActor("InfoSign");
	_infoSignGamePad = getActor("InfoSignGampad");
    //_infoSign2 = getActor("")
    _startSignButtonA = getActor("startSignButtonA");
    _creditSignButtonA = getActor("creditSignButtonA");

    _mainPlanetDisplay = _mainPlanet->getComponent<BE::Component::Display>();

    for (int starNum = 0; starNum <= STAR_MAX; ++starNum) {
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
	m_player.flytoDestination(_mainPlanet, 1 / 600.f);
	_player->getComponent<BE::Component::Transform>()->scale = { 0.8, 0.8 };
	_player->getComponent<BE::Component::CircleCollider>()->radius = 200;

	//m_player.m_movestate = Player::MoveState::FLYING;

    _menuMusicStart = BE::PropManager::instance()->lookupValue("sndMenu");
    sndStation = BE::PropManager::instance()->lookupValue("sndStation");
			
    //_menuMusicEnd = BE::PropManager::instance()->lookupValue("sndVictory");


}

void
Stage::sLegacyMenu::resume()
{
				resumeSounds();

				if (_menuMusicStart->second->type == BE::Prop::AUDIO)
				{
								bool New = static_cast<BE::Prop::Audio*>(_menuMusicStart->second)->b_mute;
								if (New != b_menuMusicRestart) {
												static_cast<BE::Prop::Audio*>(_menuMusicStart->second)->stop();
												static_cast<BE::Prop::Audio*>(_menuMusicStart->second)->play();
								}
								b_menuMusicRestart = New;
				}
				
}

void
Stage::sLegacyMenu::pause()
{
				pauseSounds();
}

void
Stage::sLegacyMenu::update(float dt_)
{
				if (!_startup)
				{
								if (_menuMusicStart->second->type == BE::Prop::AUDIO && b_menuMusicStart == false)
								{
												static_cast<BE::Prop::Audio*>(_menuMusicStart->second)->play();
												b_menuMusicStart = true;
												//            _poke1->getComponent<BE::Component::Display>()->playAnim("animHericendreIntro", false);
								}

								_startup = true;
								findStations();
								findPlanets();
				}
	


    //static int i = 0;
    m_player.TailParticle(++increasingParticle);

	/*BE::Component::ParticleEmitter *particleEmitter = m_player.m_actor->getComponent<BE::Component::ParticleEmitter>();
	particleEmitter->setCapacity(100);
	particleEmitter->size.x = 20;
	particleEmitter->size.y = 50;
	particleEmitter->maxscale = 50;
	particleEmitter->maxvel = 50;
	particleEmitter->lifetime = 0.50f;
	particleEmitter->particleType = BE::ParticleType::ONE;
	particleEmitter->_texture.setTextureId("sprBasicParticle");
	particleEmitter->loop = true;*/

    //*    if (_menuMusicStart->second->type == BE::Prop::AUDIO)
    //    {
    //        static bool menuMusicPlay = false;
    //        if (!menuMusicPlay)
    //        {
    //            static_cast<BE::Prop::Audio*>(_menuMusicStart->second)->play();
    //                        _poke1->getComponent<BE::Component::Display>()->playAnim("animHericendreIntro", false);
    //            menuMusicPlay = true;
    //        }
    //    }
    //    if (_menuMusicEnd->second->type == BE::Prop::AUDIO)
    //    {
    //        static bool menuMusicStop = true;
    //        if (menuMusicStop)
    //        {
    //            if (_menuMusicEnd->second->type == BE::Prop::AUDIO)
    //            {
    //                static_cast<BE::Prop::Audio*>(_menuMusicEnd->second)->stop();
    //            }
    //            static_cast<BE::Prop::Audio*>(_menuMusicEnd->second)->play();
    //        }
    //    */}
     _camera->getComponent<BE::Component::Transform>()->position = -_player->getComponent<BE::Component::Transform>()->position;




    m_player.Update(MenuLvSetting, dt_);

    BE::Core::Physics* physicsInstance = BE::Core::Physics::instance();
    // Select button statement
    if ((Input::isTriggered(Input::POS_ACTION)))
    {
        for (auto & station : _stations)
        {
            if (m_player.m_movestate == Player::MoveState::STAND &&
                physicsInstance->Collision(_player, station) !=
                BE::Core::Physics::CS_NoCollision)
            {
                BE::Engine::BunnyEngine::instance()->pushActiveStage(new Stage::sRocketDestMenu(this));
                return;
            }
        }
    }
    if ((Input::isTriggered(Input::SUPER)))
    {
        if (m_player.m_movestate == Player::MoveState::STAND &&
            BE::Core::Physics::instance()->Collision(_player, _mainPlanet) !=
            BE::Core::Physics::CS_NoCollision)
        {
            _mainPlanetDisplay->textureColor = { BE::HBRandom::GetFloat(0,1.f),BE::HBRandom::GetFloat(0,1.f), BE::HBRandom::GetFloat(0,1.f) , 1 };
        }
        else if (m_player.m_movestate == Player::MoveState::STAND && physicsInstance->Collision(_player, _startPlanet) != BE::Core::Physics::CS_NoCollision)
        {
            //if (_menuMusicStart->second->type == BE::Prop::AUDIO && b_menuMusicStart == true)
            //{
            //    static_cast<BE::Prop::Audio*>(_menuMusicStart->second)->stop();
            //    b_menuMusicStart = false;
            //    //            _poke1->getComponent<BE::Component::Display>()->playAnim("animHericendreIntro", false);
            //}
												shutdownSounds();
            BE::Engine::BunnyEngine::instance()->flushStages();
            BE::Engine::BunnyEngine::instance()->pushActiveStage(new Stage::sGameStage("sLevel1.stg"));
            return;
        }
        else if (m_player.m_movestate == Player::MoveState::STAND && physicsInstance->Collision(_player, _optionPlanet) != BE::Core::Physics::CS_NoCollision)
        {
												if (_menuMusicStart->second->type == BE::Prop::AUDIO)
												{
																b_menuMusicRestart = static_cast<BE::Prop::Audio*>(_menuMusicStart->second)->b_mute;
												}
            BE::Engine::BunnyEngine::instance()->pushActiveStage(new Stage::sOption);
            return;
        }
        else if (m_player.m_movestate == Player::MoveState::STAND && physicsInstance->Collision(_player, _creditPlanet) != BE::Core::Physics::CS_NoCollision)
        {
            BE::Engine::BunnyEngine::instance()->pushActiveStage(new Stage::sCredit);
            return;
        }
        else if (m_player.m_movestate == Player::MoveState::STAND && physicsInstance->Collision(_player, _exitPlanet) != BE::Core::Physics::CS_NoCollision)
        {
            BE::Engine::BunnyEngine::instance()->pushActiveStage(new Stage::sConfirmQuit);
            return;
        }
    }


    if (BE::Core::Physics::instance()->Collision(_player, _tutorialSign) != BE::Core::Physics::CS_NoCollision)
    {
		

		if (m_player.m_inputstate == Player::InPutState::KEYBOARD)
		{
			if (_infoSign->_isActive == false)
			{
				_infoSign->_isActive = true;

			}
		}
		else if (m_player.m_inputstate == Player::InPutState::GAMEPAD)
		{
			if (_infoSignGamePad->_isActive == false)
			{
				_infoSignGamePad->_isActive = true;
			}
		}
    }
				else
				{

		if (m_player.m_inputstate == Player::InPutState::KEYBOARD)
		{
			if (_infoSign->_isActive == true)
			{
				_infoSign->_isActive = false;
				_infoSignGamePad->_isActive = false;
			}
		}
		else if (m_player.m_inputstate == Player::InPutState::GAMEPAD)
		{
			if (_infoSignGamePad->_isActive == true)
			{
				_infoSignGamePad->_isActive = false;
				_infoSign->_isActive = false;
			}
		}
    }
    //Start Sign Button A
    if (BE::Core::Physics::instance()->Collision(_player, _startSign) != BE::Core::Physics::CS_NoCollision)
    {
        if (_startSignButtonA->_isActive == false)
        {
            _startSignButtonA->_isActive = true;
        }
    }
    else
    {
        if (_startSignButtonA->_isActive == true)
        {
            _startSignButtonA->_isActive = false;
        }
    }
    //Credit Sign button A
    if (BE::Core::Physics::instance()->Collision(_player, _creditSign) != BE::Core::Physics::CS_NoCollision)
    {
        if (_creditSignButtonA->_isActive == false)
        {
            _creditSignButtonA->_isActive = true;
        }
    }
    else
    {
        if (_creditSignButtonA->_isActive == true)
        {
            _creditSignButtonA->_isActive = false;
        }
    }

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

    // Also, Player can escape with ESC
				if (BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_ESCAPE)) {
								pauseSounds();
								BE::Engine::BunnyEngine::instance()->pushActiveStage(new Stage::sConfirmQuit);
				}
}

void Stage::sLegacyMenu::findStations()
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

void Stage::sLegacyMenu::findPlanets()
{
    std::vector<BE::Actor*> planetVec;

    for (size_t i = 0; i < _actorVec.size(); ++i)
    {
        if (_actorVec[i]->_name.find("planet") != std::string::npos)
        {
            planetVec.push_back(_actorVec[i].get());
        }
    }

    size_t clusterId = 0;
    size_t planetId;
    for (size_t sortedPlanets = 0; sortedPlanets < planetVec.size(); )
    {
        ++clusterId;
        planetId = 1;
        _clusters.push_back(std::vector<BE::Actor*>());
        for (size_t i = 0; i < planetVec.size();)
        {
            std::stringstream planetName;
            planetName << "planet" << clusterId << "-" << planetId;
            if (planetVec[i]->_name == planetName.str())
            {
                _clusters[clusterId - 1].push_back(planetVec[i]);
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
void Stage::sLegacyMenu::shutdownSounds(void)
{
				if (_menuMusicStart->second->type == BE::Prop::AUDIO) {
								static_cast<BE::Prop::Audio*>(_menuMusicStart->second)->stop();
				}
				if (sndStation->second->type == BE::Prop::AUDIO) {
								static_cast<BE::Prop::Audio*>(sndStation->second)->stop();
				}

				m_player.shutdownSounds();
}

void Stage::sLegacyMenu::pauseSounds(void)
{
				if (_menuMusicStart->second->type == BE::Prop::AUDIO) {
								static_cast<BE::Prop::Audio*>(_menuMusicStart->second)->pause();
				}
				if (sndStation->second->type == BE::Prop::AUDIO) {
								static_cast<BE::Prop::Audio*>(sndStation->second)->pause();
				}

				m_player.pauseSounds();
}

void Stage::sLegacyMenu::resumeSounds(void)
{
				if (_menuMusicStart->second->type == BE::Prop::AUDIO) {
								static_cast<BE::Prop::Audio*>(_menuMusicStart->second)->resume();
				}
				if (sndStation->second->type == BE::Prop::AUDIO) {
								static_cast<BE::Prop::Audio*>(sndStation->second)->resume();
				}

				m_player.resumeSounds();
}
