/******************************************************************************/
/*!
\file   Option.cpp
\title  Neon sign
\author HeeJae Kwon
\par    GAM150
\brief  The file that includes Option state's functions

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#include "Option.h"

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
    int fullscreenTexture;
    int windowTexture;
    int backTexture;

    Button *pButtons;
    float timerCount;
  };

  /*The max time to be in this state*/
  const float SPLASH_MAX_TIME = 1.0f;
  const int   ARRAY_SIZE = 20;
  const int BUTTON_SIZE = 2;
  /*Create a static variable for data so it can't be used in other files.*/

  InitData Option_data;
}



/******************************************************************************/
/*!
\brief
	Load function that load textures.
*/
/******************************************************************************/
void OptionStateLoad(void)
{

  /*Load the only texture we need for this state*/

  Option_data.splashTexture = WEGraphics::LoadTexture("Textures\\MainMenu.tga");
  Option_data.fullscreenTexture = WEGraphics::LoadTexture("Textures\\FullScreenButton.tga");
  Option_data.windowTexture = WEGraphics::LoadTexture("Textures\\WindowModeButton.tga");
  Option_data.backTexture = WEGraphics::LoadTexture("Textures\\BackButton.tga");
  WEGraphics::SetTextureColor(255, 255, 255, 255);
  /*All drawing in this state is in screen space*/
  WEGraphics::SetToOrtho();
}

/******************************************************************************/
/*!
\brief
Init function that initialize state.
*/
/******************************************************************************/
void OptionStateInit(void)
{
  WEDEBUG_CREATE_CONSOLE();
  /*Reset the timer for this state*/

  Option_data.timerCount = 0.f;

  Option_data.pButtons = new Button[BUTTON_SIZE];

  //Setting Buttons
  Option_data.pButtons[0].pos = { 640, 450 };
  Option_data.pButtons[0].scale = { 310, 50 };
  Option_data.pButtons[0].texture = Option_data.windowTexture;



  Option_data.pButtons[1].pos = { 640, 210 };
  Option_data.pButtons[1].scale = { 120, 40 };
  Option_data.pButtons[1].texture = Option_data.backTexture;
}
/******************************************************************************/
/*!
\brief
Update function that update state.
*/
/******************************************************************************/
void OptionStateUpdate(float /*dt*/)
{
  float windowWidth = static_cast<float>(WEApplication::GetWidth());
  float windowHeight = static_cast<float>(WEApplication::GetHeight());

  //Button & click Interaction
  if (WEInput::IsTriggered(WE_MOUSE_LEFT))
  {
    WEVec2 click;
    WEInput::GetMouse(click);

    for (int i = 0; i < BUTTON_SIZE; ++i)
    {
      if (WEIntersection::PointRect(click, Option_data.pButtons[i].pos, Option_data.pButtons[i].scale.x, Option_data.pButtons[i].scale.y))
      {
        switch (i)
        {
        case 0:
          if (Option_data.pButtons[i].texture == Option_data.windowTexture)
          {
            Option_data.pButtons[i].texture = Option_data.fullscreenTexture;
            WEApplication::SetFullScreen(false);
            
          }
          else if (Option_data.pButtons[i].texture == Option_data.fullscreenTexture)
          {
            Option_data.pButtons[i].texture = Option_data.windowTexture;
            WEApplication::SetFullScreen(true);
            
          }


          break;
        

        case 1: WEStateManager::SetNextState(WEStateManager::GetPreviousState());
          
          break;
        }
      }
    }



  }

  WEGraphics::StartDraw();
  WEMtx44 transform;
  WEGraphics::SetTexture(Option_data.splashTexture);
  WEGraphics::SetTextureColor(255, 255, 255, 100);
  WEMtx44::MakeTransform(transform,
    1440,
    720,
    0.0f,
    windowWidth / 2,
    windowHeight / 2,
    0.0);
  WEGraphics::Draw(transform);

  //Get mouse
  WEVec2 click;
  WEInput::GetMouse(click);

  /*Set position scale and rotation of what I want to draw*/
  WEGraphics::SetTextureColor(255, 255, 255, 255);
  for (int i = 0; i < BUTTON_SIZE; ++i)
  {
	  if (!WEIntersection::PointRect(click, Option_data.pButtons[i].pos,
		  Option_data.pButtons[i].scale.x, Option_data.pButtons[i].scale.y))
	  {
		  WEGraphics::SetTexture(Option_data.pButtons[i].texture);
		  WEMtx44::MakeTransform(transform,
			  Option_data.pButtons[i].scale.x,
			  Option_data.pButtons[i].scale.y,
			  0.0f,
			  Option_data.pButtons[i].pos.x,
			  Option_data.pButtons[i].pos.y,
			  1);
		  WEGraphics::Draw(transform);
	  }

	  else 
	  {
		  WEGraphics::SetTexture(Option_data.pButtons[i].texture);
		  WEMtx44::MakeTransform(transform,
			  Option_data.pButtons[i].scale.x * 1.2f,
			  Option_data.pButtons[i].scale.y * 1.2f,
			  0.0f,
			  Option_data.pButtons[i].pos.x,
			  Option_data.pButtons[i].pos.y,
			  1);
		  WEGraphics::Draw(transform);
	  }
  }
  /*This must be called to after all drawing is completed*/
  WEGraphics::EndDraw();
}
/******************************************************************************/
/*!
\brief
Shutdown function that shutdown state.
*/
/******************************************************************************/
void OptionStateShutdown(void)
{
}
/******************************************************************************/
/*!
\brief
Unload function that unload state.
*/
/******************************************************************************/
void OptionStateUnload(void)
{
  /*We must unload the texture when we are done with the state*/

  WEGraphics::UnloadTexture(Option_data.splashTexture);
  WEGraphics::UnloadTexture(Option_data.fullscreenTexture);
  WEGraphics::UnloadTexture(Option_data.windowTexture);
  WEGraphics::UnloadTexture(Option_data.backTexture);
}
