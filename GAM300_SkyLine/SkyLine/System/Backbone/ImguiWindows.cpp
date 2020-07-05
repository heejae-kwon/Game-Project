#include "ImguiWindows.h"
#include "ImGuiImple.h"
#include "ObjectManager.hpp"
#include "Actor.hpp"
#include "Engine.hpp"

#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>

namespace ImguiWindows
{
	void defaultWindow::draw(const char * title, bool * p_opened)
	{
		ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiSetCond_FirstUseEver);
		ImGui::Begin(title, p_opened);
		

		if (ImGui::Button("Add"))
		{
		
		}
		ImGui::SameLine();
		if (ImGui::Button("Remove"))
		{
			
		}
		ImGui::End();
	}
	void toolBar::setPointers(barBoolLists rhs)
	{
		barBools = rhs;
	}
	void toolBar::draw()
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Save"))
				{
					*barBools.show_save = !(*barBools.show_save);
				}
				if (ImGui::MenuItem("Default"))
				{
					*barBools.show_default = !(*barBools.show_default);
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit"))
			{
				if (ImGui::MenuItem("Actor"))
				{
					*barBools.show_actor = !(*barBools.show_actor);
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Debug"))
			{
				if (ImGui::MenuItem("Console"))
				{
					*barBools.show_console = !(*barBools.show_console);
				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
	}

	void actorList::draw(const char * title, bool * p_opened)
	{
		ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiSetCond_FirstUseEver);

		static unsigned selected = 0;
		std::vector<Actor*>& actorVec = ObjectManager::instance()->getActorVec();
		
		ImGui::Begin(title, p_opened);
		{
			// Adding and Removing actors
			ImGui::BeginChild("left pane", ImVec2(280, ImGui::GetWindowHeight() - 30), false);
			{
				// The list of all active actors
				ImGui::BeginChild("left pane", ImVec2(280, ImGui::GetWindowHeight() - 50), true);
				{
					for (unsigned i = 0; i < actorVec.size(); ++i)
					{
						std::string nameStr = actorVec[i]->name;
						char const* namChar = nameStr.c_str();
						if (ImGui::Selectable(namChar, selected == i) || (actorVec[i])->_isSelected)
						{
							ImGui::PushID(static_cast<int>(i));
							{
								if (!actorVec[i]->_isSelected)
								{
								}
								selected = i;
								currentSelectedActor = actorVec[i];
								/*if (currentSelectedActor->getComponent<Component::Display>())
								{
									currentSelectedActor->_isSelected = true;
								}*/
							}
							ImGui::PopID();
						}
					}
				}
				ImGui::EndChild();

				if (ImGui::Button("Add"))
				{
					ObjectManager::instance()->CreateActor("newActor", true, nullptr);
				}
				ImGui::SameLine();
				if (ImGui::Button("Remove"))
				{
					//Actor* newActor = Actor::RemoveActor("newActor", true);
				}
			}
			ImGui::EndChild();
		}
		ImGui::SameLine();

		// right section
		{
			if (currentSelectedActor != nullptr)
			{
				ImGui::BeginGroup();
				{
					char const* namChar = currentSelectedActor->name.c_str();
					ImGui::Text("Actor name: %s\n", namChar);
					ImGui::PushItemWidth(220.0f);
					{
						static char buf1[32] = "";
						if (ImGui::InputText("", buf1, 32, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CharsNoBlank))
						{
							currentSelectedActor->name = buf1;
							buf1[0] = '\0';
						}
						ImGui::PopItemWidth();
					}
					ImGui::SameLine(230.0f);
					ImGui::Checkbox("Active", &currentSelectedActor->isActive);

				}
				// Actor component's
				{
					currentSelectedActor->drawComponentData();
				}
				ImGui::EndGroup();
			}
		}

		ImGui::End();
	}

	void consoleWindow::draw(const char * /*title*/, bool * /*p_opened*/)
	{
		//ImGui::Begin(title, p_opened);
		//ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiSetCond_FirstUseEver);
		//ImGui::Begin(title, p_opened);
		/*if (ImGui::Button("Clear"))
			Clear();*/
		//ImGui::SameLine();
		//bool copy = ImGui::Button("Copy");
		//ImGui::SameLine();
		//Filter.Draw("Filter", -100.0f);
		//ImGui::Separator();
		//ImGui::BeginChild("scrolling");
		//ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 1));
		//{

		//}

		//if (ScrollToBottom)
		//	ImGui::SetScrollHere(1.0f);
		//ScrollToBottom = false;
		//ImGui::PopStyleVar();
		//ImGui::EndChild();
		//ImGui::End();
	}
	void saveStageFile::setFileName(std::string fileName_)
	{
		buf1[0] = '\0';
		for (unsigned i = 0; i < fileName_.length() && i < 63; ++i)
		{
			buf1[i] = fileName_[i];
		}
		buf1[fileName_.length()] = '\0';
	}
	void saveStageFile::draw(const char * title, bool * p_opened)
	{
		ImGui::SetNextWindowSize(ImVec2(300, 60), ImGuiSetCond_FirstUseEver);
		ImGui::SetNextWindowSizeConstraints(ImVec2(300, 60), ImVec2(300, 60));
		ImGui::Begin(title, p_opened);

		if (ImGui::InputText("", buf1, 64, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CharsNoBlank))
		{
			//Engine::instance()->saveSceneState(std::string(buf1));
			buf1[0] = '\0';
			*p_opened = false;
		}
		ImGui::SameLine();
		if (ImGui::Button("Save"))
		{
			Engine::instance()->SaveSceneState(std::string("./test.stg"));
			buf1[0] = '\0';
			*p_opened = false;
		}

		ImGui::End();
	}
}