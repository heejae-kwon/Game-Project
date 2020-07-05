/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      DearImguiHelperFunc.hh
Purpose:        I'm not proud of this one, it got out of hand. These are all the functions for all tools in the game engine
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#pragma once

#include <Core/Draw.hpp>
#include <BaseStage.hpp>
#include <Actor.hpp>
#include <Props\Props.hh>

#include <imgui\imgui.h>

#include <map>

namespace BE
{
namespace DImGuiHelperFunc
{

    /** struct ExampleAppLog
    *  This is not my code so I'm leaving it as is for now even though it doesn't follow my "guidelines"
    *  This is an example given by Omar Cornut (the maker of Dear ImGui)
    *  I did change it a tiny bit jut to make it take a va_list rather than a ...
    */
    struct ExampleAppLog
    {
        ImGuiTextBuffer     Buf;
        ImGuiTextFilter     Filter;
        ImVector<int>       LineOffsets;        // Index to lines offset
        bool                ScrollToBottom;

        void    Clear() { Buf.clear(); LineOffsets.clear(); }

        void    AddLog(const char* fmt, va_list args) IM_PRINTFARGS(2)
        {
            int old_size = Buf.size();
            Buf.appendv(fmt, args);
            for (int new_size = Buf.size(); old_size < new_size; old_size++)
                if (Buf[old_size] == '\n')
                    LineOffsets.push_back(old_size);
            ScrollToBottom = true;
        }

        void    Draw(const char* title, bool* p_opened = NULL);
    };

    struct FpsTracker
    {
        uint32_t drawCoreExecTime;
        uint32_t eventCoreExecTime;
        uint32_t physicsCoreExecTime;
        uint32_t debugCoreExecTime;
        uint32_t particleCoreExecTime;

        void setValue(uint32_t drawTime_, uint32_t eventTime_, uint32_t physicsTime_, uint32_t debugTime_, uint32_t particleTime_);

        void Draw(const char* title, bool* p_opened = NULL);
    };

    struct ActorViewer
    {
        BE::Actor*  currentSelectedActor = nullptr;
        int    compoSelected = 0;

        void Draw(const char* title, bool* p_opened = NULL);
    };

    struct PropViewer
    {
        // Prop Display
        BE::Prop::BaseProp* currentSelectedProp = nullptr;
        std::string*        currentSelectedFile = nullptr;
        std::vector<std::string> availableProps;
        std::vector<std::string> availableImage;
        std::vector<std::string> availableSound;

        // Prop Create
        bool    createMode = false;
        int     ddType = 0;         // DropDown Type
        // Image Create
        std::string*        currentSelectedImage = nullptr;
        // Audio Create
        std::string*        currentSelectedAudio = nullptr;
        // Animation Create
        std::string*        currentSelectedAnimation = nullptr;

        void searchForProps();
        void Draw(const char* title, bool* p_opened = NULL);
    };

    struct PropTableViewer
    {
        void Draw(const char* title, bool* p_opened = NULL);
    };

    struct MenuBar
    {
        struct windowPointers
        {
            bool* show_log;
            bool* show_fps;
            bool* show_actor;
            bool* show_prop;
            bool* show_table;
            bool* show_load_stage;
            bool* show_save_stage_filename;
            bool* show_config;
            bool* show_physics;

        } winPtr;

        void setPointers(windowPointers windowValues_);

        void Draw();
    };

    struct StageLoader
    {
        Stage::BaseStage* currentSelectedStage = nullptr;

        void Draw(const char* title, bool* p_opened = NULL);
    };

    struct SaveStageFilename
    {
        char buf1[64] = "";

        void setFileName(std::string fileName_);
        void Draw(const char* title, bool* p_opened = NULL);
    };
    struct ConfigWindow
    {
        glm::ivec2 _viewport;
        bool fullscreen;
        int ddRatio;
        int ddResolution;
        std::map<std::string, glm::vec2> resolutions;
        std::vector<std::vector<const char*>> resVec;

        ConfigWindow();
        void Draw(const char* title, bool* p_opened = NULL);
    };


    struct PhysicsWindow
    {
        void Draw(const char* title, bool* p_opened = NULL);
    };
}
}

