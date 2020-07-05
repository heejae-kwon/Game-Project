/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      sWinScreen.cpp
Language:      C++
Project:         GAM250
Author:         Name : HeeJae Kwon(Sound) , Wonjae Jung
Email:            sfhy33@gmail.com
Creation date:   2017.06.16
----------------------------------------------------------------------------*/
#include <GAME_SPECIFIC_FILES/sWinScreen.hpp>
#include <GAME_SPECIFIC_FILES/sLegacyMenu.hpp>
#include <WIP/PropManager.hpp>
#include <WIP/Keyboard.hpp>
#include <GAME_SPECIFIC_FILES/inputAbstraction.hh>

Stage::sWinScreen::sWinScreen()
    : BaseStage("sWinScreen.stg"), increasingParticle(0)
{
}

void
Stage::sWinScreen::start(std::string fileName_)
{
    loadProps(fileName_);
    loadStageFile(fileName_);

	_particle = getActor("particle");

	//Init Sounds
	sndBackground = BE::PropManager::instance()->lookupValue("sndWin");
}

void
Stage::sWinScreen::resume()
{
				if (sndBackground->second->type == BE::Prop::AUDIO) {
								static_cast<BE::Prop::Audio*>(sndBackground->second)->resume();
				}
}

void
Stage::sWinScreen::pause()
{
				if (sndBackground->second->type == BE::Prop::AUDIO) {
								static_cast<BE::Prop::Audio*>(sndBackground->second)->pause();
				}
}

void
Stage::sWinScreen::update(float /*dt_*/)
{
	//for(int i = 1; i < 50; i++)
	static bool playsndWin = false;

  if (sndBackground->second->type == BE::Prop::AUDIO && playsndWin == false) {
      static_cast<BE::Prop::Audio*>(sndBackground->second)->play();
      playsndWin = true;
  }

  if (increasingParticle < 200)
  {
	  _particle->getComponent<BE::Component::ParticleEmitter>()->setCapacity(++increasingParticle);
  }

  if (Input::isTriggered(Input::JUMP) || 
      Input::isTriggered(Input::POS_ACTION) || 
      Input::isTriggered(Input::NEG_ACTION)) {

      if (sndBackground->second->type == BE::Prop::AUDIO && playsndWin == true) {
          static_cast<BE::Prop::Audio*>(sndBackground->second)->stop();
          playsndWin = false;
      }

      BE::Engine::BunnyEngine::instance()->flushStages();
      BE::Engine::BunnyEngine::instance()->pushActiveStage(new sLegacyMenu);
      return;
  }
}
