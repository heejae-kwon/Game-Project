/******************************************************************************/
/*!
\file   Main.cpp
\author Matt Casanova
\title  Neon sign
\par    email: mcasanov\@digipen.edu
\par    GAM150
\par    Simple 2D Game Engine
\date   2012/11/26

This is file contains the main function to make a basic window.

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#include "WEMemory.h"
/* These are necessary includes to do any memory leak detection ***************/
/*This should always  be the first code in your file*/

/******************************************************************************/
#include <windows.h> /*WinMain*/

/*Include the engine functions*/
#include "WEApplication.h"
#include "WEStateManager.h"
#include "WEState.h"
#include "WEGameData.h"

/*My GameStates*/

#include "Ending.h"
#include "DigipenLogo.h"
#include "TeamLogo.h"
#include "MainMenu.h"
#include "WEDebugTools.h"
#include "Play.h"
#include "State.h"
#include "Story.h"
#include "Option.h"
#include "HowTo.h"
#include "LevelSelect.h"

/******************************************************************************/
/*!
The user must add states to their game After initializing the Application, and
before updating the Application.

\attention
To make switching states easier, I add the states in the order they are listed
in the DemoStates enum.
*/
/******************************************************************************/
void DemoAddStates(void)
{
  WEState state;
  int stateID;


  state.Load = SplashStateLoad;
  state.Init = SplashStateInit;
  state.Update = SplashStateUpdate;
  state.Shutdown = SplashStateShutdown;
  state.Unload = SplashStateUnload;

  stateID = WEStateManager::AddState(state);
  WEStateManager::SetStartState(stateID);


  state.Load = LogoStateLoad;
  state.Init = LogoStateInit;
  state.Update = LogoStateUpdate;
  state.Shutdown = LogoStateShutdown;
  state.Unload = LogoStateUnload;

  stateID = WEStateManager::AddState(state);

  state.Load = MainMenuStateLoad;
  state.Init = MainMenuStateInit;
  state.Update = MainMenuStateUpdate;
  state.Shutdown = ManiMenuStateShutdown;
  state.Unload = MainMenuStateUnload;

  stateID = WEStateManager::AddState(state);

	state.Load = EndingStateLoad;
	state.Init = EndingStateInit;
	state.Update = EndingStateUpdate;
	state.Unload = EndingStateShutdown;
	state.Shutdown = EndingStateUnload;

  stateID = WEStateManager::AddState(state);

  state.Load = Play_Load;
  state.Init = Play_Init;
  state.Update = Play_Update;
  state.Unload = Play_Unload;
  state.Shutdown = Play_Shutdown;

  stateID = WEStateManager::AddState(state);

  state.Load = StoryStateLoad;
  state.Init = StoryStateInit;
  state.Update = StoryStateUpdate;
  state.Unload = StoryStateUnload;
  state.Shutdown = StoryStateShutdown;

  stateID = WEStateManager::AddState(state);

  state.Load = OptionStateLoad;
  state.Init = OptionStateInit;
  state.Update = OptionStateUpdate;
  state.Unload = OptionStateUnload;
  state.Shutdown = OptionStateShutdown;

  stateID = WEStateManager::AddState(state);

  state.Load = HowToStateLoad;
  state.Init = HowToStateInit;
  state.Update = HowToStateUpdate;
  state.Unload = HowToStateUnload;
  state.Shutdown = HowToStateShutdown;

  stateID = WEStateManager::AddState(state);

  state.Load = LevelSelectStateLoad;
  state.Init = LevelSelectStateInit;
  state.Update = LevelSelectStateUpdate;
  state.Unload = LevelSelectStateUnload;
  state.Shutdown = LevelSelectStateShutdown;

  stateID = WEStateManager::AddState(state);
}

/******************************************************************************/
/*!

\brief
The main function for a windowed program.

\param instance
An identifier for the process.  This is used for various windows things.

\param prev
This is not used anymore, we can ignore it.

\param comamndLine
A string that is comes from the typed command line.  In games we usually don't
care.

\param show
A variable stating if the window is visible, we always want it visible.

\return
An Error code.  Just return 0;
*/
/******************************************************************************/
#pragma warning(suppress: 28251)
int WINAPI WinMain(HINSTANCE instance,
                   HINSTANCE /*prev*/,
                   LPSTR /*commandLine*/,
                   int /*show*/)
{


  /*Declare my InitStruct*/
  WEInitData initStruct;
  /*Create my game data initial values*/
  WEGameData gameData = { 0 };

  /*Set up my InitStruct*/
  initStruct.instance   = instance;
  initStruct.width      = 1280;
  initStruct.height     = 720;
  initStruct.title      = "NeonSign";
  initStruct.fps        = 60;
  initStruct.fullScreen = true;

  /*Information about your specific gamedata */
  initStruct.pGData       = &gameData;
  initStruct.gameDataSize = sizeof(WEGameData);

  /*Pass InitStruct to Function.  This function must be called first!!!*/
  WEApplication::Init(initStruct);
  /*Function to add all of my game states*/
  DemoAddStates();
  /*Start running the game*/
  WEApplication::Update();
  /*This function must be called after the window has closed!!!*/

  WEApplication::Shutdown();

  //int* p = new int;
  //p = 0;

  return 0;
}
