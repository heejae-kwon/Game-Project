/******************************************************************************/
/*!
\file   Story.cpp
\title  Neon sign
\author Junhyung Kim
\par    GAM150
\brief  The file that includes Story state's functions

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#include "Story.h"

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
  struct InitData
  {
    int storyTextureOne;
    int storyTextureTwo;
    int storyTextureThree;
    int storyTextureFour;
    int storyTextureFive;
    int mainMenuTexture;
    float timerCount;
  };

  /*The max time to be in this state*/
  const float PhaseOne   = 30.0f;
  const float PhaseTwo   = 60.0f;
  const float PhaseThree = 80.0f;
  const float PhaseFour  = 100.0f;
  const float PhaseFive  = 120.0f;
  const int   ARRAY_SIZE = 20;

  /*Create a static variable for data so it can't be used in other files.*/
  InitData s_data;
  FmodData Fmod;
}



/******************************************************************************/
/*!
\brief
		Load function that load textures.
*/
/******************************************************************************/
void StoryStateLoad(void)
{

  /*Load the only texture we need for this state*/
  s_data.storyTextureOne   = WEGraphics::LoadTexture("Textures\\Story1.tga");
  s_data.storyTextureTwo   = WEGraphics::LoadTexture("Textures\\Story2.tga");
  s_data.storyTextureThree = WEGraphics::LoadTexture("Textures\\Story3.tga");
  s_data.storyTextureFour  = WEGraphics::LoadTexture("Textures\\Story4.tga");
  s_data.storyTextureFive  = WEGraphics::LoadTexture("Textures\\Story5.tga");
  s_data.mainMenuTexture   = WEGraphics::LoadTexture("Textures\\MainMenuWhite.tga");

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
void StoryStateInit(void)
{
  /*Reset the timer for this state*/
  s_data.timerCount = 0.f;

  /*Play music*/
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
Update function that update state.
*/
/******************************************************************************/
void StoryStateUpdate(float dt)
{
  WEMtx44 transform;
  char timeAsText[ARRAY_SIZE];
  float windowWidth = (float)WEApplication::GetWidth();
  float windowHeight = (float)WEApplication::GetHeight();

  /*increment timer*/
  s_data.timerCount += dt * 5;

  //Save my time as a string.
  sprintf_s(timeAsText, "%.2f", PhaseOne - s_data.timerCount);

  /*This must be called before any drawing in the frame.*/
  WEGraphics::StartDraw();

  WEGraphics::SetTextureColor(255, 255, 255, (unsigned char)s_data.timerCount);
  WEGraphics::SetTexture(s_data.mainMenuTexture);
  WEMtx44::MakeTransform(transform,
    1440,
    720,
    0.0f,
    windowWidth / 2,
    windowHeight / 2,
    0.0);
  WEGraphics::Draw(transform);

  /*Set the image to draw*/
  WEGraphics::SetTextureColor(255, 255, 255, 8 * (unsigned char)s_data.timerCount);
  
  if (10 * (unsigned char)s_data.timerCount > 255)
    WEGraphics::SetTextureColor(255, 255, 255, 255);
  
  WEGraphics::SetTexture(s_data.storyTextureOne);

  WEMtx44::MakeTransform(transform,
    1600,
    200,
    0.0f,
    windowWidth / 2,
    windowHeight / 2,
    0.0);

  if (s_data.timerCount > PhaseOne)
  {
    WEGraphics::SetTextureColor(255, 255, 255, 255);
    WEGraphics::SetTexture(s_data.storyTextureTwo);
  }

  if (s_data.timerCount > PhaseTwo)
  {
    WEGraphics::SetTextureColor(255, 255, 255, 255);
    WEGraphics::SetTexture(s_data.storyTextureThree);
  }

  if (s_data.timerCount > PhaseThree)
  {
    WEGraphics::SetTextureColor(255, 255, 255, 255);
    WEGraphics::SetTexture(s_data.storyTextureFour);
  }

  if (s_data.timerCount > PhaseFour)
  {
    WEGraphics::SetTextureColor(255, 255, 255, 255);
    WEGraphics::SetTexture(s_data.storyTextureFive);
  }

  if (s_data.timerCount > PhaseFive || WEInput::IsAnyTriggered())
  {
    Fmod.result = Fmod.sound->release();
    WEStateManager::SetNextState(DS_STATE_MAINMENU);
  }

  //Once we have set the texture we can draw it with a transform
  WEGraphics::Draw(transform);

  /*This must be called to after all drawing is completed*/
  WEGraphics::EndDraw();
}
/******************************************************************************/
/*!
Shutdown function that shutdown state.
*/
/******************************************************************************/
void StoryStateShutdown(void)
{
  Fmod.result = Fmod.system->close();
  Fmod.result = Fmod.system->release();
}
/******************************************************************************/
/*!
Unload function that unload state.
*/
/******************************************************************************/
void StoryStateUnload(void)
{

  /*We must unload the texture when we are done with the state*/
  WEGraphics::UnloadTexture(s_data.storyTextureOne);
  WEGraphics::UnloadTexture(s_data.storyTextureTwo);
  WEGraphics::UnloadTexture(s_data.storyTextureThree);
  WEGraphics::UnloadTexture(s_data.storyTextureFour);
  WEGraphics::UnloadTexture(s_data.storyTextureFive);
  WEGraphics::UnloadTexture(s_data.mainMenuTexture);
}
