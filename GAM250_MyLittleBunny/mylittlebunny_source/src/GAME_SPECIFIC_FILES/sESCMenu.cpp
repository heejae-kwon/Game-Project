/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:    sESCMenu.cpp
Purpose:       This file contain ESC Menu codes.

player can do these
- Restart
- Options
- Resume
etc

Can be used C style with static functions or C++ with methods.
Language:     C++
Project:         GAM250
Author:         Name : Jihwan Oh
Email:            dkdkdkdudrn@gmail.com
date:			   2017.06.16
----------------------------------------------------------------------------*/
#include <GAME_SPECIFIC_FILES/sESCMenu.hpp>
#include <GAME_SPECIFIC_FILES/inputAbstraction.hh>

#include <GAME_SPECIFIC_FILES/sConfirmQuit.hpp>
#include <GAME_SPECIFIC_FILES/sConfirmRestart.hpp>
#include <GAME_SPECIFIC_FILES/sGameStage.hpp>
#include <GAME_SPECIFIC_FILES/sConfirmMenu.hpp>
#include <GAME_SPECIFIC_FILES/sLegacyMenu.hpp>
#include <GAME_SPECIFIC_FILES/sOption.hpp>
#include <GAME_SPECIFIC_FILES/sHowtoPlay.hpp>
#include <GAME_SPECIFIC_FILES/sCredit.hpp>
#include <GAME_SPECIFIC_FILES/sTestLevel.hpp>
#include <GAME_SPECIFIC_FILES/sGameStage.hpp>
#include <GAME_SPECIFIC_FILES/sESCMenu.hpp>

#include <WIP/PropManager.hpp>

Stage::sESCMenu::sESCMenu(std::string nextLevel_)
    : BaseStage("sESCMenu.stg")
{
    // Setting up the core config, by default everything is set to false
    {
        _stageLoadCoreConf.drawCore = true; // We want the draw core to keep drawing whatever was present while we display the confirm action pop up
    }
	nextLevel = nextLevel_;
	currentLevel = nextLevel_;
}

void
Stage::sESCMenu::start(std::string fileName_)
{
    loadProps(fileName_);
    loadStageFile(fileName_);
	nextLevel = fileName_;

    buttonNum = 1;

    _starCursor = getActor("Star");
}

void
Stage::sESCMenu::resume()
{
}

void
Stage::sESCMenu::pause()
{
}

void
Stage::sESCMenu::update(float /*dt_*/)
{
    for (auto & actor : _actorVec)
    {
        if (actor->_name == "Star")
        {
            switch (buttonNum)
            {
            case 1: {
                _starCursor->getComponent<BE::Component::Transform>()->position.y = 100;
            }break;
            case 2: {
                _starCursor->getComponent<BE::Component::Transform>()->position.y = 30;
            }break;
            case 3: {
                _starCursor->getComponent<BE::Component::Transform>()->position.y = -35;
            }break;
            case 4: {
                _starCursor->getComponent<BE::Component::Transform>()->position.y = -100;
            } break;
            case 5: {
                _starCursor->getComponent<BE::Component::Transform>()->position.y = -170;
            } break;
            case 6: {
                _starCursor->getComponent<BE::Component::Transform>()->position.y = -210;
            } break;
            default:
                break;
            }
        }
    }

    if (Input::isTriggered(Input::UP) && (buttonNum > 1 && buttonNum <= 6)) --buttonNum;
    if (Input::isTriggered(Input::DOWN) && (buttonNum >= 1 && buttonNum < 6)) ++buttonNum;

    if (Input::isTriggered(Input::SUPER) || BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_RETURN))
    {
        switch (buttonNum)
        {
            // Mode
        case 1: { //Restart
			BE::Engine::BunnyEngine::instance()->pushActiveStage(new sConfirmRestart(currentLevel));
			return;
        }break;
        case 2: { // How to play
			BE::Engine::BunnyEngine::instance()->pushActiveStage(new Stage::sHowtoPlay);
			return;
        }break;
        case 3: { // Option
			BE::Engine::BunnyEngine::instance()->pushActiveStage(new Stage::sOption);
			return;
        }break;
        case 4: { // Go menu	
			BE::Engine::BunnyEngine::instance()->pushActiveStage(new Stage::sConfirmMenu);
			return;
        } break;
        case 5: { // End game
			BE::Engine::BunnyEngine::instance()->pushActiveStage(new Stage::sConfirmQuit);
			return;
        } break;
        case 6: { // Resume Game
			BE::Engine::BunnyEngine::instance()->popActiveStage();
			return;
        } break;
        default:
            break;
        }
    }

	if (Input::isTriggered(Input::START))
	{
		BE::Engine::BunnyEngine::instance()->popActiveStage();
		return;
	}
    /*if (Input::isTriggered(Input::NEG_ACTION))
    {
        BE::Engine::BunnyEngine::instance()->popActiveStage();
        return;
    }*/

}
