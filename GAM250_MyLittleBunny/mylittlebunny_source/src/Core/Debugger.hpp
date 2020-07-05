/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      Debugger.hpp
Purpose:        Debugger is the core in charge of all the ingame tools
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#pragma once

#include <Core/BaseCore.hpp>
#include <Abstractions/ImGuiAbst.hpp>
#include <Utilities/DearImGuiHelperFunc.hh>

namespace BE
{
namespace Core
{

    //!  The BunnyEngine's Debugger Core class. 
    /*!
     The Debugger class (as it name might suggest) is the core that is responsible for debugging and performance tracking in the BunnyEngine.
     Currently it uses Dear ImGui to render all this information to the screen.
     That sums it up pretty well actually, I'll more detail later if needed.
    */
    class Debugger : public BaseCore
    {
        // All type redefinitions go here
    protected:
        using DebuggerSmartPtr = std::unique_ptr<Debugger>;

    public:
        static Debugger*    instance() //!< Returns an instance of the class
        {
            static DebuggerSmartPtr instance(new Debugger());
            return instance.get();
        }
        ~Debugger() = default;

        // These 3 should be automatically called every loop
        void                startNewFrame() final;  //!< This should be used to setup anything that is essential before data starts getting processed (ex: clearing the screen buffer)
        void                update(float dt_ = 0.f)        final;  //!< All the data get's processed in this funtrion (There will be a loop in this function for sure)
        void                endOfFrame()    final;  //!< Once all the data processing is done we call the final functions if needed (ex: flipping the screen buffer)

        void                AddLog(const char* fmt_, ...);
        void                setSaveStagFileName(std::string filenmae_);
    protected:
        //
    private:
        Debugger(); //!< Debugger's constructor is private as it is a Singleton and should only be accessed through the instance() function
        bool    windowIsOpen(); //!< Returns true if any window is still open

    public:
        bool _show_menu_bar;
    protected:
        //
    private:
        ImGuiAbst*                      _imguiInst; /*!< A reference to a Singleton that is our ImGui Abstraction*/

        bool _show_log;
        bool _show_fps;
        bool _show_actor;
        bool _show_prop;
        bool _show_table;
        bool _show_load_stage;
        bool _show_save_stage_filename;
        bool _show_config;
        bool _show_physics;

        DImGuiHelperFunc::ExampleAppLog     _log;               /*!< An instance of the logger struct that I stole from Omar Cornut, we use it as our logger currently but it should be refactored*/
        DImGuiHelperFunc::FpsTracker        _fps;               /*!< ... */
        DImGuiHelperFunc::ActorViewer       _actors;            /*!< ... */
        DImGuiHelperFunc::PropViewer        _props;             /*!< ... */
        DImGuiHelperFunc::PropTableViewer   _table;             /*!< ... */
        DImGuiHelperFunc::MenuBar           _menuBar;           /*!< ... */
        DImGuiHelperFunc::StageLoader       _stageLoader;       /*!< ... */
        DImGuiHelperFunc::SaveStageFilename _saveStageFilename; /*!< ... */
        DImGuiHelperFunc::ConfigWindow      _config;            /*!< ... */
        DImGuiHelperFunc::PhysicsWindow     _physics;            /*!< ... */
    };
}
}
