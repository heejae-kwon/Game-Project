/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:    sOption.cpp
Purpose:       This file contain Option Menu.
player can do these
- turn on / off sound
- change resolution

Can be used C style with static functions or C++ with methods.
Language:     C++
Project:         GAM250
Author:         Name : Jihwan Oh
Email:            dkdkdkdudrn@gmail.com
date:			   2017.06.16
----------------------------------------------------------------------------*/
#include <GAME_SPECIFIC_FILES/sOption.hpp>
#include <GAME_SPECIFIC_FILES/inputAbstraction.hh>
#include <WIP/PropManager.hpp>

Stage::sOption::sOption()
    : BaseStage("sOption.stg"), b_musicoff(false)
{
    // Setting up the core config, by default everything is set to false
    {
        _stageLoadCoreConf.drawCore = true; // We want the draw core to keep drawing whatever was present while we display the confirm action pop up
    }
}

void
Stage::sOption::start(std::string fileName_)
{
    loadProps(fileName_);
    loadStageFile(fileName_);

    buttonNum = 1;
				//Music
				sndBG1= BE::PropManager::instance()->lookupValue("sndBG1");
				sndDigilogo = BE::PropManager::instance()->lookupValue("sndDigilogo");
				sndLose = BE::PropManager::instance()->lookupValue("sndLose");
				sndMenu = BE::PropManager::instance()->lookupValue("sndMenu");
				sndWin = BE::PropManager::instance()->lookupValue("sndWin");
				sndSpecial = BE::PropManager::instance()->lookupValue("sndSpecial");
			
				//SFX
								sndFly = BE::PropManager::instance()->lookupValue("sndFly");
								sndStation = BE::PropManager::instance()->lookupValue("sndStation");
								sndHit = BE::PropManager::instance()->lookupValue("sndHit");
								sndJump = BE::PropManager::instance()->lookupValue("sndJump");
	
    _starCursor = getActor("Star");
				_turnonSound = getActor("TurnonSound");

}

void
Stage::sOption::resume()
{
}

void
Stage::sOption::pause()
{
}

void
Stage::sOption::update(float /*dt_*/)
{
								if (sndBG1->second->type == BE::Prop::AUDIO)
				{
						_turnonSound->_isActive=		static_cast<BE::Prop::Audio*>(sndBG1->second)->b_mute;
				}

								//_turnonSound->_isActive = b_musicoff;
				for (auto & actor : _actorVec)
				{
								if (actor->_name == "Star")
								{
												switch (buttonNum)
												{
												case 1: {
																_starCursor->getComponent<BE::Component::Transform>()->position.x = 320;
																_starCursor->getComponent<BE::Component::Transform>()->position.y = 160;
												}break;
												case 2: {
																_starCursor->getComponent<BE::Component::Transform>()->position.x = 320;
																_starCursor->getComponent<BE::Component::Transform>()->position.y = 105;
												}break;
												case 3: {
																_starCursor->getComponent<BE::Component::Transform>()->position.x = 320;
																_starCursor->getComponent<BE::Component::Transform>()->position.y = 45;
												}break;
												case 4: {
																_starCursor->getComponent<BE::Component::Transform>()->position.x = 320;
																_starCursor->getComponent<BE::Component::Transform>()->position.y = -15;
												} break;
												case 5: {
																_starCursor->getComponent<BE::Component::Transform>()->position.x = 320;
																_starCursor->getComponent<BE::Component::Transform>()->position.y = -75;
												} break;
												case 6: {
																_starCursor->getComponent<BE::Component::Transform>()->position.x = 320;
																_starCursor->getComponent<BE::Component::Transform>()->position.y = -130;
												} break;
												case 7: {
																_starCursor->getComponent<BE::Component::Transform>()->position.x = 320;
																_starCursor->getComponent<BE::Component::Transform>()->position.y = -185;
												} break;
												case 8: {
																_starCursor->getComponent<BE::Component::Transform>()->position.x = 175;
																_starCursor->getComponent<BE::Component::Transform>()->position.y = -250;
												} break;
												case 9: {
																_starCursor->getComponent<BE::Component::Transform>()->position.x = 80;
												} break;
												default:
																break;
												}
								}
				}

				if (Input::isTriggered(Input::UP) && (buttonNum > 1 && buttonNum <= 8)) --buttonNum;
				if (Input::isTriggered(Input::DOWN) && (buttonNum >= 1 && buttonNum < 8)) ++buttonNum;
				if (Input::isTriggered(Input::LEFT) && (buttonNum == 3)) buttonNum = 9;
				if (Input::isTriggered(Input::RIGHT) && (buttonNum == 9)) buttonNum = 3;

				if (Input::isTriggered(Input::SUPER) || BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_RETURN))
				{
								switch (buttonNum)
								{

								case 1: { // Mute Music Only

												if (sndBG1->second->type == BE::Prop::AUDIO)
												{
																bool mute = static_cast<BE::Prop::Audio*>(sndBG1->second)->b_mute;
																if (mute == false)
																{
																				turnoffMusicSounds();
																}
																else
																{
																				turnonAllSounds();
																}
												}

								}break;
								case 2: { // Mute All Sound

												turnoffAllSounds();
								}break;

												// Mode
								case 9: { // If button is Full Screen
												BE::Core::Debugger::instance()->AddLog("[LOG][sOption::%s] Screen set to fullscreen", __func__);
												//BE::WindowAbst::instance()->resizeWindow(glm::vec2(1920, 1080));
												BE::WindowAbst::instance()->setFullscreen(true);

								}break;
								case 3: { // If button is WIndow Screen
												BE::Core::Debugger::instance()->AddLog("[LOG][sOption::%s] Screen set to windowed", __func__);
												//BE::WindowAbst::instance()->resizeWindow(glm::vec2(1280, 720));
												BE::WindowAbst::instance()->setFullscreen(false);
								}break;

												// Resolution
								case 4: { // 1280 960
												BE::Core::Debugger::instance()->AddLog("[LOG][sOption::%s] Screen Size set 1280 960", __func__);
												BE::WindowAbst::instance()->resizeWindow(glm::vec2(1280, 720));
								}break;
								case 5: { // 1280 1024
												BE::Core::Debugger::instance()->AddLog("[LOG][sOption::%s] Screen Size set 1280 1024", __func__);
												BE::WindowAbst::instance()->resizeWindow(glm::vec2(1280, 800));
								} break;
								case 6: { // 1600 900
												BE::Core::Debugger::instance()->AddLog("[LOG][sOption::%s] Screen Size set 1600 900", __func__);
												BE::WindowAbst::instance()->resizeWindow(glm::vec2(1600, 900));
								} break;
								case 7: { // 1600 1050
												BE::Core::Debugger::instance()->AddLog("[LOG][sOption::%s] Screen Size set 1680 1050", __func__);
												BE::WindowAbst::instance()->resizeWindow(glm::vec2(1920, 1080));
								} break;
								case 8: { // Quit
												BE::Engine::BunnyEngine::instance()->popActiveStage();
								} break;
								default:
												break;
								}
				}

				/*if (Input::isTriggered(Input::NEG_ACTION))
				{
								BE::Engine::BunnyEngine::instance()->popActiveStage();
								return;
				}*/

}

void Stage::sOption::turnoffMusicSounds(void)
{
				if (sndBG1->second->type == BE::Prop::AUDIO)
				{
								static_cast<BE::Prop::Audio*>(sndBG1->second)->turnoff();
				}
				if (sndDigilogo->second->type == BE::Prop::AUDIO)
				{
								static_cast<BE::Prop::Audio*>(sndDigilogo->second)->turnoff();
				}
				if (sndLose->second->type == BE::Prop::AUDIO)
				{
								static_cast<BE::Prop::Audio*>(sndLose->second)->turnoff();
				}
				if (sndMenu->second->type == BE::Prop::AUDIO)
				{
								static_cast<BE::Prop::Audio*>(sndMenu->second)->turnoff();
				}
				if (sndSpecial->second->type == BE::Prop::AUDIO)
				{
								static_cast<BE::Prop::Audio*>(sndSpecial->second)->turnoff();
				}
				if (sndWin->second->type == BE::Prop::AUDIO)
				{
								static_cast<BE::Prop::Audio*>(sndWin->second)->turnoff();
				}
}

void Stage::sOption::turnoffAllSounds(void)
{
				turnoffMusicSounds();

				if (sndFly->second->type == BE::Prop::AUDIO)
				{
								static_cast<BE::Prop::Audio*>(sndFly->second)->turnoff();
				}
				if (sndHit->second->type == BE::Prop::AUDIO)
				{
								static_cast<BE::Prop::Audio*>(sndHit->second)->turnoff();
				}
				if (sndJump->second->type == BE::Prop::AUDIO)
				{
								static_cast<BE::Prop::Audio*>(sndJump->second)->turnoff();
				}
				if (sndStation->second->type == BE::Prop::AUDIO)
				{
								static_cast<BE::Prop::Audio*>(sndStation->second)->turnoff();
				}
}



void Stage::sOption::turnonMusicSounds(void)
{
				if (sndBG1->second->type == BE::Prop::AUDIO)
				{
								static_cast<BE::Prop::Audio*>(sndBG1->second)->turnon();
				}
				if (sndDigilogo->second->type == BE::Prop::AUDIO)
				{
								static_cast<BE::Prop::Audio*>(sndDigilogo->second)->turnon();
				}
				if (sndLose->second->type == BE::Prop::AUDIO)
				{
								static_cast<BE::Prop::Audio*>(sndLose->second)->turnon();
				}
				if (sndMenu->second->type == BE::Prop::AUDIO)
				{
								static_cast<BE::Prop::Audio*>(sndMenu->second)->turnon();
				}
				if (sndSpecial->second->type == BE::Prop::AUDIO)
				{
								static_cast<BE::Prop::Audio*>(sndSpecial->second)->turnon();
				}
				if (sndWin->second->type == BE::Prop::AUDIO)
				{
								static_cast<BE::Prop::Audio*>(sndWin->second)->turnon();
				}
}

void Stage::sOption::turnonAllSounds(void)
{
				turnonMusicSounds();

				if (sndFly->second->type == BE::Prop::AUDIO)
				{
								static_cast<BE::Prop::Audio*>(sndFly->second)->turnon();
				}
				if (sndHit->second->type == BE::Prop::AUDIO)
				{
								static_cast<BE::Prop::Audio*>(sndHit->second)->turnon();
				}
				if (sndJump->second->type == BE::Prop::AUDIO)
				{
								static_cast<BE::Prop::Audio*>(sndJump->second)->turnon();
				}
				if (sndStation->second->type == BE::Prop::AUDIO)
				{
								static_cast<BE::Prop::Audio*>(sndStation->second)->turnon();
				}
}
