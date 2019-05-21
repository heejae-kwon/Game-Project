/******************************************************************************/
/*!
\file   MainMenu.cpp
\title  Neon sign
\author Junhyung Kim
\par    GAM150
\brief  This is the interface file for the main menu state.

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#include "MainMenu.h"

#include "WEInput.h"
#include "WEApplication.h"
#include "WEDebugTools.h"
#include "WEIntersection.h"
#include "WEMath.h"
#include "WEVec2.h"
#include "WEMtx44.h"
#include "WEStateManager.h"
#include "WEGraphics.h"
#include "State.h"
#include <cstdio>
#include "FmodData.h"

/*Make a struct for my shared state data*/
namespace
{
  struct Button
  {
    WEVec2 pos;
    WEVec2 scale;
    int texture;
  };

  struct InitData
  {
    int splashTexture;
    int splashTexture1;
    int splashTexture2;
    int splashTexture3;
    int splashTexture4;
    int splashTexture5;
    int startTexture;
    int HowToTexture;
    int optionTexture;
    int exitTexture;
    
    Button *pButtons;
    float timerCount;

    float forTexture;
  };

  /*The max time to be in this state*/
  const float SPLASH_MAX_TIME = 1.0f;
  const int   ARRAY_SIZE = 20;
  const int BUTTON_SIZE = 4;
  /*Create a static variable for data so it can't be used in other files.*/

  InitData Menu_data;
  FmodData Fmod;
}



/******************************************************************************/
/*!
The load state will only be called once, when the state is first entered.
You should load resources that won't need to be changed if the state is
restarted.

*/
/******************************************************************************/
void MainMenuStateLoad(void)
{

  /*Load the only texture we need for this state*/

  Menu_data.splashTexture = WEGraphics::LoadTexture("Textures\\MainMenuWhite.tga");
  Menu_data.splashTexture1 = WEGraphics::LoadTexture("Textures\\MainMenu.tga");
  Menu_data.splashTexture2 = WEGraphics::LoadTexture("Textures\\MainMenuBlue.tga");
  Menu_data.splashTexture3 = WEGraphics::LoadTexture("Textures\\MainMenuGreen.tga");
  Menu_data.splashTexture4 = WEGraphics::LoadTexture("Textures\\MainMenuOrange.tga");
  Menu_data.splashTexture5 = WEGraphics::LoadTexture("Textures\\MainMenuPink.tga");

  Menu_data.startTexture = WEGraphics::LoadTexture("Textures\\StartButton.tga");
  Menu_data.HowToTexture = WEGraphics::LoadTexture("Textures\\HowToButton.tga");
  Menu_data.optionTexture = WEGraphics::LoadTexture("Textures\\OptionButton.tga");
  Menu_data.exitTexture = WEGraphics::LoadTexture("Textures\\ExitButton.tga");
  WEGraphics::SetTextureColor(255, 255, 255, 255);
  /*All drawing in this state is in screen space*/
  WEGraphics::SetToOrtho();
}
/******************************************************************************/
/*!
The Init function will be called once when the state is entered, then again
every time the state is restarted.  You don't want to load textures here.  Use
this is reset things to initial starting values for the state.  Here I am also
using this state to test my vectors and matricies.

*/
/******************************************************************************/
void MainMenuStateInit(void)
{
  WEDEBUG_CREATE_CONSOLE();
  /*Reset the timer for this state*/

  Menu_data.timerCount = 0.f;
  
  Menu_data.pButtons = new Button[BUTTON_SIZE];

  Menu_data.forTexture = 0;


  //Setting Buttons
  Menu_data.pButtons[0].pos = { 399, 350 };
  Menu_data.pButtons[0].scale = { 150, 50 };
  Menu_data.pButtons[0].texture = Menu_data.startTexture;

  Menu_data.pButtons[1].pos = { 399, 270 };
  Menu_data.pButtons[1].scale = { 256, 32 };
  Menu_data.pButtons[1].texture = Menu_data.HowToTexture;

  Menu_data.pButtons[2].pos = { 399, 190 };
  Menu_data.pButtons[2].scale = { 150, 58 };
  Menu_data.pButtons[2].texture = Menu_data.optionTexture;

  Menu_data.pButtons[3].pos = { 399, 110 };
  Menu_data.pButtons[3].scale = { 125, 48 };
  Menu_data.pButtons[3].texture = Menu_data.exitTexture;

  MusicInit(Fmod);
  Fmod.result = Fmod.system->createSound(Common_MediaPath("BGM.ogg"), FMOD_LOOP_NORMAL | FMOD_2D, 0, &Fmod.sound);

  Fmod.result = Fmod.sound->getNumSubSounds(&Fmod.numsubsounds);

  if (Fmod.numsubsounds)
  {
    Fmod.sound->getSubSound(0, &Fmod.sound_to_play);
  }
  else
  {
    Fmod.sound_to_play = Fmod.sound;
  }

  /*
  Play the sound.
  */
  Fmod.result = Fmod.system->playSound(Fmod.sound_to_play, 0, false, &Fmod.channel);
}
/******************************************************************************/
/*!
The update function will be called once per frame.  This is where all the
action, behavoir, drawing and state changes should happen.
*/
/******************************************************************************/
void MainMenuStateUpdate(float dt)
{
  float windowWidth = static_cast<float>(WEApplication::GetWidth());
  float windowHeight = static_cast<float>(WEApplication::GetHeight());

  Menu_data.forTexture += dt;

  WEGraphics::StartDraw();
  WEMtx44 transform;
  

  //Texture Change
  if (Menu_data.forTexture < 1)
  {
    WEGraphics::SetTexture(Menu_data.splashTexture);
    WEMtx44::MakeTransform(transform,
      1440,
      720,
      0.0f,
      windowWidth / 2,
      windowHeight / 2,
      0.0);
    WEGraphics::Draw(transform);
  }
  else if (Menu_data.forTexture < 2)
  {
    WEGraphics::SetTexture(Menu_data.splashTexture1);
    WEMtx44::MakeTransform(transform,
      1440,
      720,
      0.0f,
      windowWidth / 2,
      windowHeight / 2,
      0.0);
    WEGraphics::Draw(transform);
  }
  else if (Menu_data.forTexture < 3)
  {
    WEGraphics::SetTexture(Menu_data.splashTexture2);
    WEMtx44::MakeTransform(transform,
      1440,
      720,
      0.0f,
      windowWidth / 2,
      windowHeight / 2,
      0.0);
    WEGraphics::Draw(transform);
  }
  else if (Menu_data.forTexture < 4)
  {
    WEGraphics::SetTexture(Menu_data.splashTexture3);
    WEMtx44::MakeTransform(transform,
      1440,
      720,
      0.0f,
      windowWidth / 2,
      windowHeight / 2,
      0.0);
    WEGraphics::Draw(transform);
  }
  else if (Menu_data.forTexture < 5)
  {
    WEGraphics::SetTexture(Menu_data.splashTexture4);
    WEMtx44::MakeTransform(transform,
      1440,
      720,
      0.0f,
      windowWidth / 2,
      windowHeight / 2,
      0.0);
    WEGraphics::Draw(transform);
  }
  else if (Menu_data.forTexture < 6)
  {
    WEGraphics::SetTexture(Menu_data.splashTexture5);
    WEMtx44::MakeTransform(transform,
      1440,
      720,
      0.0f,
      windowWidth / 2,
      windowHeight / 2,
      0.0);
    WEGraphics::Draw(transform);
  }
  else
  {
    Menu_data.forTexture = 0;
  }

  //Button & click Interaction
  if (WEInput::IsTriggered(WE_MOUSE_LEFT))
  {
    WEVec2 click;
    WEInput::GetMouse(click);

    for (int i = 0; i < BUTTON_SIZE; ++i)
    {
      if(WEIntersection::PointRect(click, Menu_data.pButtons[i].pos, Menu_data.pButtons[i].scale.x, Menu_data.pButtons[i].scale.y))
      {
        switch (i)
        {
        case 0: 
          Fmod.result = Fmod.sound->release();
          WEStateManager::SetNextState(DS_STATE_LEVELSELECT);
          break;
        case 1: WEStateManager::SetNextState(DS_STATE_HOWTO);
          break;
        case 2: WEStateManager::SetNextState(DS_STATE_OPTION);
          break;
        case 3: WEStateManager::Quit();
          break;
        }
      }
    }
    
    

  }

  //Get mouse
  WEVec2 click;
  WEInput::GetMouse(click);

  /*Set position scale and rotation of what I want to draw*/
  for (int i = 0; i < BUTTON_SIZE; ++i)
  {
	  if (!WEIntersection::PointRect(click, Menu_data.pButtons[i].pos,
		  Menu_data.pButtons[i].scale.x, Menu_data.pButtons[i].scale.y))
	  {
		  WEGraphics::SetTexture(Menu_data.pButtons[i].texture);
		  WEMtx44::MakeTransform(transform,
			  Menu_data.pButtons[i].scale.x,
			  Menu_data.pButtons[i].scale.y,
			  0.0f,
			  Menu_data.pButtons[i].pos.x,
			  Menu_data.pButtons[i].pos.y,
			  1);
		  WEGraphics::Draw(transform);
	  }

	  else
	  {
		  WEGraphics::SetTexture(Menu_data.pButtons[i].texture);
		  WEMtx44::MakeTransform(transform,
			  Menu_data.pButtons[i].scale.x * 1.2f,
			  Menu_data.pButtons[i].scale.y * 1.2f,
			  0.0f,
			  Menu_data.pButtons[i].pos.x,
			  Menu_data.pButtons[i].pos.y,
			  1);
		  WEGraphics::Draw(transform);
	  }
  }

  /*This must be called to after all drawing is completed*/
  WEGraphics::EndDraw();
}
/******************************************************************************/
/*!
This is the shutdown state.  Use this state to clean up any resources from
the init state.  Since this state is simple, there is nothing to clean up
here.

*/
/******************************************************************************/
void ManiMenuStateShutdown(void)
{
  Fmod.result = Fmod.system->close();
  Fmod.result = Fmod.system->release();
}
/******************************************************************************/
/*!
This is the unload state.  Use this state to clean up any resources from the
load state.  Here I need to destroy my console and unload my texture.

*/
/******************************************************************************/
void MainMenuStateUnload(void)
{

  /*We must unload the texture when we are done with the state*/

  WEGraphics::UnloadTexture(Menu_data.splashTexture);
  WEGraphics::UnloadTexture(Menu_data.splashTexture1);
  WEGraphics::UnloadTexture(Menu_data.splashTexture2);
  WEGraphics::UnloadTexture(Menu_data.splashTexture3);
  WEGraphics::UnloadTexture(Menu_data.splashTexture4);
  WEGraphics::UnloadTexture(Menu_data.splashTexture5);

  WEGraphics::UnloadTexture(Menu_data.startTexture);
  WEGraphics::UnloadTexture(Menu_data.HowToTexture);
  WEGraphics::UnloadTexture(Menu_data.optionTexture);
  WEGraphics::UnloadTexture(Menu_data.exitTexture);
}
