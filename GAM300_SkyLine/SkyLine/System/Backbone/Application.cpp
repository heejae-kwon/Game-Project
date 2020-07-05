#include "Application.hpp"
//#include <GLFW/glfw3.h>
#include "Engine.hpp"
#include <iostream>
#include <memory>
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
	width_(720),
	height_(480),
	targetFrameRate_(1.0 / 60.0),
	isFullscreen_(false),
	name_("TheWindow"),
	savedTime_(0.0),
	frameTime_(0.0),
	deltaTime_(0.0),
	lastFrame_(0.0),
	currentFrame_(0.0)
{
	//FIX THIS
	const int major = 4; //4
	const int minor = 6;//4.6
	const bool resizable = false;

			pWindow = SDL_CreateWindow(
								"ftlgame",
								SDL_WINDOWPOS_CENTERED,
								SDL_WINDOWPOS_CENTERED,
							width_,
							height_,
								SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE|SDL_WINDOW_OPENGL
				);
				
				SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
//				SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);


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
}



void Application::Update(float /*dt*/)
{
//								Input::instance()->Reset();
				//Todo: PollEvents
				PollEvents();

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
}

void Application::PollEvents()
{
				while (SDL_PollEvent(&event)) {
								PollWindowEvent(event);
								PollKeyboardEvent(event);
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

								Input::instance()->SetKeyPressed(static_cast<Key_Scancode>(currEvent.key.keysym.scancode),
																																								 static_cast<Key_EventType>(SDL_KEYDOWN));

				}break;
				case SDL_KEYUP: {

								Input::instance()->SetKeyPressed(static_cast<Key_Scancode>(currEvent.key.keysym.scancode), 
																																								 static_cast<Key_EventType>(SDL_KEYUP));

				}break;

				default:
								break;
				}
}

void Application::SwapWindow()
{
				SDL_GL_SwapWindow(pWindow);
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