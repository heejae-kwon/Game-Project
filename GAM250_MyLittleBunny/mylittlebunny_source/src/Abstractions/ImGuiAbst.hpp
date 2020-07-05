/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      ImGuiAbst.hpp
Purpose:        The abstraction for the gui library we use (in this case Dear ImGui)
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#pragma once

#include <Abstractions/WindowAbst.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl_gl3.h>

#include <memory>

namespace BE
{

    //!  ImGuiAbst(raction) class. 
    /*!
     ImGuiAbst is a very basic abstraction of Dear ImGui, I don't think I'll switch it out for another Immediat Mode GUI library that is why it is so barebones.
     This class is used by the Debugger core.
     It has to be called every frame that we wish to render debug info to the screen
     that is why it has the startNewFrame() and endOfFrame() that you might see often throughout this engine.
    */

    class ImGuiAbst
    {
        // All type redefinitions go here
    protected:
        using ImGuiAbstSmartPtr = std::unique_ptr<ImGuiAbst>;

    public:
        static ImGuiAbst* instance() //!< Returns an instance of the class
        {
            static ImGuiAbstSmartPtr instance(new ImGuiAbst());
            return instance.get();
        }
        ~ImGuiAbst();

        void    startNewFrame();   //!< Function that will be called at the start of each frame
        void    handleEvent(WindowAbst::windowEvent* event_);
        void    endOfFrame();      //!< Function that will be called at the end of each frame
        void    checkKbOverride(); //!< Checks to see if kb override event has been received by ImGui
    protected:
        //
    private:
        ImGuiAbst();    //!< ImGuiAbst's constructor is private as it is a Singleton and should only be accessed through the instance() function

    public:
        //
    protected:
        //
    private:
        //
    };
}