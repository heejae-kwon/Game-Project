/******************************************************************************/
/*!
\file   Ending.cpp
\title  Neon sign
\author Junhyung Kim
\par    GAM150
\brief  This is the interface file for the ending state.

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#include "Ending.h"

#include "Play.h"

#include "FmodData.h"
#include "Music.h"
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
	struct Building
	{
		WEVec2 pos;
		WEVec2 scale;
		int texture;
	};

  struct InitData
  {
    int clearTexture;
		int creditTextureOne;
		int creditTextureTwo;
		int creditTextureThree;
		int creditTextureFour;
    float timerCount;
		float scrollDown;
		float delayCount;

	int buildingclearTexture[8];
	Building Buildings[8];
	FmodData FmodData;
  };

  /*The max time to be in this state*/
  const float SPLASH_MAX_TIME = 1.0f;
  const int   ARRAY_SIZE = 20;

  /*Create a static variable for data so it can't be used in other files.*/
  InitData s_data;
}



/******************************************************************************/
/*!

\brief 
	The function that load textures
*/
/******************************************************************************/
void EndingStateLoad(void)
{

  /*Load the only texture we need for this state*/
  s_data.clearTexture = WEGraphics::LoadTexture("Textures\\Clear.tga");
	s_data.creditTextureOne = WEGraphics::LoadTexture("Textures\\CreditOne.tga");
	s_data.creditTextureTwo = WEGraphics::LoadTexture("Textures\\CreditTwo.tga");
	s_data.creditTextureThree = WEGraphics::LoadTexture("Textures\\CreditThree.tga");
	s_data.creditTextureFour = WEGraphics::LoadTexture("Textures\\CreditFour.tga");

  s_data.buildingclearTexture[0] = WEGraphics::LoadTexture("Textures\\LevelBuilding1C.tga");
  s_data.buildingclearTexture[1] = WEGraphics::LoadTexture("Textures\\LevelBuilding2C.tga");
  s_data.buildingclearTexture[2] = WEGraphics::LoadTexture("Textures\\LevelBuilding3C.tga");
  s_data.buildingclearTexture[3] = WEGraphics::LoadTexture("Textures\\LevelBuilding4C.tga");
  s_data.buildingclearTexture[4] = WEGraphics::LoadTexture("Textures\\LevelBuilding5C.tga");
  s_data.buildingclearTexture[5] = WEGraphics::LoadTexture("Textures\\LevelBuilding6C.tga");
  s_data.buildingclearTexture[6] = WEGraphics::LoadTexture("Textures\\LevelBuilding7C.tga");
  s_data.buildingclearTexture[7] = WEGraphics::LoadTexture("Textures\\LevelBuilding8C.tga");

  WEGraphics::SetTextureColor(255, 255, 255, 255);
  /*All drawing in this state is in screen space*/
  WEGraphics::SetToOrtho();
}
/******************************************************************************/
/*!

	\brief
		The function that initialize states.
*/
/******************************************************************************/
void EndingStateInit(void)
{
  /*Reset the timer for this state*/
  s_data.timerCount = 0.f;
	s_data.scrollDown = -4.0f;
	s_data.delayCount = 0.f;

  s_data.Buildings[0].pos = { 100, 105 };
  s_data.Buildings[0].scale = { 142, 217 };
  s_data.Buildings[0].texture = s_data.buildingclearTexture[0];

  s_data.Buildings[1].pos = { 250, 175 };
  s_data.Buildings[1].scale = { 85, 353 };
  s_data.Buildings[1].texture = s_data.buildingclearTexture[1];

  s_data.Buildings[2].pos = { 380, 200 };
  s_data.Buildings[2].scale = { 80, 410 };
  s_data.Buildings[2].texture = s_data.buildingclearTexture[2];

  s_data.Buildings[3].pos = { 540, 260 };
  s_data.Buildings[3].scale = { 114, 533 };
  s_data.Buildings[3].texture = s_data.buildingclearTexture[3];

  s_data.Buildings[4].pos = { 700, 170 };
  s_data.Buildings[4].scale = { 94, 345 };
  s_data.Buildings[4].texture = s_data.buildingclearTexture[4];

  s_data.Buildings[5].pos = { 860, 270 };
  s_data.Buildings[5].scale = { 152, 550 };
  s_data.Buildings[5].texture = s_data.buildingclearTexture[5];

  s_data.Buildings[6].pos = { 1030, 225 };
  s_data.Buildings[6].scale = { 92, 463 };
  s_data.Buildings[6].texture = s_data.buildingclearTexture[6];

  s_data.Buildings[7].pos = { 1180, 260 };
  s_data.Buildings[7].scale = { 130, 534 };
  s_data.Buildings[7].texture = s_data.buildingclearTexture[7];


  //FMOD
  /*Play music*/

  MusicInit(s_data.FmodData);


	s_data.FmodData.result = s_data.FmodData.system->createSound(Common_MediaPath("EndingBGM.ogg"), FMOD_LOOP_NORMAL | FMOD_2D, 0, &s_data.FmodData.sound);
	s_data.FmodData.result = s_data.FmodData.sound->getNumSubSounds(&s_data.FmodData.numsubsounds);
	if (s_data.FmodData.numsubsounds)
		s_data.FmodData.sound->getSubSound(0, &s_data.FmodData.sound_to_play);
  else

		s_data.FmodData.sound_to_play = s_data.FmodData.sound;
	s_data.FmodData.result = s_data.FmodData.system->playSound(s_data.FmodData.sound_to_play, 0, false, &s_data.FmodData.channel);

}
/******************************************************************************/
/*!

	\brief
		The function that keep updates ending state.

	\param dt
*/
/******************************************************************************/
void EndingStateUpdate(float dt)
{
  WEMtx44 transform;
  char timeAsText[ARRAY_SIZE];
  float windowWidth = (float)WEApplication::GetWidth();
  float windowHeight = (float)WEApplication::GetHeight();


  /*increment timer*/
  s_data.timerCount += dt;
	s_data.scrollDown += dt;
	s_data.delayCount += dt;

  //Save my time as a string.
  sprintf_s(timeAsText, "%.2f", SPLASH_MAX_TIME - s_data.timerCount);

  /*Check for time, only be in this state for the
  set time*/


	if (WEInput::IsTriggered(WE_MOUSE_LEFT) && s_data.delayCount > 5.0)
  {
    WEVec2 click;
    WEInput::GetMouse(click);
	WEStateManager::SetNextState(DS_STATE_MAINMENU);
  }
  /*Set position scale and rotation of what I want to draw*/
  WEMtx44::MakeTransform(transform,
    800,
    1000,
    0.0f,
    windowWidth / 2,
    windowHeight / 2,
    0.0);

  /*This must be called before any drawing in the frame.*/
  WEGraphics::StartDraw();


  if (s_data.timerCount < 0.5f)
  {
	  WEGraphics::SetTextureColor(255, 255, 255, 30);
  }

  else if (s_data.timerCount < 1.f)
  {
	  WEGraphics::SetTextureColor(255, 255, 255, 100);
  }

  else if (s_data.timerCount < 1.5f)
  {
	  WEGraphics::SetTextureColor(255, 255, 255, 255);
  }

  else
  {
	  s_data.timerCount = 0;
  }



	//Delay between credit and clear image

	if (s_data.delayCount < 4.0)
	{
		for (int i = 0; i < 8; ++i)
		{
			WEGraphics::SetTexture(s_data.Buildings[i].texture);
			WEMtx44::MakeTransform(transform,
				s_data.Buildings[i].scale.x,
				s_data.Buildings[i].scale.y,
				0.0f,
				s_data.Buildings[i].pos.x,
				s_data.Buildings[i].pos.y,
				1);
			WEGraphics::Draw(transform);
		}


		WEGraphics::SetTexture(s_data.clearTexture);
		WEMtx44::MakeTransform(transform,
			512,
			512,
			0.0f,
			230,
			550,
			1);
		WEGraphics::Draw(transform);
	}

	else
	{
		for (int i = 0; i < 8; ++i)
		{
			WEGraphics::SetTexture(s_data.Buildings[i].texture);
			WEMtx44::MakeTransform(transform,
				s_data.Buildings[i].scale.x,
				s_data.Buildings[i].scale.y,
				0.0f,
				s_data.Buildings[i].pos.x,
				s_data.Buildings[i].pos.y + 50 * s_data.scrollDown,
				1);
			WEGraphics::Draw(transform);
		}


		WEGraphics::SetTexture(s_data.clearTexture);
		WEMtx44::MakeTransform(transform,
			512,
			512,
			0.0f,
			230,
			550 + 50 * s_data.scrollDown,
			1);
		WEGraphics::Draw(transform);

		//Credit


		WEGraphics::SetTextureColor(255, 255, 255, 255);

		WEGraphics::SetTexture(s_data.creditTextureOne);
		WEMtx44::MakeTransform(transform,
			960,
			540,
			0.0f,
			640,
			-360 + 50 * s_data.scrollDown,
			1);
		WEGraphics::Draw(transform);


		WEGraphics::SetTexture(s_data.creditTextureTwo);
		WEMtx44::MakeTransform(transform,
			960,
			540,
			0.0f,
			640,
			-900 + 50 * s_data.scrollDown,
			1);
		WEGraphics::Draw(transform);

		WEGraphics::SetTexture(s_data.creditTextureThree);
		WEMtx44::MakeTransform(transform,
			960,
			540,
			0.0f,
			640,
			-1440 + 50 * s_data.scrollDown,
			1);
		WEGraphics::Draw(transform);

		WEGraphics::SetTexture(s_data.creditTextureFour);
		WEMtx44::MakeTransform(transform,
			960,
			540,
			0.0f,
			640,

			-2100 + 50 * s_data.scrollDown,
			1);
		WEGraphics::Draw(transform);
	}


	

  //Once we have set the texture we can draw it with a transform
  WEGraphics::Draw(transform);

  /*This must be called to after all drawing is completed*/
  WEGraphics::EndDraw();
}
/******************************************************************************/
/*!

\brief 
	The function that shutdown the state.
*/
/******************************************************************************/
void EndingStateShutdown(void)
{

	s_data.FmodData.result = s_data.FmodData.system->close();
	s_data.FmodData.result = s_data.FmodData.system->release();
}
/******************************************************************************/
/*!

\brief
The function that unload the texture.
*/
/******************************************************************************/
void EndingStateUnload(void)
{

	for (int i = 0; i < 8; ++i)
	{
		WEGraphics::UnloadTexture(s_data.buildingclearTexture[i]);
	}


  /*We must unload the texture when we are done with the state*/
  WEGraphics::UnloadTexture(s_data.clearTexture);
	WEGraphics::UnloadTexture(s_data.creditTextureOne);
	WEGraphics::UnloadTexture(s_data.creditTextureTwo);
	WEGraphics::UnloadTexture(s_data.creditTextureThree);
	WEGraphics::UnloadTexture(s_data.creditTextureFour);
}
