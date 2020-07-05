/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      ImGuiAbst.cpp
Purpose:        The abstraction for the gui library we use (in this case Dear ImGui)
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#include <Abstractions/ImGuiAbst.hpp>
#include <Abstractions/WindowAbst.hpp>
#include <Abstractions/RenderAbst.hpp>
#include <Core/Event.hpp>

BE::ImGuiAbst::ImGuiAbst()
{
    WindowAbst::instance()->createWindow();         // Making sure that both of these are initialized
    RenderAbst::instance()->createOpenGlContext();  // before we attempt to init Dear ImGui.

    ImGui_ImplSdlGL3_Init(WindowAbst::instance()->getWindowPtr());
}

BE::ImGuiAbst::~ImGuiAbst()
{
    ImGui_ImplSdlGL3_Shutdown();
}

void
BE::ImGuiAbst::startNewFrame()
{
    ImGui_ImplSdlGL3_NewFrame(WindowAbst::instance()->getWindowPtr());
}

void BE::ImGuiAbst::handleEvent(WindowAbst::windowEvent* event_)
{
    ImGui_ImplSdlGL3_ProcessEvent(event_);
}

void
BE::ImGuiAbst::endOfFrame()
{
    ImGui::Render();
}

void BE::ImGuiAbst::checkKbOverride()
{
    ImGuiIO& io = ImGui::GetIO();
    if (io.WantCaptureKeyboard == true)
    {
        BE::Core::Event::instance()->flushKeyboardEvents();
    }
    if (io.WantCaptureMouse == true)
    {
        BE::Core::Event::instance()->flushMouseEvents();
    }
}
