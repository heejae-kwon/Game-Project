/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      sLoseScreen.cpp
Language:      C++
Project:         GAM250
Author:         Name : HeeJae Kwon(Sound), Wonjae Jung
Email:            sfhy33@gmail.com
Creation date:   2017.06.16
----------------------------------------------------------------------------*/
#include <GAME_SPECIFIC_FILES/sLoseScreen.hpp>
#include <GAME_SPECIFIC_FILES/sLegacyMenu.hpp>
#include <WIP/PropManager.hpp>
#include <WIP/Keyboard.hpp>
#include <GAME_SPECIFIC_FILES/inputAbstraction.hh>

Stage::sLoseScreen::sLoseScreen()
	: BaseStage("sLoseScreen.stg"), increasingParticle()
{
}

void
Stage::sLoseScreen::start(std::string fileName_)
{
    loadProps(fileName_);
    loadStageFile(fileName_);
	_particle = getActor("particle");
    _particle->getComponent<BE::Component::ParticleEmitter>()->setCapacity(200);

	BE::Core::Draw::instance()->setClearBufferColor(glm::vec3(0, 0, 0));

  //Init Sounds
	sndBackground = BE::PropManager::instance()->lookupValue("sndLose");
}

void
Stage::sLoseScreen::resume()
{
  if (sndBackground->second->type == BE::Prop::AUDIO) {
      static_cast<BE::Prop::Audio*>(sndBackground->second)->resume();
  }
}

void
Stage::sLoseScreen::pause()
{
  if (sndBackground->second->type == BE::Prop::AUDIO) {
      static_cast<BE::Prop::Audio*>(sndBackground->second)->pause();
  }
}

void
Stage::sLoseScreen::update(float /*dt_*/)
{
	static bool playsndLose = false;

	if (increasingParticle < 200)
	{
		_particle->getComponent<BE::Component::ParticleEmitter>()->setCapacity(++increasingParticle);
		_particle->getComponent<BE::Component::ParticleEmitter>()->fade=true;
	}
  //Play the lose sound
  if (sndBackground->second->type == BE::Prop::AUDIO && playsndLose == false) {
      static_cast<BE::Prop::Audio*>(sndBackground->second)->play();
      playsndLose = true;
  }
	
  if (Input::isTriggered(Input::JUMP) || Input::isTriggered(Input::POS_ACTION) || Input::isTriggered(Input::NEG_ACTION))
  {
    //Stop the lose sound
      if (sndBackground->second->type == BE::Prop::AUDIO && playsndLose == true) {
          static_cast<BE::Prop::Audio*>(sndBackground->second)->stop();
          playsndLose = false;
      }

      BE::Engine::BunnyEngine::instance()->flushStages();
      BE::Engine::BunnyEngine::instance()->pushActiveStage(new sLegacyMenu);
      return;
  }
}
