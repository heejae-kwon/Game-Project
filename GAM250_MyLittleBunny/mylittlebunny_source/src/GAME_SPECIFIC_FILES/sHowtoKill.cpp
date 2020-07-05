/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:    sHowtoKill.cpp
Purpose:       This file contain confirming restart codes.
Can be used C style with static functions or C++ with methods.
Language:     C++
Project:         GAM250
Author:         Name : Jihwan Oh
Email:            dkdkdkdudrn@gmail.com
date:			   2017.06.16
----------------------------------------------------------------------------*/
#include <GAME_SPECIFIC_FILES/sHowtoKill.hpp>
#include <GAME_SPECIFIC_FILES/inputAbstraction.hh>
#include <WIP/PropManager.hpp>
#include <WIP/Keyboard.hpp>

Stage::sHowtoKill::sHowtoKill()
    : BaseStage("sHowtoKill.stg")
{
    // Setting up the core config, by default everything is set to false
    {
        _stageLoadCoreConf.drawCore = true; // We want the draw core to keep drawing whatever was present while we display the confirm action pop up
    }
}

void
Stage::sHowtoKill::start(std::string fileName_)
{
    loadProps(fileName_);
    loadStageFile(fileName_);
}

void
Stage::sHowtoKill::resume()
{
}

void
Stage::sHowtoKill::pause()
{
}

void
Stage::sHowtoKill::update(float /*dt_*/)
{
    if (Input::isTriggered(Input::NEG_ACTION)
        || Input::isTriggered(Input::POS_ACTION)
        || BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_ESCAPE))
    {
        BE::Engine::BunnyEngine::instance()->popActiveStage();
        return;
    }
}
