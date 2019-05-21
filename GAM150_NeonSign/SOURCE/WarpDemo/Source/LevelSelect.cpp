/******************************************************************************/
/*!
\file   LevelSelect.cpp
\title  Neon sign
\author HeeJae Kwon
\par    GAM150
\brief  The file that includes LevelSelect state's functions

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#include "LevelSelect.h"

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
#include <iostream>

/*Make a struct for my shared state data*/
namespace
{

	/*The max time to be in this state*/
	const float SPLASH_MAX_TIME = 1.0f;
	const int   ARRAY_SIZE = 20;
	const int BUTTON_SIZE = 10;

	struct Button
	{
		WEVec2 pos;
		WEVec2 scale;
		int texture;
		bool isActive;
	};

	struct Building
	{
		WEVec2 pos;
		WEVec2 scale;
		int texture;
	};

	struct InitData
	{
		int LevelControl;
		int MaxLevel;

		int buttonTexture[BUTTON_SIZE];
		int buildingTexture[BUTTON_SIZE-2];
		int buildingclearTexture[BUTTON_SIZE-2];

		Button Buttons[BUTTON_SIZE];
		Building Buildings[BUTTON_SIZE-2];
		float timerCount;

		std::string path;
	};


	/*Create a static variable for data so it can't be used in other files.*/

	InitData Level_data;

	/******************************************************************************/
	/*!
	\brief
	Read LevelControl number

	\param fileName
	The file that includes informations

	\param Level_data
	Get map data
	*/
	/******************************************************************************/
	void ReadLevelControl(const char* fileName, InitData &Level_data)
	{
		FILE* pFile = 0;

		fopen_s(&pFile, fileName, "rt");
		WEDEBUG_ASSERT(pFile != 0, "Can't open the file!!!");
		if (pFile)
		{
			fscanf_s(pFile, "%d", &Level_data.LevelControl);
			fscanf_s(pFile, "%d", &Level_data.MaxLevel);

			fclose(pFile);
		}
	}
	/******************************************************************************/
	/*!
	\brief
	Write LevelControl number

	\param fileName
	The file that includes informations

	\param Level_data
	Get map data
	*/
	/******************************************************************************/
	void WriteLevelControl(const char* fileName, const InitData &Level_data)
	{
		FILE* pFile = 0;

		fopen_s(&pFile, fileName, "wt");
		WEDEBUG_ASSERT(pFile != 0, "Can't open the file!!!");
		if (pFile)
		{
			fprintf(pFile, "%d\n", Level_data.LevelControl);
			fprintf(pFile, "%d\n", Level_data.MaxLevel);

			fclose(pFile);
		}

	}
}




/******************************************************************************/
/*!

\brief
	
*/
/******************************************************************************/
void LevelSelectStateLoad(void)
{

	/*Load the only texture we need for this state*/
	Level_data.buildingTexture[0] = WEGraphics::LoadTexture("Textures\\LevelBuilding1.tga");
	Level_data.buildingTexture[1] = WEGraphics::LoadTexture("Textures\\LevelBuilding2.tga");
	Level_data.buildingTexture[2] = WEGraphics::LoadTexture("Textures\\LevelBuilding3.tga");
	Level_data.buildingTexture[3] = WEGraphics::LoadTexture("Textures\\LevelBuilding4.tga");
	Level_data.buildingTexture[4] = WEGraphics::LoadTexture("Textures\\LevelBuilding5.tga");
	Level_data.buildingTexture[5] = WEGraphics::LoadTexture("Textures\\LevelBuilding6.tga");
	Level_data.buildingTexture[6] = WEGraphics::LoadTexture("Textures\\LevelBuilding7.tga");
	Level_data.buildingTexture[7] = WEGraphics::LoadTexture("Textures\\LevelBuilding8.tga");


	Level_data.buildingclearTexture[0] = WEGraphics::LoadTexture("Textures\\LevelBuilding1C.tga");
	Level_data.buildingclearTexture[1] = WEGraphics::LoadTexture("Textures\\LevelBuilding2C.tga");
	Level_data.buildingclearTexture[2] = WEGraphics::LoadTexture("Textures\\LevelBuilding3C.tga");
	Level_data.buildingclearTexture[3] = WEGraphics::LoadTexture("Textures\\LevelBuilding4C.tga");
	Level_data.buildingclearTexture[4] = WEGraphics::LoadTexture("Textures\\LevelBuilding5C.tga");
	Level_data.buildingclearTexture[5] = WEGraphics::LoadTexture("Textures\\LevelBuilding6C.tga");
	Level_data.buildingclearTexture[6] = WEGraphics::LoadTexture("Textures\\LevelBuilding7C.tga");
	Level_data.buildingclearTexture[7] = WEGraphics::LoadTexture("Textures\\LevelBuilding8C.tga");


	Level_data.buttonTexture[0] = WEGraphics::LoadTexture("Textures\\LevelButton1.tga");
	Level_data.buttonTexture[1] = WEGraphics::LoadTexture("Textures\\LevelButton2.tga");
	Level_data.buttonTexture[2] = WEGraphics::LoadTexture("Textures\\LevelButton3.tga");
	Level_data.buttonTexture[3] = WEGraphics::LoadTexture("Textures\\LevelButton4.tga");
	Level_data.buttonTexture[4] = WEGraphics::LoadTexture("Textures\\LevelButton5.tga");
	Level_data.buttonTexture[5] = WEGraphics::LoadTexture("Textures\\LevelButton6.tga");
	Level_data.buttonTexture[6] = WEGraphics::LoadTexture("Textures\\LevelButton7.tga");
	Level_data.buttonTexture[7] = WEGraphics::LoadTexture("Textures\\LevelButton8.tga");
	Level_data.buttonTexture[8] = WEGraphics::LoadTexture("Textures\\Reset.tga");
	Level_data.buttonTexture[9] = WEGraphics::LoadTexture("Textures\\BackButton.tga");

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
void LevelSelectStateInit(void)
{
	WEDEBUG_CREATE_CONSOLE();
	/*Reset the timer for this state*/

	Level_data.timerCount = 0.f;

	//Setting Buttons
	Level_data.Buttons[0].pos = { 100, 245 };
	Level_data.Buttons[0].scale = { 110, 35 };
	Level_data.Buttons[0].texture = Level_data.buttonTexture[0];
	Level_data.Buttons[0].isActive = false;
	Level_data.Buildings[0].pos = { 100, 105 };
	Level_data.Buildings[0].scale = { 142, 217 };
	Level_data.Buildings[0].texture = Level_data.buildingTexture[0];

	
	Level_data.Buttons[1].pos = { 250, 380 };
	Level_data.Buttons[1].scale = { 110, 35 };
	Level_data.Buttons[1].texture = Level_data.buttonTexture[1];
	Level_data.Buttons[1].isActive = false;
	Level_data.Buildings[1].pos = { 250, 175 };
	Level_data.Buildings[1].scale = { 85, 353 };
	Level_data.Buildings[1].texture = Level_data.buildingTexture[1];

	Level_data.Buttons[2].pos = { 380, 443 };
	Level_data.Buttons[2].scale = { 110, 35 };
	Level_data.Buttons[2].texture = Level_data.buttonTexture[2];
	Level_data.Buttons[2].isActive = false;
	Level_data.Buildings[2].pos = { 380, 200 };
	Level_data.Buildings[2].scale = { 80, 410 };
	Level_data.Buildings[2].texture = Level_data.buildingTexture[2];

	Level_data.Buttons[3].pos = { 540, 552 };
	Level_data.Buttons[3].scale = { 110, 35 };
	Level_data.Buttons[3].texture = Level_data.buttonTexture[3];
	Level_data.Buttons[3].isActive = false;
	Level_data.Buildings[3].pos = { 540, 260 };
	Level_data.Buildings[3].scale = { 114, 533 };
	Level_data.Buildings[3].texture = Level_data.buildingTexture[3];

	Level_data.Buttons[4].pos = { 700, 378 };
	Level_data.Buttons[4].scale = { 110, 35 };
	Level_data.Buttons[4].texture = Level_data.buttonTexture[4];
	Level_data.Buttons[4].isActive = false;
	Level_data.Buildings[4].pos = { 700, 170 };
	Level_data.Buildings[4].scale = { 94, 345 };
	Level_data.Buildings[4].texture = Level_data.buildingTexture[4];

	Level_data.Buttons[5].pos = { 860, 583 };
	Level_data.Buttons[5].scale = { 110, 35 };
	Level_data.Buttons[5].texture = Level_data.buttonTexture[5];
	Level_data.Buttons[5].isActive = false;
	Level_data.Buildings[5].pos = { 860, 270 };
	Level_data.Buildings[5].scale = { 152, 550 };
	Level_data.Buildings[5].texture = Level_data.buildingTexture[5];

	Level_data.Buttons[6].pos = { 1030, 506 };
	Level_data.Buttons[6].scale = { 110, 35 };
	Level_data.Buttons[6].texture = Level_data.buttonTexture[6];
	Level_data.Buttons[6].isActive = false;
	Level_data.Buildings[6].pos = { 1030, 230 };
	Level_data.Buildings[6].scale = { 92, 463 };
	Level_data.Buildings[6].texture = Level_data.buildingTexture[6];

	Level_data.Buttons[7].pos = { 1180, 567 };
	Level_data.Buttons[7].scale = { 110, 35 };
	Level_data.Buttons[7].texture = Level_data.buttonTexture[7];
	Level_data.Buttons[7].isActive = false;
	Level_data.Buildings[7].pos = { 1180, 260 };
	Level_data.Buildings[7].scale = { 130, 534 };
	Level_data.Buildings[7].texture = Level_data.buildingTexture[7];

	//reset button
	Level_data.Buttons[8].pos = { 80, 690 };
	Level_data.Buttons[8].scale = { 110, 35 };
	Level_data.Buttons[8].texture = Level_data.buttonTexture[8];
	Level_data.Buttons[8].isActive = true;
	//back button
	Level_data.Buttons[9].pos = { 1200, 690 };
	Level_data.Buttons[9].scale = { 110, 40 };
	Level_data.Buttons[9].texture = Level_data.buttonTexture[9];
	Level_data.Buttons[9].isActive = true;


	Level_data.path = getenv("USERPROFILE");
	Level_data.path += "/My Documents/NeonSign/LevelControl.txt";

	ReadLevelControl(Level_data.path.c_str(), Level_data);
	/*Reset the timer for this state*/

	for (int i = 0;i<= Level_data.MaxLevel;++i)
	{
		Level_data.Buttons[i].isActive = true;

		if (i != 0)
		Level_data.Buildings[i-1].texture = Level_data.buildingclearTexture[i-1];
	}
}
/******************************************************************************/
/*!
The update function will be called once per frame.  This is where all the
action, behavoir, drawing and state changes should happen.
*/ 
/******************************************************************************/
void LevelSelectStateUpdate(float /*dt*/)
{
	/*float windowWidth = static_cast<float>(WEApplication::GetWidth());
	float windowHeight = static_cast<float>(WEApplication::GetHeight());*/

	//Button & click Interaction
	if (WEInput::IsTriggered(WE_MOUSE_LEFT))
	{
		WEVec2 click;
		WEInput::GetMouse(click);

		for (int i = 0; i < BUTTON_SIZE; ++i)
		{
			if (WEIntersection::PointRect(click, Level_data.Buttons[i].pos, Level_data.Buttons[i].scale.x, Level_data.Buttons[i].scale.y) && Level_data.Buttons[i].isActive == true)
			{
				switch (i)
				{
				case 0:
					Level_data.LevelControl = 0;
					WEStateManager::SetNextState(DS_STATE_PLAY);
					break;
				case 1:
					Level_data.LevelControl = 1;
					WEStateManager::SetNextState(DS_STATE_PLAY);
					break;
				case 2:
					Level_data.LevelControl = 2;
					WEStateManager::SetNextState(DS_STATE_PLAY);
					break;
				case 3:
					Level_data.LevelControl = 3;
					WEStateManager::SetNextState(DS_STATE_PLAY);
					break;
				case 4:
					Level_data.LevelControl = 4;
					WEStateManager::SetNextState(DS_STATE_PLAY);
					break;
				case 5:
					Level_data.LevelControl = 5;
					WEStateManager::SetNextState(DS_STATE_PLAY);
					break;
				case 6:
					Level_data.LevelControl = 6;
					WEStateManager::SetNextState(DS_STATE_PLAY);
					break;
				case 7:
					Level_data.LevelControl = 7;
					WEStateManager::SetNextState(DS_STATE_PLAY);
					break;
				case 8:
					Level_data.LevelControl = 0;
					Level_data.MaxLevel = 0;
					WEStateManager::Restart();
					break;
				case 9:
					WEStateManager::SetNextState(DS_STATE_MAINMENU);
					break;
				}
			}
		}



	}

	WEGraphics::StartDraw();
	WEMtx44 transform;

	//Get mouse
	WEVec2 click;
	WEInput::GetMouse(click);

	//For buildings
	WEGraphics::SetTextureColor(255, 255, 255, 255);
	for (int i = 0; i < BUTTON_SIZE-2; ++i)
	{
		WEGraphics::SetTexture(Level_data.Buildings[i].texture);
		WEMtx44::MakeTransform(transform,
			Level_data.Buildings[i].scale.x,
			Level_data.Buildings[i].scale.y,
			0.0f,
			Level_data.Buildings[i].pos.x,
			Level_data.Buildings[i].pos.y,
			1);
		WEGraphics::Draw(transform);
	}

	/*Set position scale and rotation of what I want to draw*/
	WEGraphics::SetTextureColor(255, 255, 255, 255);
	for (int i = 0; i < 8; ++i)
	{
		//If We can't enter that stage, it's color is darker than other
		if (i > Level_data.MaxLevel)
			WEGraphics::SetTextureColor(255, 255, 255, 100);

		//Mouse is not on the that button
		if (!WEIntersection::PointRect(click, Level_data.Buttons[i].pos,
			Level_data.Buttons[i].scale.x, Level_data.Buttons[i].scale.y)
			|| i > Level_data.MaxLevel)
		{
			WEGraphics::SetTexture(Level_data.Buttons[i].texture);
			WEMtx44::MakeTransform(transform,
				Level_data.Buttons[i].scale.x,
				Level_data.Buttons[i].scale.y,
				0.0f,
				Level_data.Buttons[i].pos.x,
				Level_data.Buttons[i].pos.y,
				1);
			WEGraphics::Draw(transform);
		}

		else
		{
			WEGraphics::SetTexture(Level_data.Buttons[i].texture);
			WEMtx44::MakeTransform(transform,
				Level_data.Buttons[i].scale.x * 1.2f,
				Level_data.Buttons[i].scale.y * 1.2f,
				0.0f,
				Level_data.Buttons[i].pos.x,
				Level_data.Buttons[i].pos.y,
				1);
			WEGraphics::Draw(transform);
		}

		//Reset graphics
		WEGraphics::SetTextureColor(255, 255, 255, 255);
	}

	//Other buttons
	for (int i = 8; i < BUTTON_SIZE; ++i)
	{
		if (!WEIntersection::PointRect(click, Level_data.Buttons[i].pos,
			Level_data.Buttons[i].scale.x, Level_data.Buttons[i].scale.y))
		{
			WEGraphics::SetTexture(Level_data.Buttons[i].texture);
			WEMtx44::MakeTransform(transform,
				Level_data.Buttons[i].scale.x,
				Level_data.Buttons[i].scale.y,
				0.0f,
				Level_data.Buttons[i].pos.x,
				Level_data.Buttons[i].pos.y,
				1);
			WEGraphics::Draw(transform);
		}

		else
		{
			WEGraphics::SetTexture(Level_data.Buttons[i].texture);
			WEMtx44::MakeTransform(transform,
				Level_data.Buttons[i].scale.x * 1.2f,
				Level_data.Buttons[i].scale.y * 1.2f,
				0.0f,
				Level_data.Buttons[i].pos.x,
				Level_data.Buttons[i].pos.y,
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
void LevelSelectStateShutdown(void)
{
	WriteLevelControl(Level_data.path.c_str(), Level_data);
	/*Reset the timer for this state*/
}
/******************************************************************************/
/*!
This is the unload state.  Use this state to clean up any resources from the
load state.  Here I need to destroy my console and unload my texture.

*/
/******************************************************************************/
void LevelSelectStateUnload(void)
{
	/*We must unload the texture when we are done with the state*/

	for (int i = 0; i < BUTTON_SIZE-2; ++i)
	{
		WEGraphics::UnloadTexture(Level_data.buildingTexture[i]);
		WEGraphics::UnloadTexture(Level_data.buildingclearTexture[i]);
	}

	for (int i = 0; i < BUTTON_SIZE; ++i)
		WEGraphics::UnloadTexture(Level_data.buttonTexture[i]);
}
