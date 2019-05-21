/******************************************************************************/
/*!
\file   HowTo.cpp
\title  Neon sign
\author Junhyung Kim
\par    GAM150
\brief  This is the interface file for the how to play state.

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
		int howToTexture;
		int howToTwoTexture;

		int nextTexture;
		int nextTwoTexture;
		int backTexture;

		Button *pButtons;
		float timerCount;
	};

	/*The max time to be in this state*/
	const float SPLASH_MAX_TIME = 1.0f;
	const int   ARRAY_SIZE = 20;
	const int   BUTTON_SIZE = 2;

	int pageCheck;
	/*Create a static variable for data so it can't be used in other files.*/

	InitData Option_data;
}



/******************************************************************************/
/*!
The load state will only be called once, when the state is first entered.
You should load resources that won't need to be changed if the state is
restarted.

*/
/******************************************************************************/
void HowToStateLoad(void)
{

	/*Load the only texture we need for this state*/
	Option_data.howToTexture    = WEGraphics::LoadTexture("Textures\\HowTo.tga");
	Option_data.howToTwoTexture = WEGraphics::LoadTexture("Textures\\HowToTwo.tga");

	Option_data.backTexture    = WEGraphics::LoadTexture("Textures\\BackButton.tga");
	Option_data.nextTexture    = WEGraphics::LoadTexture("Textures\\Next.tga");
	Option_data.nextTwoTexture = WEGraphics::LoadTexture("Textures\\NextTwo.tga");

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
void HowToStateInit(void)
{
	WEDEBUG_CREATE_CONSOLE();
	/*Reset the timer for this state*/

	Option_data.timerCount = 0.f;

	Option_data.pButtons = new Button[BUTTON_SIZE];

	//Setting Buttons
	Option_data.pButtons[0].pos = { 1190, 680 };
	Option_data.pButtons[0].scale = { 120, 40 };
	Option_data.pButtons[0].texture = Option_data.backTexture;


	Option_data.pButtons[1].pos = { 1180, 340 };
	Option_data.pButtons[1].scale = { 70, 70 };
	Option_data.pButtons[1].texture = Option_data.nextTexture;

	pageCheck = 1;
}
/******************************************************************************/
/*!
The update function will be called once per frame.  This is where all the
action, behavoir, drawing and state changes should happen.
*/
/******************************************************************************/
void HowToStateUpdate(float /*dt*/)
{
	float windowWidth  = static_cast<float>(WEApplication::GetWidth());
	float windowHeight = static_cast<float>(WEApplication::GetHeight());

	if (WEInput::IsTriggered(WE_ESCAPE))
		WEStateManager::SetNextState(WEStateManager::GetPreviousState());

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
					//Click Back
				case 0:
					WEStateManager::SetNextState(WEStateManager::GetPreviousState());
					break;

					//Click the Arrow
				case 1:
				{
					//If first page
					if (pageCheck == 1)
					{
						Option_data.pButtons[1].texture = Option_data.nextTwoTexture;
						pageCheck = 2;
						break;
					}

					else
					{
						Option_data.pButtons[1].texture = Option_data.nextTexture;
						pageCheck = 1;
						break;
					}
				}
				}
			}
		}
	}

	WEGraphics::StartDraw();
	WEMtx44 transform;

	//Draw HowTo Texture
	if (pageCheck == 1)
	{
		WEGraphics::SetTexture(Option_data.howToTexture);
		WEGraphics::SetTextureColor(255, 255, 255, 255);
		WEMtx44::MakeTransform(transform,
			1280,
			720,
			0.0f,
			windowWidth / 2,
			windowHeight / 2,
			0.0);
		WEGraphics::Draw(transform);
	}

	else
	{
		WEGraphics::SetTexture(Option_data.howToTwoTexture);
		WEGraphics::SetTextureColor(255, 255, 255, 255);
		WEMtx44::MakeTransform(transform,
			1280,
			720,
			0.0f,
			windowWidth / 2,
			windowHeight / 2,
			0.0);
		WEGraphics::Draw(transform);
	}


	/*Set position scale and rotation of what I want to draw*/
	WEGraphics::SetTextureColor(255, 255, 255, 255);
	for (int i = 0; i < BUTTON_SIZE; ++i)
	{
		//Get mouse
		WEVec2 click;
		WEInput::GetMouse(click);

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

		//If Mouse is on the button, it will be bigger
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


	/*This must be called before any drawing in the frame.*/



	/*Set the image to draw*/



	//Once we have set the texture we can draw it with a transform



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
void HowToStateShutdown(void)
{
}
/******************************************************************************/
/*!
This is the unload state.  Use this state to clean up any resources from the
load state.  Here I need to destroy my console and unload my texture.

*/
/******************************************************************************/
void HowToStateUnload(void)
{

	/*We must unload the texture when we are done with the state*/

	WEGraphics::UnloadTexture(Option_data.howToTexture);
	WEGraphics::UnloadTexture(Option_data.howToTwoTexture);
	WEGraphics::UnloadTexture(Option_data.backTexture);
	WEGraphics::UnloadTexture(Option_data.nextTexture);
	WEGraphics::UnloadTexture(Option_data.nextTwoTexture);
}
