/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:    sConfirmQuit.cpp
Purpose:       This file contain confirming quit codes.
Can be used C style with static functions or C++ with methods.
Language:     C++
Project:         GAM250
Author:         Name : Jihwan Oh
Email:            dkdkdkdudrn@gmail.com
date:			   2017.06.16
----------------------------------------------------------------------------*/
#include <GAME_SPECIFIC_FILES/sCredit.hpp>
#include <GAME_SPECIFIC_FILES/inputAbstraction.hh>
#include <WIP/PropManager.hpp>
#include <WIP/Keyboard.hpp>

Stage::sCredit::sCredit()
    : BaseStage("sCredit.stg")
{
    // Setting up the core config, by default everything is set to false
    {
        _stageLoadCoreConf.drawCore = true; // We want the draw core to keep drawing whatever was present while we display the confirm action pop up
    }
}

void
Stage::sCredit::start(std::string fileName_)
{
    loadProps(fileName_);
    loadStageFile(fileName_);
}

void
Stage::sCredit::resume()
{
}

void
Stage::sCredit::pause()
{
}

void
Stage::sCredit::update(float /*dt_*/)
{
    if (BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_s) ||
		BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_ESCAPE) ||
		Input::isTriggered(Input::NEG_ACTION))
    {
        BE::Engine::BunnyEngine::instance()->popActiveStage();
        return;
    }
}
