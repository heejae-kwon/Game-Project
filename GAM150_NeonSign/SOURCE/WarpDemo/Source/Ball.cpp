/******************************************************************************/
/*!
\file   Ball.cpp
\title  Neon sign
\author Kim gue sik
\par    GAM150
\brief
To do ball movement and decision ball direction and draw the ball, limit border

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#include "Ball.h"
/******************************************************************************/
/*!
\param pBalls
Get Ball struct

\param ballID
Update the ball which has this ID

\param dt
Get the time

\brief
Update Ball Movement
*/
/******************************************************************************/
void BallMovement(Ball *pBalls, int ballID, float dt)
{

  WEVec2 acc;

  //Get accel of it by it's force and mass
  acc = pBalls[ballID].forceSum * (1 / pBalls[ballID].mass);

  //Gravity
  acc.y -= 50;

  //To get ingame plus vel
  WEVec2 dVel = acc * dt * 2.5f;

  pBalls[ballID].vel += dVel;

  //to get ingame plus pos
  WEVec2 dPos = pBalls[ballID].vel * dt;

  pBalls[ballID].pos += dPos;

  //Fix bug Codes
  if (pBalls[ballID].vel.x < 0.00001f && pBalls[ballID].vel.x > -0.00001f)
	  pBalls[ballID].vel.x = 0.0005f;

  if (pBalls[ballID].vel.y < 0.00001f && pBalls[ballID].vel.y > -0.00001f)
	  pBalls[ballID].vel.y = 0.0005f;

  //We use force to get acc so Clear it
  pBalls[ballID].forceSum = { 0, 0 };

}//BallMovement

/******************************************************************************/
/*!
\param data
Get Play struct to make Ball

\brief
Create Ball
*/
/******************************************************************************/
void CreateBall(Play &data)
{
	//Ball Constructor
	for (int i = 0; i < data.maxBalls; ++i)
	{
		//Initialize values
		WEVec2 pos = data.pBalls[i].pos;
		WEVec2 vel = { 0, 0 };
		WEVec2 scale = data.pBalls[i].scale;

		WEVec2 forceSum;
		float mass;
		float radius;
		float rotation;
		float rotationVel;
		bool DynamicState;

		//Not click forceSum
		forceSum = { FORCE_SIZE * sqrt(2.f) * 0.5f, FORCE_SIZE * sqrt(2.f) * 0.5f };
		mass = 100;
		radius = scale.x * 0.5f;
		rotation = 0;
		rotationVel = 0;
		DynamicState = false;

		//To make Particle
		data.pParticleMgr->AddTrailEmitter(PARTICLE_COUNT, pos, vel, data.TextureData.particleTexture, ET_TRAIL);

		/*Add to the object manager*/
		data.pObjMgr->AddBall(pos, scale, vel, forceSum, mass, radius, rotation, rotationVel, DynamicState, 255, 255, 255, 255);
	}
}//CreateBall

/******************************************************************************/
/*!
\param pBall
Get Ball struct to get Ball information

\param pButtons
Get Object struct to shot the ball

\param data
Get Play struct to know block and ball conditions

\brief
Set Ball direction
*/
/******************************************************************************/
void BallDirection(Ball *pBalls, Object *pButtons, Play &data)
{

	for (int i = 0; i < data.pObjMgr->GetBallCount(); ++i)
	{
		//User click in limit range, change direction
		if (WEInput::IsPressed(WE_MOUSE_LEFT) && data.ConditionData.blockCondition == CanMove && data.ConditionData.ballCondition == Stoping && !WEInput::IsPressed(WE_P))
		{
			WEVec2 click;
			WEVec2 normal;
			WEInput::GetMouse(click);

			for (int j = 0; j < data.pObjMgr->GetButtonCount(); ++j)
			{
				//If User click button, just do button's action
				if (WEIntersection::PointRect(click, pButtons[j].pos, pButtons[j].scale.x, pButtons[j].scale.y))
				{
					data.BTCheck = true;
				}
			}

			//User don't click button
			if (data.BTCheck == false)
			{
				{
					//Get mouse position
					WEGraphics::ConvertScreenToWorld(click.x, click.y);

					//In the click range
					if (WEIntersection::PointCircle(click, pBalls[i].pos, DIRECTION_AREA) == false)
						return;

					//Set Shot Ball direction
					WEVec2::Normalize(normal, click - pBalls[i].pos);
					pBalls[i].vel = { 0, 0 };
					pBalls[i].forceSum.x = FORCE_SIZE * normal.x;
					pBalls[i].forceSum.y = FORCE_SIZE * normal.y;

					//Get before shot vector
					data.KeepNormal = normal;
				}
			}
		}
	}
}

/******************************************************************************/
/*!
\param pBall
Get Ball struct to get Ball information

\param data
Get Play struct to know ball conditions

\brief
Draw Ball
*/
/******************************************************************************/
void DrawBall(const Ball *pBalls, const Play &data)
{
	//Set Texture Coords
	WEGraphics::SetTextureCoords(1, 1, 0, 0, 0);

	//Initialize WEMtx44 to use
	WEMtx44 tranform;
	for (int i = 0; i < data.pObjMgr->GetBallCount(); ++i)
	{
		//What to draw
		WEGraphics::SetTexture(data.TextureData.ballTexture);

		//Texture's color
		WEGraphics::SetTextureColor(pBalls[i].red,
			pBalls[i].green,
			pBalls[i].blue,
			pBalls[i].alpha);

		//Draw it
		WEMtx44::MakeTransform(tranform,
			pBalls[i].scale.x,
			pBalls[i].scale.y,
			0,
			pBalls[i].pos.x,
			pBalls[i].pos.y,
			0);
		WEGraphics::Draw(tranform);

		//What to draw
		WEGraphics::SetTexture(data.TextureData.ballBorderTexture);

		//Texture's color
		WEGraphics::SetTextureColor(pBalls[i].red,
			pBalls[i].green,
			pBalls[i].blue,
			pBalls[i].alpha);

		//Draw it
		WEMtx44::MakeTransform(tranform,
			pBalls[i].scale.x + 1.5f,
			pBalls[i].scale.y + 1.5f,
			0,
			pBalls[i].pos.x,
			pBalls[i].pos.y,
			0);
		WEGraphics::Draw(tranform);
	}
}

/******************************************************************************/
/*!
\param pBall
Get Ball struct to get Ball information

\param data
Get Play struct to know ball conditions

\brief
Draw Ball direction Limit
*/
/******************************************************************************/
void DrawDirectionLimit(const Ball *pBalls, const Play &data)
{
	//Get user's mouse click
	WEVec2 click;
	WEInput::GetMouse(click);
	WEGraphics::ConvertScreenToWorld(click.x, click.y);

	for (int i = 0; i < data.pObjMgr->GetBallCount(); ++i)
	{
		//If user click out of range or shooting condition, we didn't draw it.
		if (WEIntersection::PointCircle(click, pBalls[i].pos, DIRECTION_AREA) == false || data.ConditionData.ballCondition == Shooting)
			return;

		//else draw ball click limit
		WEGraphics::SetTextureCoords(1, 1, 0, 0, 0);
		WEMtx44 tranform;

		//What to draw
		WEGraphics::SetTexture(data.TextureData.ballGuideTexture);
		WEGraphics::SetTextureColor(255,
			255,
			255,
			50);
		WEMtx44::MakeTransform(tranform,
			DIRECTION_AREA * 2,
			DIRECTION_AREA * 2,
			0,
			pBalls[i].pos.x,
			pBalls[i].pos.y,
			0);
		WEGraphics::Draw(tranform);
	}
}

/******************************************************************************/
/*!
\param pBall
Get Ball struct to get Ball information

\param pButtons
Get Object struct to get Button information

\param pArrow
Get Object struct to get Arrow information

\param data
Get Play struct to know ball conditions

\brief
Reset Ball Position
*/
/******************************************************************************/
void ResetBallPosition(Ball *pBalls, Object *pButtons, Object *pArrow, Play &data)
{
	//If condition is reset, change reset image to shoot image
	if (data.ConditionData.ballCondition == Resetting)
	{
		for (int i = 0; i < data.pObjMgr->GetButtonCount(); i++)
		{
			if (pButtons[i].texture == data.TextureData.stopTexture)
			{
				pButtons[i].texture = data.TextureData.shootTexture;
			}
		}

		//Get before shot vector
		WEVec2 normal = data.KeepNormal;

		//Get cos
		float cos = WEVec2::Dot(normal, { 1, 0 });

		//Reset the ball position and make ballCondition Stoping
		for (int i = 0; i < data.pObjMgr->GetBallCount(); ++i)
		{
			//position will be start and vel direction is before shoot
			pBalls[i].pos = data.pBalls[i].pos;
			pBalls[i].forceSum = { FORCE_SIZE * normal.x, FORCE_SIZE* normal.y };
			pBalls[i].vel = { 0, 0 };
			pArrow[0].pos.x = pBalls[i].pos.x + (normal.x * pArrow[0].scale.x);
			pArrow[0].pos.y = pBalls[i].pos.y + (normal.y * pArrow[0].scale.y);

			//To get arrow's rotation
			if (pBalls[i].pos.y < pArrow[0].pos.y)
				pArrow[0].rotation = WEMath::DegreeToRadian(My_Degreefloat(cos));

			else
				pArrow[0].rotation = WEMath::DegreeToRadian(-My_Degreefloat(cos));

			data.ConditionData.ballCondition = Stoping;
		}
	}//data.ballCondition == Resetting


	//if Ball get out of the monitor or Press 'R'
	for (int i = 0; i < data.pObjMgr->GetBallCount(); ++i)
	{
		//Out of screen or press R
		if ((pBalls[i].pos.x < data.topLeft.x) || (pBalls[i].pos.x > data.topRight.x) ||
			(pBalls[i].pos.y > data.topLeft.y) || (pBalls[i].pos.y < data.botLeft.y) || WEInput::IsTriggered(WE_R))
		{
			//Make ballCondition Resetting
			data.ConditionData.ballCondition = Resetting;
		}
	}
}
