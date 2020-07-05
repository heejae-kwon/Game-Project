#pragma once
#include <string>
#include "BaseCore.hpp"
//#include <GLFW/glfw3.h>
//pre-declaration
#include <SDL.h>

#define MAX_CONTROLLERS 4

struct GLFWwindow;
struct GLFWmonitor;
struct GLFWvidmode;

class Application: public BaseCore 
{
public:
			static Application* instance();
			//	GLFWwindow * getWindow() { return window_; }
			//int toggleWindowed(); // return state after the functuion call


			//double targetFrameRate_; // target framrate

			// window: W,H,Full?,name of window
			//	double update(); // call every frame, I swap buffers here, so call last
			void Update(float dt) override;
			void SwapWindow();
			void SetFullscreen(bool active);
			
			SDL_Window* getWindow(void); //window data

			SDL_GLContext getContext(void);

			~Application();//dtor

			//double dt_;
private:
			Application(/*int width,
				int height,
				bool fullscreen, //fix later
				const std::string& name*/);

			bool isFullscreen_;

			double savedTime_;
			double frameTime_;
			double deltaTime_;
			double lastFrame_;
			double currentFrame_;

			int width_;
			int height_;

			int monitorWidth_;
			int monitorHeight_;

			std::string name_;
			//GLFWwindow * window_;
			//GLFWmonitor * monitor_;
			//const GLFWvidmode * videmode_;
			void PollEvents();
			void PollWindowEvent(SDL_Event& currEvent);
			void PollKeyboardEvent(SDL_Event& currEvent);
			void PollMouseEvent(SDL_Event& currEvent);
			void PollGamepadEvent(SDL_Event& currEvent);


			SDL_Event event;					//Events frome the OS
			SDL_Window* pWindow; //window data

			SDL_GLContext glContext;

			/*Values for Joystick*/
			SDL_GameController *ControllerHandles[MAX_CONTROLLERS];
			int MaxJoysticks = SDL_NumJoysticks();
			int ControllerIndex = 0;
};

/*void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

void processInput(GLFWwindow *window)*/;