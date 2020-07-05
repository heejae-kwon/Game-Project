#pragma once

#include <string>

class Actor; // predeclaration
namespace ImguiWindows
{
	struct defaultWindow
	{
		void draw(const char* title, bool* p_opened = 0);
	};

	struct saveStageFile
	{
		char buf1[64] = "";

		void setFileName(std::string fileName_);
		void draw(const char* title, bool* p_opened = 0);
	};

	struct actorList
	{
		Actor*  currentSelectedActor = nullptr;
		void draw(const char* title, bool* p_opened = 0);
	};

	struct consoleWindow
	{
		//ImGuiTextFilter     Filter;
		bool						ScrollToBottom;
		void draw(const char* title, bool* p_opened = 0);
	};

	struct toolBar
	{
		struct barBoolLists
		{
			bool* show_default;
			bool* show_save;
			bool* show_actor;
			bool* show_console;
		}barBools;

		void setPointers(barBoolLists rhs);
		void draw();
	};

}
