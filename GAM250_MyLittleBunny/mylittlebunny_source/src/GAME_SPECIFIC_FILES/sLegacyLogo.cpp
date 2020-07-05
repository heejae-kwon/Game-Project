/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      sLegacyLogo.cpp
Purpose:        create the logo stage.
Language:       C++
Project:        GAM250
Author:         Name : wonjae.jung
Email:          wonjae0925@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/
#include <BunnyEngine.hpp>
#include <WIP/PropManager.hpp>
#include <WIP/Keyboard.hpp>
#include <WIP\Gamepad.hpp>

#include <GAME_SPECIFIC_FILES/sLegacyLogo.hpp>
#include <GAME_SPECIFIC_FILES/sLegacyMenu.hpp>

Stage::sLegacyLogo::sLegacyLogo()
    : BaseStage("sLegacyLogo.stg"), _elapsedTime(0.f)  /*_firstLogo(true), _secondLogo(false)*/
{
}

void
Stage::sLegacyLogo::start(std::string fileName_)
{
    loadProps(fileName_);
    loadStageFile(fileName_);


    _digiLogo = getActor("DigipenLogo");
    _teamLogo = getActor("TeamLogo");

				//
				_fmodLogo = getActor("FmodLogo");
				_gamepadLogo = getActor("GamepadLogo");
				_story = getActor("Story");
				_storyToStart = getActor("StoryToStart");
    if (_teamLogo != nullptr)
    {
        _teamLogo->_isActive = false;
    }
				if (_fmodLogo != nullptr) {
								_fmodLogo->_isActive = false;
				}
				if (_gamepadLogo != nullptr) {
								_gamepadLogo->_isActive = false;
				}
				if (_story != nullptr) {
					_story->_isActive = false;
				}


				//Sound Init
				sndDigilogo = BE::PropManager::instance()->lookupValue("sndDigilogo");
				sndStory = BE::PropManager::instance()->lookupValue("sndStory");
				b_phaseout = false;
				b_sound = false;

}

void
Stage::sLegacyLogo::resume()
{
				if (sndDigilogo->second->type == BE::Prop::AUDIO) {
								static_cast<BE::Prop::Audio*>(sndDigilogo->second)->resume();
				}
				if (sndStory->second->type == BE::Prop::AUDIO) {
								static_cast<BE::Prop::Audio*>(sndStory->second)->resume();
				}
}

void
Stage::sLegacyLogo::pause()
{
				if (sndDigilogo->second->type == BE::Prop::AUDIO) {
								static_cast<BE::Prop::Audio*>(sndDigilogo->second)->pause();
				}
				if (sndStory->second->type == BE::Prop::AUDIO) {
								static_cast<BE::Prop::Audio*>(sndStory->second)->pause();
				}

}

void
Stage::sLegacyLogo::update(float dt_)
{
    _elapsedTime += dt_;
				float phaseTime = dt_*0.8f;

    if (_digiLogo->_isActive == true)
    {
								if (sndDigilogo->second->type == BE::Prop::AUDIO && b_sound == false) {
            static_cast<BE::Prop::Audio*>(sndDigilogo->second)->play();
												b_sound = true;
        }


								if (_digiLogo->getComponent<BE::Component::Display>()->textureColor.a >=1) {
											b_phaseout	 = true;
								}

								if (b_phaseout) {
												_digiLogo->getComponent<BE::Component::Display>()->textureColor.a -= phaseTime;
								}
								else {
												_digiLogo->getComponent<BE::Component::Display>()->textureColor.a += phaseTime;
								}


        if (_elapsedTime > 3.0f ||
												BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_ANY)	||
												BE::Input::Gamepad::instance()->IsTriggered(BE::GP::BUTTON_A) ||
												BE::Input::Gamepad::instance()->IsTriggered(BE::GP::BUTTON_X) ||
												BE::Input::Gamepad::instance()->IsTriggered(BE::GP::BUTTON_Y) ||
												BE::Input::Gamepad::instance()->IsTriggered(BE::GP::BUTTON_B))
        {
            _digiLogo->_isActive = false;
            _fmodLogo->_isActive = true;
												b_phaseout = false;
            _elapsedTime = 0.f;
        }
    }
				else if (_fmodLogo->_isActive == true)
    {
								if (_fmodLogo->getComponent<BE::Component::Display>()->textureColor.a >=1) {
											b_phaseout	 = true;
								}

								if (b_phaseout) {
												_fmodLogo->getComponent<BE::Component::Display>()->textureColor.a -= phaseTime;
								}
								else {
												_fmodLogo->getComponent<BE::Component::Display>()->textureColor.a += phaseTime;
								}


        if (_elapsedTime > 3.0f ||
												BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_ANY)	||
												BE::Input::Gamepad::instance()->IsTriggered(BE::GP::BUTTON_A) ||
												BE::Input::Gamepad::instance()->IsTriggered(BE::GP::BUTTON_X) ||
												BE::Input::Gamepad::instance()->IsTriggered(BE::GP::BUTTON_Y) ||
												BE::Input::Gamepad::instance()->IsTriggered(BE::GP::BUTTON_B))
        {
            _fmodLogo->_isActive = false;
												_teamLogo->_isActive = true;
												b_phaseout = false;
            _elapsedTime = 0.f;
        }
    }
				else if (_teamLogo->_isActive == true)
    {
								if (_teamLogo->getComponent<BE::Component::Display>()->textureColor.a >=1) {
											b_phaseout	 = true;
								}

								if (b_phaseout) {
												_teamLogo->getComponent<BE::Component::Display>()->textureColor.a -= phaseTime;
								}
								else {
												_teamLogo->getComponent<BE::Component::Display>()->textureColor.a +=phaseTime;
								}


        if (_elapsedTime > 3.0f || 
												BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_ANY)	||
												BE::Input::Gamepad::instance()->IsTriggered(BE::GP::BUTTON_A) ||
												BE::Input::Gamepad::instance()->IsTriggered(BE::GP::BUTTON_X) ||
												BE::Input::Gamepad::instance()->IsTriggered(BE::GP::BUTTON_Y) ||
												BE::Input::Gamepad::instance()->IsTriggered(BE::GP::BUTTON_B))
 
        {
												_teamLogo->_isActive = false;
												_gamepadLogo->_isActive = true;
												b_phaseout = false;
            _elapsedTime = 0.f;
        }
    }
    else if (_gamepadLogo->_isActive == true)
    {
								if (_gamepadLogo->getComponent<BE::Component::Display>()->textureColor.a >=1) {
											b_phaseout	 = true;
								}

								if (b_phaseout) {
												_gamepadLogo->getComponent<BE::Component::Display>()->textureColor.a -= phaseTime;
								}
								else {
												_gamepadLogo->getComponent<BE::Component::Display>()->textureColor.a += phaseTime;
								}


								if (_elapsedTime > 3.0f ||
												BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_ANY) ||
												BE::Input::Gamepad::instance()->IsTriggered(BE::GP::BUTTON_A) ||
												BE::Input::Gamepad::instance()->IsTriggered(BE::GP::BUTTON_X) ||
												BE::Input::Gamepad::instance()->IsTriggered(BE::GP::BUTTON_Y) ||
												BE::Input::Gamepad::instance()->IsTriggered(BE::GP::BUTTON_B))
								{
												if (sndDigilogo->second->type == BE::Prop::AUDIO && b_sound == true) {
																static_cast<BE::Prop::Audio*>(sndDigilogo->second)->stop();
																b_sound = false;
												}

												_teamLogo->_isActive = false;
												_gamepadLogo->_isActive = false;
												_story->_isActive = true;
												b_phaseout = false;
								}
    }
	else if (_story->_isActive == true) //Story
	{
	

					if (_elapsedTime > 6.0f) {
									_storyToStart->_isActive = true;
									
									if (sndStory->second->type == BE::Prop::AUDIO && b_sound == false) {
													static_cast<BE::Prop::Audio*>(sndStory->second)->play();
													b_sound = true;
									}
					}

		if (
			BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_ANY) ||
			BE::Input::Gamepad::instance()->IsTriggered(BE::GP::BUTTON_A) ||
			BE::Input::Gamepad::instance()->IsTriggered(BE::GP::BUTTON_X) ||
			BE::Input::Gamepad::instance()->IsTriggered(BE::GP::BUTTON_Y) ||
			BE::Input::Gamepad::instance()->IsTriggered(BE::GP::BUTTON_B))
		{
			if (sndStory->second->type == BE::Prop::AUDIO && b_sound == true) {
				static_cast<BE::Prop::Audio*>(sndStory->second)->stop();
				b_sound = false;
			}

			_story->_isActive = false;
			_storyToStart->_isActive = false;
			BE::Engine::BunnyEngine::instance()->flushStages();
			BE::Engine::BunnyEngine::instance()->pushActiveStage(new Stage::sLegacyMenu);
			return;
		}
	}
}
