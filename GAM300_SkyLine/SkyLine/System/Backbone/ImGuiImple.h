#pragma once

#include "ImguiWindows.h"
struct SDL_Window;

class ImGuiImpl
{
public:
	static ImGuiImpl* instance();

	~ImGuiImpl();
	
	void newFrame(void);
	void render(void);

	void Update(float dt);

private:
	bool showSave;
	bool showDefaultWindow;
	bool showActorList;
	bool showConsole;

	SDL_Window * m_window;
	ImGuiImpl();

	//Imgui Windows
	ImguiWindows::toolBar m_toolBar; // toolbar
	ImguiWindows::defaultWindow m_defaultWindow;
	ImguiWindows::actorList m_actorList;
	ImguiWindows::saveStageFile m_saveStage;
};