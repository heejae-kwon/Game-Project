/******************************************************************************/
/*!
\file   Goal.cpp
\title  Neon sign
\author HeeJae Kwon
\par    GAM150
\brief  The file that includes Goal's functions

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#include "Goal.h"
#include "FmodData.h"//For Sound

/******************************************************************************/
/*!
\brief Create Goal

\param data
Get map data
*/
/******************************************************************************/
void CreateGoal(Play &data)
{
	for (int i = 0; i < data.maxGoals; ++i)
	{
		WEVec2 pos = data.pGoals[i].pos;
		WEVec2 scale = data.pGoals[i].scale;
		Action action;
		float radius = scale.x * 0.5f;

		//Quit Button
		action = QuitAction;
		data.pObjMgr->AddGoal(pos, scale, radius, 255, 255, 255, 255, action);
	}


}//CreateGoal

/******************************************************************************/
/*!
\brief Update Goal

\param pBalls
The pointer of balls

\param pGoals
The pointer of goals

\param data
Get map data

\param dt

*/
/******************************************************************************/
void UpdateGoal(Ball *pBalls, Object *pGoals, Play &data, float dt)
{
	for (int i = 0; i < data.pObjMgr->GetBallCount(); ++i)
	{
		for (int j = 0; j < data.pObjMgr->GetGoalCount(); ++j)
		{
			//Goal check is 0 and Touch the goal
			if (data.GoalValue == 0 && WEIntersection::CircleCircle(pBalls[i].pos, pBalls[i].radius, pGoals[j].pos, pGoals[j].radius))
			{
				//Sound
				data.FmodData.result = data.FmodData.system->playSound(data.FmodData.sound2, 0, false, &data.FmodData.channel);
			}

			//Ball touch the Goal
			if (WEIntersection::CircleCircle(pBalls[i].pos, pBalls[i].radius, pGoals[j].pos, pGoals[j].radius))
			{
				//Goal Color
				WEGraphics::SetBackgroundColor(data.GoalValue, data.GoalValue, data.GoalValue);

				WEVec2 normal;

				//Get normalize of go center of goal
				WEVec2::Normalize(normal, pGoals[j].pos - pBalls[i].pos);

				//Go to center of goal
				pBalls[i].vel = normal * dt * 4000;

				//+time
				data.GoalValue += dt;
			}

			if (data.GoalValue > LeveltoLevelDT)
			{
				//Level Control + 1
				++data.LevelControl;

				//Quit Sound
				data.FmodData.result = data.FmodData.sound->release();

				//Reset goal check
				data.GoalValue = 0;

				//Restart the map
				WEStateManager::Restart();
			}
		}
	}
}

/******************************************************************************/
/*!
\brief 
Draw Goal

\param pGoals
The pointer of goals

\param data
Get map data
*/
/******************************************************************************/
void DrawGoal(const Object *pGoals, const Play &data)
{
	//Set Texture Coords
	WEGraphics::SetTextureCoords(1, 1, 0, 0, 0);

	WEMtx44 tranform;

	//What to draw
	WEGraphics::SetTexture(data.TextureData.goalTexture);

	//Draw Goal
	for (int i = 0; i < data.pObjMgr->GetGoalCount(); ++i)
	{
		WEGraphics::SetTextureColor(pGoals[i].red,
			pGoals[i].green,
			pGoals[i].blue,
			pGoals[i].alpha);
		WEMtx44::MakeTransform(tranform,
			pGoals[i].scale.x,
			pGoals[i].scale.y,
			0,
			pGoals[i].pos.x,
			pGoals[i].pos.y,
			0);
		WEGraphics::Draw(tranform);
	}
}
