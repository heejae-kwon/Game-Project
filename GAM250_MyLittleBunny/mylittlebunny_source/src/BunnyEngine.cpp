/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      BunnyEngine.cpp
Purpose:        The main part of our engine.
Handles creating and destroying stages.
Switching between play and editor mode.
Also handles the main game loop.
Language:       C++
Project:        GAM200
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#include <BunnyEngine.hpp>
#include <Abstractions/AudioAbst.hpp>
#include <WIP/Keyboard.hpp>
#include <WIP/Mouse.hpp>
#include <Utilities/BagOfGoodies.hh>

#include <emptyStage.hpp>

#include <TimeAPI.h>
#include <iostream>

BE::Engine::BunnyEngine::BunnyEngine(bool debugMode_) :
    _isClosing(false),
    _debugModeIsActive(debugMode_),
    _sleepIsGranular(false),
    _mainTimer(BE::TimerManager::instance()->createTimer()),
    _eventCoreInstance(Core::Event::instance()),
    _debuggerCoreInstance(Core::Debugger::instance()),
    _drawCoreInstance(Core::Draw::instance()),
    _physicsCoreInstance(Core::Physics::instance()),
    _particleCoreInstance(Core::Particle::instance()),
    _firstActiveStage(nullptr)
{
    _debugModeIsActive = false;
    setDebugMode(_debugModeIsActive);
    Core::Debugger::instance()->_show_menu_bar = _debugModeIsActive;

    _quitEvent = BE::Core::Event::instance()->getQuitStateAddr(); // We get a pointer to a boolean that will be set to true if we receive a QUIT event
    _pauseEvent = BE::Core::Event::instance()->getPauseStateAddr(); // We get a pointer to a boolean that will be set to true if we receive a QUIT event
    _unpauseEvent = BE::Core::Event::instance()->getUnpauseStateAddr(); // We get a pointer to a boolean that will be set to true if we receive a QUIT event

//    UINT desiredSchedulerMS = 1;
    // NOTE: Set the schedular's granularity to make the sleep() more precise/granular
//    _sleepIsGranular = (timeBeginPeriod(desiredSchedulerMS) == TIMERR_NOERROR);
//    _sleepIsGranular = true;
}

BE::Engine::BunnyEngine::~BunnyEngine()
{
    std::remove(formatPath("./Data/tempStage.stg").c_str()); // Removes the temporary file
}

void
BE::Engine::BunnyEngine::flushStages()
{
    while (_activeStages.size() > 0)
    {
        removeCoreOffset();
        _activeStages.pop_back();
    }
    _selectedActors.resize(0); // When we destroy all stages we want clear out this array as it's contents will have most certainly been freed
}

void
BE::Engine::BunnyEngine::pushActiveStage(Stage::BaseStage* stage_, std::string overrideFileName)
{
    if (_activeStages.size() >= 1)
    {
        // If we are in normal play mode, we pause the previous stage and load up the new one
        Stage::BaseStage* prevStage = _activeStages.back().get();
        prevStage->pause();
    }

    addCoreOffset(stage_->getCoreConfig());
    _activeStages.push_back(std::unique_ptr<Stage::BaseStage>(stage_));

    if (this->_debugModeIsActive)
    {
        _firstActiveStage = stage_->cpy();
        stage_->start(overrideFileName);
        saveSceneState("tempStage.stg");
    }
    else
    {
        if (_firstActiveStage == nullptr)
        {
            _firstActiveStage = stage_->cpy();
            stage_->start();
            saveSceneState("tempStage.stg");
        }
        else
        {
            stage_->start();
        }
        TimerManager::instance()->resetAll();
    }
}

void
BE::Engine::BunnyEngine::popActiveStage()
{
    if (_activeStages.size() > 0)
    {
        removeCoreOffset();
        _activeStages.pop_back();
        if (_activeStages.size() > 0)
        {
            _activeStages.back()->resume(); // We are only calling this as a precaution in case the stage was paused
        }
    }
}

BE::Stage::BaseStage*
BE::Engine::BunnyEngine::getActiveStage()
{
    return (_activeStages.size() > 0) ? (_activeStages.back().get()) : (nullptr);
}

void
BE::Engine::BunnyEngine::run()
{
    static bool isPaused = false;
        
    while (!(*_quitEvent) && !_isClosing)
    {

        if (*_pauseEvent == true && isPaused == false)
        {
            pushActiveStage(new BE::Stage::emptyStage());
            isPaused = true;
        }
        if (*_unpauseEvent == true && isPaused == true)
        {
            popActiveStage();
            isPaused = false;
        }

        // Start Frame
        {
            _drawCoreInstance->startNewFrame();
            _eventCoreInstance->startNewFrame();
            _debuggerCoreInstance->startNewFrame();
            _physicsCoreInstance->startNewFrame();
            _particleCoreInstance->startNewFrame();
        }

        // Update
        {
            float dt = 0.f;
            _eventCoreInstance->update();

            if (_activeStages.size() > 0)
            {
                if (_debugModeIsActive != true)
                {
                    dt = targetSecondsPerFrame;
                    _activeStages.back()->update(dt);
                }
                else
                {
                    update();
                }
            }
            _physicsCoreInstance->update(dt);
            _debuggerCoreInstance->update();
            _drawCoreInstance->update(dt);
            _particleCoreInstance->update(dt);
        }

        // End Frame
        {
            _physicsCoreInstance->endOfFrame();
            _debuggerCoreInstance->endOfFrame();
            _eventCoreInstance->endOfFrame();
            _drawCoreInstance->endOfFrame();
            _particleCoreInstance->endOfFrame();
        }
        frameLock();
        _mainTimer->update();
    }
}

void BE::Engine::BunnyEngine::update()
{
    static bool moveEnabled = false;

    // Selecting actors and adding actors to the selection
    if (BE::Input::Mouse::instance()->IsTriggered(BE::MS::KEY_LEFT))
    {
        Actor*   tmpActor = nullptr;

        for (int i = (static_cast<int>(_selectedActors.size()) - 1); i >= 0; --i)
        {
            if (_selectedActors[i]->_isSelected == false)
            {
                std::swap(_selectedActors[i], _selectedActors.back());
                _selectedActors.pop_back();
            }
        }

        glm::vec4 mousePos = BoG::getMouseCoord();
        if ((tmpActor = BE::Core::Draw::instance()->checkSpriteOverlap(mousePos)) != nullptr)
        {
            if (Input::Keyboard::instance()->IsPressed(KB::KEY_LCTRL) || Input::Keyboard::instance()->IsPressed(KB::KEY_RCTRL))
            {
                if (tmpActor->_isSelected)
                {
                    moveEnabled = true;
                }
                else
                {
                    tmpActor->_isSelected = true;
                    _selectedActors.push_back(tmpActor);
                    moveEnabled = false;
                }
            }
            else
            {
                if (tmpActor->_isSelected)
                {
                    moveEnabled = true;
                }
                else
                {
                    for (int i = (static_cast<int>(_selectedActors.size()) - 1); i >= 0; --i)
                    {
                        _selectedActors[i]->_isSelected = false;
                        _selectedActors.pop_back();
                    }
                    tmpActor->_isSelected = true;
                    _selectedActors.push_back(tmpActor);
                    moveEnabled = false;
                }
            }
        }
        else
        {
            for (int i = (static_cast<int>(_selectedActors.size()) - 1); i >= 0; --i)
            {
                _selectedActors[i]->_isSelected = false;
                _selectedActors.pop_back();
            }
        }
    }

    // save the old mouse position so to alwayse base myself off of that while the key is pressed
    static glm::vec2 oldMousePos;
    if (BE::Input::Mouse::instance()->IsTriggered(BE::MS::KEY_MIDDLE))
    {
        glm::vec4 tempPos = BoG::getMouseCoord();
        oldMousePos[0] = tempPos[0];
        oldMousePos[1] = tempPos[1];
    }
    // moving the camera
    if (BE::Input::Mouse::instance()->IsPressed(BE::MS::KEY_MIDDLE))
    {
        glm::vec4 tempPos = BoG::getMouseCoord();
        glm::vec2 newMousePos;
        newMousePos[0] = tempPos[0];
        newMousePos[1] = tempPos[1];
        Component::Transform *transform = Core::Draw::instance()->getCurrentCamera()->getComponent<Component::Transform>();
        Component::Camera *camera = Core::Draw::instance()->getCurrentCamera()->getComponent<Component::Camera>();

        if (BE::Input::Mouse::instance()->IsPressed(BE::MS::KEY_RIGHT))
        {
            transform->position = glm::vec3(0.f);
        }
        else
        {
            transform->position += glm::vec3(newMousePos - oldMousePos, 0.f) * camera->zoom;
            oldMousePos = newMousePos;
        }
    }

    if (BE::Input::Mouse::instance()->nbrOfMouseScrolls != 0)
    {
        if (Input::Keyboard::instance()->IsPressed(KB::KEY_LCTRL) || Input::Keyboard::instance()->IsPressed(KB::KEY_RCTRL))
        {
            for (auto & actor : _selectedActors)
            {
                Component::Transform *transform = actor->getComponent<Component::Transform>();

                transform->scale.x -= BE::Input::Mouse::instance()->nbrOfMouseScrolls / 10.f;
                transform->scale.y -= BE::Input::Mouse::instance()->nbrOfMouseScrolls / 10.f;
            }
        }
        else if (Input::Keyboard::instance()->IsPressed(KB::KEY_LSHIFT) || Input::Keyboard::instance()->IsPressed(KB::KEY_RSHIFT))
        {
            for (auto & actor : _selectedActors)
            {
                Component::Transform *transform = actor->getComponent<Component::Transform>();

                transform->rotation -= BE::Input::Mouse::instance()->nbrOfMouseScrolls;
            }
        }
        else
        {
            Component::Camera *camera = Core::Draw::instance()->getCurrentCamera()->getComponent<Component::Camera>();

            camera->zoom -= static_cast<float>(BE::Input::Mouse::instance()->nbrOfMouseScrolls);
            if (camera->zoom <= 0)
            {
                camera->zoom += 1;
            }
        }
    }

    if (_selectedActors.size() > 0 && moveEnabled && BE::Input::Mouse::instance()->IsPressed(BE::MS::KEY_LEFT))
    {
        static Actor* spriteOverlapResult;
        glm::vec4 mouseCoord = BoG::getMouseCoord();

        if (BE::Input::Mouse::instance()->IsTriggered(BE::MS::KEY_LEFT))
        {
            spriteOverlapResult = BE::Core::Draw::instance()->checkSpriteOverlap(mouseCoord);
        }
        glm::vec2 posOffset;


        glm::vec2 screenMousePos(mouseCoord[0], mouseCoord[1]);
        glm::vec2 cameraMousePos(mouseCoord[2], mouseCoord[3]);

        glm::vec2 actorPos = spriteOverlapResult->getComponent<BE::Component::Transform>()->position;
        if (spriteOverlapResult->getComponent<Component::Display>()->drawType == Component::Display::SPRITE)
        {
            posOffset = actorPos - cameraMousePos;
        }
        else
        {
            posOffset = actorPos - screenMousePos;

        }

        for (auto & actor : _selectedActors)
        {
            actor->getComponent<BE::Component::Transform>()->position -= glm::vec3(posOffset, 0);
        }
    }
}

void BE::Engine::BunnyEngine::quit()
{
    _isClosing = true;
}

void
BE::Engine::BunnyEngine::setDebugMode(bool isActive_)
{
    if (_debugModeIsActive != isActive_)
    {
        _debugModeIsActive = isActive_;
        if (isActive_)
        {
            TimerManager::instance()->resetAll();
            flushStages();

            if (_firstActiveStage != nullptr)
            {
                pushActiveStage(_firstActiveStage, "tempStage.stg");
            }
        }
        else
        {
            saveSceneState("tempStage.stg");
            TimerManager::instance()->startAll();
            Core::Draw::instance()->resetSelected();
        }
    }
}

void BE::Engine::BunnyEngine::saveSceneState(std::string filename_)
{
    //    if (_debugModeIsActive)
    //    {
    if (getActiveStage() != nullptr)
    {
        getActiveStage()->saveStageFile("./Data/" + filename_);
    }
    else
    {
        Core::Debugger::instance()->AddLog("[WARNING][BaseStage::%s] Saving empty stages is not supported\n", __func__);
    }
    //    }
}

void
BE::Engine::BunnyEngine::addCoreOffset(Stage::BaseStage::keepPrevActorsOnLoad coreConfig_)
{
    Core::Draw::instance()->pushNewOffset(coreConfig_.drawCore);
    Core::Physics::instance()->pushNewOffset(coreConfig_.physicsCore);
    Core::Particle::instance()->pushNewOffset(coreConfig_.particleCore);
}

void
BE::Engine::BunnyEngine::removeCoreOffset()
{
    BE::Core::Draw::instance()->popPreviousOffset();
    BE::Core::Physics::instance()->popPreviousOffset();
    Core::Particle::instance()->popPreviousOffset();
}

void BE::Engine::BunnyEngine::frameLock()
{
    float secondsElapsedForFrame = _mainTimer->getSecSinceUpdate();
    if (secondsElapsedForFrame < targetSecondsPerFrame)
    {
        if (_sleepIsGranular)
        {
//            float currentElapsed = _mainTimer->getSecSinceUpdate();
            DWORD sleepMs = (DWORD)(1000.0f * (targetSecondsPerFrame - secondsElapsedForFrame));
            if (sleepMs > 0)
            {
                SDL_Delay(sleepMs);
//                Sleep(sleepMs);
            }
        }

        secondsElapsedForFrame = _mainTimer->getSecSinceUpdate();
        if (secondsElapsedForFrame < targetSecondsPerFrame)
        {
            // TODO: Missed target frame rate
        }

        while (secondsElapsedForFrame < targetSecondsPerFrame)
        {
            secondsElapsedForFrame = _mainTimer->getSecSinceUpdate();
//            char fpsBuffer[256];
//            sprintf_s(fpsBuffer, "%fs/f\n", secondsElapsedForFrame);
//            OutputDebugStringA(fpsBuffer);
        }
    }
    else
    {
        // TODO: Missed target frame rate
    }

}
