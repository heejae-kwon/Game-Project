#pragma once
#include <stack>
#include <BaseLevel.hpp>
#include <memory>
		//The engine manage all systems in the game, updating them, routing msgs,
				//and destroy the systems when the game ends
				class Engine
				{
				public:
								//Magical singletern code
								static Engine* instance(bool debugMode_ = false);
								~Engine();

								//Update all systems
								void GameLoop();

								void PushActiveLevel(Level::BaseLevel * level_, std::string overrideFileName = "");
								void PopActiveLevel();

								//You should do return after using this function
								void GotoNextLevel(Level::BaseLevel*level_);

								Level::BaseLevel* GetActiveLevel() const;

								void Quit();
								void SaveSceneState(std::string filename_);

								//Todo: System Message functions

				private:
								//Hide Constructor
								Engine(bool debugMode_);
								//Track all systems the engine uses
							//	std::vector<System*> SystemsList;
								//Main loop
								bool GameIsRunning;
								//delta for each frame
								float dt;
								//Fixed time step used for the physics integration function.
								const float pm_fixeddt;
								//Accumulation of time cannot exceed pm_accumlock.
								const float pm_accumulatorlock;
								float pm_accumulator;

								std::stack<std::unique_ptr<Level::BaseLevel>> activeLevels;

				};

				//A global pointer of the instance of the Engine
				//extern Engine* ENGINE;

