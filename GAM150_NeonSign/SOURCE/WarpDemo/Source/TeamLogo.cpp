/******************************************************************************/
/*!
\file   TeamLogo.cpp
\title  Neon sign
\author Junhyung Kim
\par    GAM150
\brief  This is the interface file for team logo state.

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#include "TeamLogo.h"

#include "WEApplication.h"
#include "WEDebugTools.h"
#include "WEMath.h"
#include "WEVec2.h"
#include "WEMtx44.h"
#include "WEStateManager.h"
#include "WEGraphics.h"
#include "WEInput.h"

#include "State.h"

#include <cstdio>

/*Make a struct for my shared state data*/
namespace
{
  struct InitData
  {
    int splashTexture;
    float timerCount;
  };

  /*The max time to be in this state*/
  const float SPLASH_MAX_TIME = 4.0f;
  const int   ARRAY_SIZE = 20;

  /*Create a static variable for data so it can't be used in other files.*/
  InitData s_data;
}



/******************************************************************************/
/*!
The load state will only be called once, when the state is first entered.
You should load resources that won't need to be changed if the state is
restarted.

*/
/******************************************************************************/
void LogoStateLoad(void)
{

  /*Load the only texture we need for this state*/
  s_data.splashTexture = WEGraphics::LoadTexture("Textures\\TeamLogo.tga");

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
void LogoStateInit(void)
{
  /*Reset the timer for this state*/
  s_data.timerCount = 0.f;
}
/******************************************************************************/
/*!
The update function will be called once per frame.  This is where all the
action, behavoir, drawing and state changes should happen.
*/
/******************************************************************************/
void LogoStateUpdate(float dt)
{
  WEMtx44 transform;
  char timeAsText[ARRAY_SIZE];
  float windowWidth = (float)WEApplication::GetWidth();
  float windowHeight = (float)WEApplication::GetHeight();


  /*increment timer*/
  s_data.timerCount += dt;

  //Save my time as a string.
  sprintf_s(timeAsText, "%.2f", SPLASH_MAX_TIME - s_data.timerCount);

  /*Check for time, only be in this state for the
  set time*/
  if (s_data.timerCount > SPLASH_MAX_TIME || WEInput::IsTriggered(WE_SPACE))
    WEStateManager::SetNextState(DS_STATE_STORY);

  /*Set position scale and rotation of what I want to draw*/
  WEMtx44::MakeTransform(transform,
    512,
    256,
    0.0f,
    windowWidth / 2,
    windowHeight / 2,
    0.0);

  /*This must be called before any drawing in the frame.*/
  WEGraphics::StartDraw();

  /*Set the image to draw*/
  WEGraphics::SetTexture(s_data.splashTexture);

  //Once we have set the texture we can draw it with a transform
  WEGraphics::Draw(transform);

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
void LogoStateShutdown(void)
{
}
/******************************************************************************/
/*!
This is the unload state.  Use this state to clean up any resources from the
load state.  Here I need to destroy my console and unload my texture.

*/
/******************************************************************************/
void LogoStateUnload(void)
{

  /*We must unload the texture when we are done with the state*/
  WEGraphics::UnloadTexture(s_data.splashTexture);
}
