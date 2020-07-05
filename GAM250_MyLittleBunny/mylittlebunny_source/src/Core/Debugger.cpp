/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      Debugger.cpp
Purpose:        Debugger is the core in charge of all the ingame tools
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#include <Core/Debugger.hpp>
#include <Core/Event.hpp>
#include <WIP/Keyboard.hpp>
#include <BunnyEngine.hpp>

BE::Core::Debugger::Debugger()
    : BaseCore(), _imguiInst(ImGuiAbst::instance()),
    _show_log(false),
    _show_fps(false),
    _show_actor(false),
    _show_prop(false),
    _show_table(false),
    _show_menu_bar(false),
    _show_load_stage(false),
    _show_save_stage_filename(false),
    _show_config(false)
{
    BaseCore::_coreStringId = "Debugger";

    DImGuiHelperFunc::MenuBar::windowPointers winPtr;
    winPtr.show_log = &_show_log;
    winPtr.show_fps = &_show_fps;
    winPtr.show_actor = &_show_actor;
    winPtr.show_prop = &_show_prop;
    winPtr.show_table = &_show_table;
    winPtr.show_load_stage = &_show_load_stage;
    winPtr.show_save_stage_filename = &_show_save_stage_filename;
    winPtr.show_config = &_show_config;
    winPtr.show_physics = &_show_physics;

    _menuBar.setPointers(winPtr);
}

void
BE::Core::Debugger::startNewFrame()
{
    BaseCore::startNewFrame();  // You should ALWAYSE call the Core's base functions as we are extending the base functions
    {
        _imguiInst->startNewFrame();

        Event::winEventQueue events = Event::instance()->getEventStack();
        while (!events.empty())
        {
            _imguiInst->handleEvent(&events.front());
            events.pop();
        }
        _imguiInst->checkKbOverride();
    }
    BaseCore::updateExecTime();
}

void
BE::Core::Debugger::update(float /*dt_*/)
{
    BaseCore::update();  // You should ALWAYSE call the Core's base functions as we are extending the base functions
    {
        if (Input::Keyboard::instance()->IsPressed(KB::KEY_LCTRL) && Input::Keyboard::instance()->IsTriggered(KB::KEY_F5))
        {
            Engine::BunnyEngine::instance()->setDebugMode(true);
            _show_menu_bar = true;
        }
        else if (Input::Keyboard::instance()->IsTriggered(KB::KEY_F5))
        {
            Engine::BunnyEngine::instance()->setDebugMode(false);
            _show_menu_bar = false;
        }

        {
            if (_show_menu_bar)
            {
                _menuBar.Draw();
            }
            if (_show_log)
            {
                _log.Draw("Logger", &_show_log);
            }
            if (_show_fps)
            {
                _fps.setValue(Core::Draw::instance()->getExecTime(), Core::Event::instance()->getExecTime(), Core::Physics::instance()->getExecTime(), getExecTime(), Core::Particle::instance()->getExecTime());
                _fps.Draw("FPS", &_show_fps);
            }
            if (_show_actor)
            {
                _actors.Draw("Actor Viewer", &_show_actor);
            }
            if (_show_prop)
            {
                _props.Draw("Prop Viewer", &_show_prop);
            }
            if (_show_table)
            {
                _table.Draw("Correspondance Table", &_show_table);
            }
            if (_show_load_stage)
            {
                _stageLoader.Draw("Load stage", &_show_load_stage);
            }
            if (_show_save_stage_filename)
            {
                _saveStageFilename.Draw("Save As", &_show_save_stage_filename);
            }
            if (_show_config)
            {
                _config.Draw("Settings", &_show_config);
            }
            if (_show_physics)
            {
                _physics.Draw("Physics", &_show_physics);
            }
        }

        if (windowIsOpen() == true)
        {
            WindowAbst::instance()->setMouseState(true);
        }
        else
        {
            WindowAbst::instance()->setMouseState(false);
        }
    }
    BaseCore::updateExecTime();
}

void
BE::Core::Debugger::endOfFrame()
{
    BaseCore::endOfFrame();  // You should ALWAYSE call the Core's base functions as we are extending the base functions
    {
        _imguiInst->endOfFrame();
    }
    BaseCore::updateExecTime();
    BaseCore::flushExecTimeLog();
}

void
BE::Core::Debugger::AddLog(const char* fmt_, ...)
{
    va_list args;
    va_start(args, fmt_);
    _log.AddLog(fmt_, args);
    va_end(args);
}

void
BE::Core::Debugger::setSaveStagFileName(std::string filename_)
{
    _saveStageFilename.setFileName(filename_);
}

bool
BE::Core::Debugger::windowIsOpen()
{
    if (_show_log || _show_fps || _show_actor ||_show_prop || _show_load_stage || _show_save_stage_filename || _show_menu_bar)
    {
        return true;
    }
    return false;
}
