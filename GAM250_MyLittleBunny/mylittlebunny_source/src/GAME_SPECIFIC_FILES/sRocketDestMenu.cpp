/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      sRocketDestMenu.cpp
Purpose:        A stage that is used when selecting which planet to fly to
Language:       C++
Project:        GAM200
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#include <BunnyEngine.hpp>

#include <GAME_SPECIFIC_FILES/sRocketDestMenu.hpp>
#include <Abstractions/RenderAbst.hpp>
#include <GAME_SPECIFIC_FILES/inputAbstraction.hh>


Stage::sRocketDestMenu::sRocketDestMenu(sLegacyMenu * stage_)
    : BaseStage("sRocketDestinationSelect.stg"), _previousStage(stage_), _selectedStation(0), _mustExit(false)
{
    // Setting up the core config, by default everything is set to false
    {
        _stageLoadCoreConf.drawCore = true; // We want the draw core to keep drawing the game
        _stageLoadCoreConf.physicsCore = true; // We want the enemies to keep moving
    }
}

void Stage::sRocketDestMenu::start(std::string fileName_)
{
    loadProps(fileName_);
    loadStageFile(fileName_);

				_previousStage->resume();

    if (_previousStage != nullptr)
    {
        m_player = &_previousStage->m_player;

        for (size_t i = 0; i < _previousStage->_stations.size(); ++i)
        {
            if (m_player->m_dirPlanet == _previousStage->_clusters[i][0])
            {
                currentPlanetIndex = static_cast<int>(i);
            }
        }
        if (currentPlanetIndex == _selectedStation)
        {
            _selectedStation++;
        }
    }
}

void Stage::sRocketDestMenu::resume()
{
}

void Stage::sRocketDestMenu::pause()
{
}

void Stage::sRocketDestMenu::update(float dt_)
{
    if (_previousStage != nullptr)
    {

        onInput(dt_); // Everything that is triggered by an input is in here
        if (_mustExit)
        {
            return;
        }

        for (size_t i = 0; i < _previousStage->_stations.size(); ++i)
        {
            BE::Component::Transform *transform = _previousStage->_stations[i]->getComponent<BE::Component::Transform>();
            if (_previousStage->m_player.m_dirPlanet != _previousStage->_clusters[i][0])
            {
                if (i == _selectedStation)
                {
                    static size_t oldSelected = _selectedStation;
                    static float radius1 = 0;
                    static float radius2 = 100;

                    if (oldSelected != _selectedStation)
                    {
                        oldSelected = _selectedStation;
                        radius1 = 0.f;
                        radius2 = 100.f;
                    }

                    radius1 += dt_ * 500;
                    radius2 += dt_ * 500;

                    BE::Core::Debugger::instance()->AddLog("RADIUS %.2f RADIUS %.2f DT %.2f\n", radius1, radius2, dt_);

                    if (radius1 >= 500.f)
                    {
                        radius1 = 0.f;
                    }
                    if (radius2 >= 500.f)
                    {
                        radius2 = 0.f;
                    }

                    for (int j = 0; j < 4; ++j)
                    {
                        int sizeoffset = 5 * j;
                        BE::RenderAbst::instance()->drawCircle(transform->position, glm::vec2(radius1 + sizeoffset, radius1 + sizeoffset), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
                        BE::RenderAbst::instance()->drawCircle(transform->position, glm::vec2(radius2 + sizeoffset, radius2 + sizeoffset), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
                    }
                }
                else
                {
                    BE::RenderAbst::instance()->drawCircle(transform->position, glm::vec2(250.f, 250.f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
                }
            }

        }
    }
}

void Stage::sRocketDestMenu::onInput(float dt_)
{

    if (Input::isTriggered(Input::RIGHT))
    {
        ++_selectedStation;
        if (static_cast<size_t>(_selectedStation) >= _previousStage->_stations.size())
        {
            _selectedStation = 0;
        }
        if (_selectedStation == currentPlanetIndex)
        {
            _selectedStation++;
        }
        if (static_cast<size_t>(_selectedStation) >= _previousStage->_stations.size())
        {
            _selectedStation = 0;
        }
    }
    else if (Input::isTriggered(Input::LEFT))
    {
        int intSelectedStation = static_cast<int>(_selectedStation);

        --intSelectedStation;
        --_selectedStation;
        if (intSelectedStation < 0)
        {
            _selectedStation = static_cast<int>(_previousStage->_stations.size()) - 1;
        }
        if (_selectedStation == currentPlanetIndex)
        {
            intSelectedStation = static_cast<int>(_selectedStation);

            --intSelectedStation;
            --_selectedStation;
        }
        if (intSelectedStation < 0)
        {
            _selectedStation = static_cast<int>(_previousStage->_stations.size()) - 1;
        }
    }

    if (Input::isTriggered(Input::POS_ACTION))
    {
        m_player->flytoOtherPlanet(_previousStage->_clusters[_selectedStation][0], dt_);
        BE::Engine::BunnyEngine::instance()->popActiveStage();
        _mustExit = true;
        return;
    }

    if (Input::isTriggered(Input::NEG_ACTION))
    {
        BE::Engine::BunnyEngine::instance()->popActiveStage();
        _mustExit = true;
        return;
    }

}
