/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      sPokemon.cpp
Purpose:        To test animation with health bar
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/
#include <BunnyEngine.hpp>
#include <WIP/PropManager.hpp>
#include <WIP/Keyboard.hpp>
#include <WIP/Mouse.hpp>
#include <Utilities/JsonWriter.hh>
#include <Utilities/JsonReader.hh>
#include <Utilities/BagOfGoodies.hh>

#include <GAME_SPECIFIC_FILES/sPokemon.hpp>
#include <GAME_SPECIFIC_FILES/sConfirmMenu.hpp>
#include <GAME_SPECIFIC_FILES/logicFunctions.hh>

Stage::sPokemon::sPokemon() :
    BaseStage("sPokemon.stg"),
    _poke1(nullptr),
    _poke2(nullptr),
    btlStartPlay(true),
    btlEndPlay(false),
    _cooldownTimer(2.5f)
{
}

Stage::sPokemon::~sPokemon()
{
    //    BE::Core::Debugger::instance()->AddLog("[GAME][sPokemon::%s] Destroying Stage\n", __func__);
    if (_battleStart != nullptr && _battleStart->second->type == BE::Prop::AUDIO)
    {
        static_cast<BE::Prop::Audio*>(_battleStart->second)->stop();
    }
    if (_battleEnd != nullptr && _battleEnd->second->type == BE::Prop::AUDIO)
    {
        static_cast<BE::Prop::Audio*>(_battleEnd->second)->stop();
    }
}

void
Stage::sPokemon::start(std::string fileName_)
{
    loadProps(fileName_);
    loadStageFile(fileName_);

    _poke1 = getActor("poke1");
    _poke2 = getActor("poke2");
    _battleStart = BE::PropManager::instance()->lookupValue("sndBattle");
    _battleEnd = BE::PropManager::instance()->lookupValue("sndVictory");
    _tackle = BE::PropManager::instance()->lookupValue("sndAttTackle");

    _poke2HP = getActor("poke2HP");
    _currentPoke2HP = _poke2->getComponent<BE::Component::Gameplay>()->hp;

    if (getActor("tmpActor") == nullptr) // This is done so that it isn't created a bunch of times
    {
        BE::Engine::BunnyEngine::instance()->getActiveStage()->addActor(BE::Actor::createActor("tmpActor", true));
        _tmpActorVec.push_back(getActor("tmpActor"));
        _tmpActorVec.back()->addComponent<BE::Component::Display>();
        _tmpActorVec.back()->getComponent<BE::Component::Display>()->setTextureId("sprGerminion", 7);
        _tmpActorVec.back()->getComponent<BE::Component::Display>()->playAnim("animUpDown");
    }
    else
    {
        _tmpActorVec.push_back(getActor("tmpActor"));
    }

    _hPColors.push_back(glm::vec4(1.f, 0.f, 0.f, 0.f));
    _hPColors.push_back(glm::vec4(1.f, 0.f, 0.f, 1.f));
    _hPColors.push_back(glm::vec4(1.f, .5f, 0.f, 1.f));
}

void
Stage::sPokemon::resume()
{
}

void
Stage::sPokemon::pause()
{
}

void
Stage::sPokemon::update(float dt_)
{
    // Audio
    if (_battleStart->second->type == BE::Prop::AUDIO)
    {
        if (btlStartPlay)
        {
            static_cast<BE::Prop::Audio*>(_battleStart->second)->play();
            //            _poke1->getComponent<BE::Component::Display>()->playAnim("animHericendreIntro", false);
            _poke2->getComponent<BE::Component::Display>()->playAnim("animKaiminusIntro", false);
            btlStartPlay = false;
        }
    }
    if (_battleEnd->second->type == BE::Prop::AUDIO)
    {
        if (btlEndPlay)
        {
            if (_battleStart->second->type == BE::Prop::AUDIO)
            {
                static_cast<BE::Prop::Audio*>(_battleStart->second)->stop();
            }
            static_cast<BE::Prop::Audio*>(_battleEnd->second)->play();
        }
    }
    // -

    // Default behavior
    if (BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_KP_PLUS))
    {
        BE::Core::Debugger::instance()->AddLog("[LOG][sLevel1::update()] KeyPad + pressed\n");
        BE::WindowAbst::instance()->resizeWindow(glm::vec2(1920, 1080));
    }
    if (BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_KP_MINUS))
    {
        BE::Core::Debugger::instance()->AddLog("[LOG][sLevel1::update()] KeyPad - pressed\n");
        BE::WindowAbst::instance()->resizeWindow(glm::vec2(1280, 720));
    }
    if (BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_ESCAPE))
    {
        BE::Engine::BunnyEngine::instance()->pushActiveStage(new sConfirmMenu);
    }
    // -

    // Game Logic

    if (_poke1->getComponent<BE::Component::Display>()->animPlaying == false && BE::Input::Keyboard::instance()->IsTriggered(BE::KB::KEY_SPACE))
    {
        _poke1->getComponent<BE::Component::Display>()->playAnim("animAttTackle", false);
        static_cast<BE::Prop::Audio*>(_tackle->second)->play();

        if (_poke2->getComponent<BE::Component::Gameplay>()->hp > 0)
        {
            _currentPoke2HP -= 20;
            _poke2->getComponent<BE::Component::Display>()->playAnim("animHit", false);
        }
    }

    if (_poke2->getComponent<BE::Component::Gameplay>()->hp > _currentPoke2HP)
    {
        healthBarReduction(dt_);

        if (_poke2->getComponent<BE::Component::Gameplay>()->hp == 0)
        {
            static_cast<BE::Prop::Audio*>(_battleStart->second)->stop();
            static_cast<BE::Prop::Audio*>(_battleEnd->second)->play();
            _poke2->getComponent<BE::Component::Display>()->playAnim("animDeath", false);
            _poke2HP->getComponent<BE::Component::Display>()->textureColor = _hPColors[0];
        }
    }

    // Spawning actors with mouse click
    if (BE::Input::Mouse::instance()->IsTriggered(BE::MS::KEY_LEFT))
    {
        glm::vec4 mousePos = BE::BoG::getMouseCoord();
        {
            std::stringstream ss;

            ss << "tmpActor" << _tmpActorVec.size();
            BE::Engine::BunnyEngine::instance()->getActiveStage()->addActor(BE::Actor::createActor(ss.str(), true));
            _tmpActorVec.push_back(getActor(ss.str()));
            _tmpActorVec.back()->addComponent<BE::Component::Display>();
            _tmpActorVec.back()->getComponent<BE::Component::Display>()->setTextureId("sprGerminion", 7);
            _tmpActorVec.back()->getComponent<BE::Component::Transform>()->position = glm::vec3(mousePos[2], mousePos[3], 0.f);
        }
    }
}

void
Stage::sPokemon::healthBarReduction(float dt_)
{
    static float _cooldown = 0.f;

    _cooldown -= dt_;
    if (_cooldown <= 0.f)
    {
        _cooldown = 0.03f;

        int oldHp = _poke2->getComponent<BE::Component::Gameplay>()->hp;
        float oldScaleX = _poke2HP->getComponent<BE::Component::Transform>()->scale.x;
        int newHP = oldHp - 1;
        float percent = (newHP * 100.f) / oldHp;

        if (newHP <= 60)
        {
            _poke2HP->getComponent<BE::Component::Display>()->textureColor = _hPColors[2];
        }
        if (newHP <= 30)
        {
            _poke2HP->getComponent<BE::Component::Display>()->textureColor = _hPColors[1];
        }

        _poke2->getComponent<BE::Component::Gameplay>()->hp = newHP;
        _poke2HP->getComponent<BE::Component::Transform>()->scale.x = (oldScaleX * percent) / 100;
        _poke2HP->getComponent<BE::Component::Transform>()->position.x -= (oldScaleX - _poke2HP->getComponent<BE::Component::Transform>()->scale.x) * 4;
    }
}
