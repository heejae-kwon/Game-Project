/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:    sHowtoPlay.cpp
Purpose:       This file contain show how to play codes.
Can be used C style with static functions or C++ with methods.
Language:     C++
Project:         GAM250
Author:         Name : Jihwan Oh, Wonjae Jung(GamePad)
Email:            dkdkdkdudrn@gmail.com
date:			   2017.06.16
----------------------------------------------------------------------------*/
#include <GAME_SPECIFIC_FILES/sHowtoPlay.hpp>
#include <GAME_SPECIFIC_FILES/inputAbstraction.hh>
#include <WIP/PropManager.hpp>
#include <WIP/Keyboard.hpp>

Stage::sHowtoPlay::sHowtoPlay()
    : BaseStage("sHowtoPlay.stg")
{
    // Setting up the core config, by default everything is set to false
    {
        _stageLoadCoreConf.drawCore = true; // We want the draw core to keep drawing whatever was present while we display the confirm action pop up
    }
}

void
Stage::sHowtoPlay::start(std::string fileName_)
{
	
    loadProps(fileName_);
    loadStageFile(fileName_);
	_infoSign = getActor("HowtoPlay");
	_infoSignGamePad = getActor("HowtoPlayGamePad");
}
void 
Stage::sHowtoPlay::movementControl() {

	Input::InputType inputType;

	Input::isPressed(Input::UP, &inputType);
	Input::isPressed(Input::DOWN, &inputType);
	Input::isPressed(Input::LEFT, &inputType);
	Input::isPressed(Input::RIGHT, &inputType);
	Input::isPressed(Input::JUMP, &inputType);
	Input::isPressed(Input::SUPER, &inputType);

	if (inputType == Input::InputType::KEYBOARD)
	{
		m_inputstate = KEYBOARD;
	}
	else if (inputType == Input::InputType::GAMEPAD)//
	{
		m_inputstate = GAMEPAD;

	}
}
void
Stage::sHowtoPlay::resume()
{
}

void
Stage::sHowtoPlay::pause()
{
}

void
Stage::sHowtoPlay::update(float /*dt_*/)
{

	movementControl();
	
	
	if (m_inputstate == GAMEPAD)
	{
		if (_infoSignGamePad->_isActive == false)
		{
			_infoSignGamePad->_isActive = true;
			_infoSign->_isActive = false;
		}
	}
	else if (m_inputstate == KEYBOARD)
	{
		if (_infoSign->_isActive == false)
		{

			_infoSign->_isActive = true;
			_infoSignGamePad->_isActive = false;

		}
	}

    if (Input::isTriggered(Input::NEG_ACTION)
        || Input::isTriggered(Input::POS_ACTION)
        || BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_ESCAPE))
    {
        BE::Engine::BunnyEngine::instance()->popActiveStage();
        return;
    }

}
