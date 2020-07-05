#include "Application.hpp"
#include "Engine.hpp"
#include "Input.hpp"
#include "Gamepad.hpp"
//#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>

Application * Application::instance()
{
				static std::unique_ptr<Application> instance(new Application());
				return instance.get();
}

Application::Application(/*int width,
	int height,
	bool fullscreen,
	const std::string& name*/)
	:
	width_(1280),
	height_(720),
	//targetFrameRate_(1.0 / 60.0),
	isFullscreen_(false),
	name_("TheWindow"),
	savedTime_(0.0),
	frameTime_(0.0),
	deltaTime_(0.0),
	lastFrame_(0.0),
	currentFrame_(0.0)
{
  // Load default OpenGL library
  SDL_GL_LoadLibrary(NULL);

	//FIX THIS
	const int major = 4; //4
	const int minor = 3;//4.1
	const bool resizable = false;

				if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS) < 0) {
										std::cout << "Initialize is failed\n";
				}
				pWindow = SDL_CreateWindow(
								name_.c_str(),
								SDL_WINDOWPOS_CENTERED,
								SDL_WINDOWPOS_CENTERED,
								width_,
								height_,
								SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE|SDL_WINDOW_OPENGL
				);
				
				SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);


				glContext =	SDL_GL_CreateContext(pWindow);
	// Init GLFW
	//glfwInit();
	//// Set all the required options for GLFW
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);                 // version #
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);                 // version #.#
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//glfwWindowHint(GLFW_RESIZABLE, resizable);


	//window_ = glfwCreateWindow(width_, height_, name_.c_str(), nullptr, nullptr);
	//glfwMakeContextCurrent(window_);
	//glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);
	//glfwSetKeyCallback(window_, key_callback);
	//glfwSetMouseButtonCallback(window_, mouseButtonCallback);


	////savedTime_ = glfwGetTime();
	//monitor_ = glfwGetPrimaryMonitor();
	//videmode_ = glfwGetVideoMode(monitor_);
	//monitorWidth_ = videmode_->width;
	//monitorHeight_ = videmode_->height;

	////Engine should know about this? 
	//targetFrameRate_ = 1.0 / (double)(videmode_->refreshRate);

				// Joystick codes
				MaxJoysticks = SDL_NumJoysticks();
				 ControllerIndex = 0;

				 // save all joysticks to engine
				 for (int i = 0; i < MaxJoysticks; ++i)
				 {
					 if (!SDL_IsGameController(i))
					 {
						 continue;
					 }
					 if (ControllerIndex >= MAX_CONTROLLERS)
					 {
						 break;
					 }
					 ControllerHandles[ControllerIndex] = SDL_GameControllerOpen(i);
					 ControllerIndex++;
				 }
}



void Application::Update(float /*dt*/)
{
	Input::Keyboard::instance()->Reset();
	Input::Gamepad::instance()->Reset();
	//Todo: PollEvents
	PollEvents();
    SDL_GL_SwapWindow(pWindow);

	/*processInput(window_);*/

	// Set frame time
	//double currentFrame = glfwGetTime();
	//deltaTime_ = currentFrame - lastFrame_;
	//lastFrame_ = currentFrame;
	//dt_ = 1.0 / deltaTime_;
	//std::cout << dt_ << std::endl;


	// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	// -------------------------------------------------------------------------------
	//glfwSwapInterval(1);
	//glfwSwapBuffers(window_);
	//glfwPollEvents();

	//reword so this is at top of loop
	// Render
	// Clear the colorbuffer
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT);

}

Application::~Application()
{
/*	glfwTerminate()*/;
				SDL_GL_DeleteContext(glContext);

				SDL_DestroyWindow(pWindow);
				pWindow = nullptr;
				SDL_Quit();

				// Joystick codes
				for (int i = 0; i < MAX_CONTROLLERS; ++i)
				{
					if (ControllerHandles[i])
					{// need to close before the end
						SDL_GameControllerClose(ControllerHandles[ControllerIndex]);
						ControllerHandles[ControllerIndex] = NULL;
					}
				}
}

void Application::PollEvents()
{
				while (SDL_PollEvent(&event)) {
						ImGui_ImplSDL2_ProcessEvent(&event);

						PollWindowEvent(event);
						PollKeyboardEvent(event);
						PollGamepadEvent(event);
						//PollMouse
				}
}

void Application::PollWindowEvent(SDL_Event & currEvent)
{
				switch (currEvent.type) {
				case SDL_QUIT: {
								Engine::instance()->Quit();
				}break;
				default:
								break;
				}
}

void Application::PollKeyboardEvent(SDL_Event & currEvent)
{
				switch (currEvent.type) {
				case SDL_KEYDOWN: {

								Input::Keyboard::instance()->SetKeyPressed(static_cast<Key_Scancode>(currEvent.key.keysym.scancode),
																																								 static_cast<Key_EventType>(SDL_KEYDOWN));

				}break;
				case SDL_KEYUP: {

								Input::Keyboard::instance()->SetKeyPressed(static_cast<Key_Scancode>(currEvent.key.keysym.scancode),
																																								 static_cast<Key_EventType>(SDL_KEYUP));

				}break;

				default:
								break;
				}
}

void Application::PollGamepadEvent(SDL_Event & currEvent)
{
	switch (currEvent.type) {
				case SDL_CONTROLLERBUTTONDOWN: {

					Input::Gamepad::instance()->SetButtonPressed(static_cast<Key_GameControllerButton>(currEvent.cbutton.button),
																																								 static_cast<Key_EventType>(SDL_CONTROLLERBUTTONDOWN));

				}break;
				case SDL_CONTROLLERBUTTONUP: {

					Input::Gamepad::instance()->SetButtonPressed(static_cast<Key_GameControllerButton>(currEvent.cbutton.button),
																																								 static_cast<Key_EventType>(SDL_CONTROLLERBUTTONUP));

				}break;
				case SDL_CONTROLLERAXISMOTION: {
					if (currEvent.jaxis.which == 0)
					{
						Input::Gamepad::instance()->SetAxisDirection(static_cast<char>(currEvent.caxis.axis),
																																								 static_cast<int>(currEvent.caxis.value));
					}
				}break;
				default:
								break;
				}
	Input::Gamepad::instance()->stickUpdate();
}

void Application::SwapWindow()
{
				SDL_GL_SwapWindow(pWindow);
}

void Application::SetFullscreen(bool active)
{
				    if (active)
    {
        SDL_SetWindowFullscreen(pWindow, SDL_WINDOW_FULLSCREEN);
    }
    else
    {
        SDL_SetWindowFullscreen(pWindow, false);
    }
								isFullscreen_ = active;
}

SDL_Window * Application::getWindow(void)
{
	return pWindow;
}

SDL_GLContext Application::getContext(void)
{
	return glContext;
}

//
//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//// ---------------------------------------------------------------------------------------------------------
//void processInput(GLFWwindow *window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//}
//
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	// make sure the viewport matches the new window dimensions; note that width and 
//	// height will be significantly larger than specified on retina displays.
//	glViewport(0, 0, width, height);
//}
//
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
//{
//}
//
//void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
//{
//}

