
#include "ImGuiImple.h"
#include "Application.hpp"
#include <memory>
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>
#include <glad/glad.h>

ImGuiImpl * ImGuiImpl::instance()
{
	static std::unique_ptr<ImGuiImpl> instance(new ImGuiImpl());
	return instance.get();
}

ImGuiImpl::ImGuiImpl()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

	m_window = Application::instance()->getWindow();

	ImGui_ImplSDL2_InitForOpenGL(m_window, Application::instance()->getContext());
	ImGui_ImplOpenGL3_Init("#version 330");

	ImGui::StyleColorsDark();

	// Initialize tool Bar's booleans
	ImguiWindows::toolBar::barBoolLists toolList;
	toolList.show_save = &showSave;
	toolList.show_actor = &showActorList;
	toolList.show_default = &showDefaultWindow;
	toolList.show_console = &showConsole;
	m_toolBar.setPointers(toolList);
}

ImGuiImpl::~ImGuiImpl()
{
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiImpl::newFrame(void)
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_window);
	ImGui::NewFrame();
}

void ImGuiImpl::Update(float /*dt*/)
{
	newFrame();
	m_toolBar.draw();
	if (showDefaultWindow)
		m_defaultWindow.draw("DEFAULT WINDOW", &showDefaultWindow);
	if (showActorList)
		m_actorList.draw("Actor List", &showActorList);
	if (showSave)
		m_saveStage.draw("Save Stage", &showSave);
	render();
}

void ImGuiImpl::render(void)
{
	ImGui::Render();

	SDL_GL_MakeCurrent(m_window, Application::instance()->getContext());

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
	ImGui::GetDrawData();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
