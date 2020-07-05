#include "Engine.hpp"
#include "Timer.hpp"
#include "Application.hpp"

#include "Level_1.hpp"
#include "PhysicsCore.hpp"
#include "GraphicsCore.hpp"
#include "AudioCore.hpp"
#include "LogicCore.hpp"
#include "Input.hpp"
#include "Gamepad.hpp"
#include "ImGuiImple.h"

#include <memory>
#include <iostream>
//Magical singletern code

Engine * Engine::instance(bool debugMode_)  //!< Returns an instance of the class
{
				static std::unique_ptr<Engine> instance(new Engine(debugMode_));
				return instance.get();
}

Engine::~Engine()
{
}

void Engine::GameLoop()
{
//	Level::Level_1 *level = new Level::Level_1(std::string("Level_1"));
	PushActiveLevel(new Level::Level_1(std::string("Level_1")),std::string("Level_1"));
	while (GameIsRunning) {
			//Update the dt
			//Calculayte the amount of time took for one iteration in prvious frame.
			dt = Timer::instance()->GetDelta();
			pm_accumulator += dt;

			//To prevent spiral of death; just a user defined random number.
			if (pm_accumulator > pm_accumulatorlock) {
				pm_accumulator = pm_accumulatorlock;
			}

			ImGuiImpl::instance()->Update(dt);
			Application::instance()->Update(dt);
			GetActiveLevel()->Update(dt); // level update
	//		level->Update(dt);
			LogicCore::instance()->Update(dt);


			while (pm_accumulator >= pm_fixeddt) {
							AudioCore::instance()->Update(dt);
							PhysicsCore::instance()->Update(pm_accumulator);
							pm_accumulator -= pm_fixeddt;				
			}
			//Have to implement linear interpolation, for the smooth game feels.
			GraphicsCore::instance()->Update(pm_accumulator);

								// Keyboard keys
								if (Input::Keyboard::instance()->IsTriggered(Key_SCANCODE_ESCAPE))
								{
									Engine::instance()->Quit();
								}
								if (Input::Keyboard::instance()->IsTriggered(Key_SCANCODE_F5))
								{
									Application::instance()->SetFullscreen(true);
								}
								if (Input::Keyboard::instance()->IsTriggered(Key_SCANCODE_F6))
								{
									Application::instance()->SetFullscreen(false);
								}
								// Gamepad
								if (Input::Gamepad::instance()->IsPressed(Key_CONTROLLER_BUTTON_A))
								{
									std::cout << Input::Gamepad::instance()->leftStick.stickAngle << std::endl;
								}
								if (Input::Gamepad::instance()->IsTriggered(Key_CONTROLLER_BUTTON_B))
								{
									std::cout << "Gamepad : b" << std::endl;
								}
								if (Input::Gamepad::instance()->IsTriggered(Key_CONTROLLER_BUTTON_DPAD_DOWN	))
								{
									std::cout << "Gamepad : Dpad Down" << std::endl;
								}
								if (Input::Gamepad::instance()->IsTriggered(Key_CONTROLLER_BUTTON_LEFTSTICK))
								{
									std::cout << "Gamepad : left Stick" << std::endl;
								}
								if (Input::Gamepad::instance()->IsTriggered(Key_CONTROLLER_BUTTON_LEFTSHOULDER))
								{
									std::cout << "SHOULDER" << std::endl;
								}
								if (Input::Gamepad::instance()->IsTriggered(Key_CONTROLLER_BUTTON_BACK))
								{
									std::cout << "Gamepad : Back" << std::endl;
								}
								if (Input::Gamepad::instance()->IsTriggered(Key_CONTROLLER_BUTTON_GUIDE))
								{
									std::cout << "GUIDE" << std::endl;
								}
								if (Input::Gamepad::instance()->IsTriggered(Key_CONTROLLER_BUTTON_START))
								{
									std::cout << "START" << std::endl;
								}/*
								if (Input::Gamepad::instance()->IsTriggered(Key_CONTROLLER_BUTTON_MAX))
								{
									std::cout << "MAX" << std::endl;
								}*/
				}

}

 void Engine::PushActiveLevel(Level::BaseLevel * level_, std::string overrideFileName)
{
		if (activeLevels.size() >= 1)
		{
				// If we are in normal play mode, we pause the previous stage and load up the new one
				Level::BaseLevel* prevStage = activeLevels.top().get();
				prevStage->Pause();
		}

		//addCoreOffset(stage_->getCoreConfig());
		activeLevels.push(std::unique_ptr<Level::BaseLevel>(level_));

		/*    if (this->_debugModeIsActive)
		{
		_firstActiveStage = stage_->cpy();
		stage_->start(overrideFileName);
		saveSceneState("tempStage.stg");
		}
		else
		{
		if (_firstActiveStage == nullptr)
		{
		_firstActiveStage = stage_->cpy();
		stage_->start();
		saveSceneState("tempStage.stg");
		}
		else
		{
		stage_->start();
		}
		TimerManager::instance()->resetAll();
		}*/
}

void Engine::PopActiveLevel()
	{
			if (activeLevels.size() > 0)
			{
					// removeCoreOffset();
					activeLevels.pop();
					if (activeLevels.size() > 0)
					{
							activeLevels.top()->Resume(); // We are only calling this as a precaution in case the stage was paused
					}
			}
	}


//You should do return after use this function
void Engine::GotoNextLevel(Level::BaseLevel * level_) {

		while (activeLevels.size() != 0) {
				PopActiveLevel();
		}
		PushActiveLevel(level_);
}

Level::BaseLevel * Engine::GetActiveLevel() const
{
		return (activeLevels.size() > 0) ? (activeLevels.top().get()) : (nullptr);
}

void Engine::Quit()
{
				GameIsRunning = false;
}

 void Engine::SaveSceneState(std::string filename_)
{
		//    if (_debugModeIsActive)
		//    {
		if (GetActiveLevel() != nullptr)
		{
				GetActiveLevel()->SaveLevelFile(filename_);
		}
		else
		{
				//  Core::Debugger::instance()->AddLog("[WARNING][BaseStage::%s] Saving empty stages is not supported\n", __func__);
		}
		//    }
}


Engine::Engine(bool /*debugMode*/) : GameIsRunning(true),
dt(0), pm_fixeddt(1/60.f), pm_accumulator(0), pm_accumulatorlock(0.25f)
{
				Timer::instance();
				//ENGINE = this;
		//Add systems to the engine
				Application::instance(); // 0
				AudioCore::instance();
				LogicCore::instance();
	//			ObjectFactory::instance(); //1
				PhysicsCore::instance(); //3
				GraphicsCore::instance(); //4
				Input::Keyboard::instance();
				Input::Gamepad::instance();
				ImGuiImpl::instance();
				
        // Temp init, remove and use for loop when other systems' Initialize functions are complete
        GraphicsCore::instance()->Initialize();
        PhysicsCore::instance()->Initialize();
				//Initialize systems after being added
/*				for (auto & sys : SystemsList) {
								sys->Initialize();
				}*/

				//Initialize Timer

}