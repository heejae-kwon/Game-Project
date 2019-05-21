/******************************************************************************/
/*!
\file   SB.cpp
\title  Neon sign
\author HeeJae Kwon, Kim gue sik
\par    GAM150
\brief  The file that includes SpecialBox's functions

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#include "SB.h"

/******************************************************************************/
/*!
\brief
Create Special Box

\param data
Get map data
*/
/******************************************************************************/
void CreateSB(Play &data)
{
  for (int i = 0; i < data.maxSB; ++i)
  {
    WEVec2 pos = data.pSB[i].pos;
    WEVec2 scale = data.pSB[i].scale;
    float rotation = data.pSB[i].rotation;
    data.pObjMgr->AddSB(pos, scale, rotation, 255, 255, 255, 255);
  }
}

/******************************************************************************/
/*!
\brief
Update Special Box

\param pBalls
The pointer of balls

\param pSB
The pointer of Special Box

\param dt

\param data
Get map data
*/
/******************************************************************************/
void UpdateSB(Ball *pBalls, Block *pSB, float dt, Play &data)
{
  for (int i = 0; i < data.pObjMgr->GetBallCount(); ++i)
  {
    for (int j = 0; j < data.pObjMgr->GetSBCount(); ++j)
    {
      if (WEIntersection::CircleRect(pBalls[i].pos, pBalls[i].radius,
        pSB[j].pos, pSB[j].scale.x, pSB[j].scale.y) && data.BS == true)
      {
        data.BSCheck = true;
      }
      else
      {
        data.BS = true;
        data.BSCheck = false;
      }
      
      if (data.BSCheck == true)
      {
        data.BS = false;
        data.SBdt += dt;

        WEVec2 normal;
        WEVec2::Normalize(normal, pSB[j].pos - pBalls[i].pos);
		data.Special = j;
        

        if (data.SBdt < 0.6f && static_cast<int>(pBalls[i].pos.x) != static_cast<int>(pSB[j].pos.x))
        {
          pBalls[i].vel = normal * dt * 2000;
        }
        else if (data.SBdt < 0.6f && static_cast<int>(pBalls[i].pos.x) == static_cast<int>(pSB[j].pos.x))
        {         
          pBalls[i].vel = { 0, 0 };
          pBalls[i].pos = pSB[j].pos;
        }
        else
        {
          int SBDegree = static_cast<int>(WEMath::RadianToDegree(pSB[j].rotation)) % 360;
		  pBalls[i].vel = { 0, 0 };

          //Decide Ball Direction
          //UP
          if ((SBDegree < 5 && SBDegree > -5) || SBDegree > 355 || SBDegree < -355)
            pBalls[i].forceSum = { 1, SB_FORCE_SIZE };
          //DOWN
          else if ((SBDegree < 185 && SBDegree > 175) || (SBDegree > -185 && SBDegree < -175))
            pBalls[i].forceSum = { 1, -SB_FORCE_SIZE };
          //RIGHT
          else if ((SBDegree < 275 && SBDegree > 265) || (SBDegree > -95 && SBDegree < -85))
            pBalls[i].forceSum = { SB_FORCE_SIZE, 1 };
          //LEFT
          else if ((SBDegree < 95 && SBDegree > 85) || (SBDegree > -275 && SBDegree < -265))
            pBalls[i].forceSum = { -SB_FORCE_SIZE, 1 };
        
		  
		  //To know it go outside of the SB at next dt.
		  BallMovement(pBalls, i, dt);

		  //Check Special box interect with ball
		  data.CheckSBInter = true;
        }

      }
	  
    }//end for j

	//Check ball is out of that special box
	if (data.CheckSBInter == true)
	data.CheckSBOut = WEIntersection::CircleRect(pBalls[i].pos, pBalls[i].radius, pSB[data.Special].pos, pSB[data.Special].scale.x, pSB[data.Special].scale.y);
  }//end for i

  //Reset Condition
  if (data.CheckSBInter == true && data.CheckSBOut == false)
  {
	  //FMOD
	  data.FmodData.result = data.FmodData.system->playSound(data.FmodData.sound4, 0, false, &data.FmodData.channel);

	  //Reset the SB time and two check
	  data.SBdt = 0;
	  data.CheckSBInter = false;
	  data.CheckSBOut   = true;
  }

  //If the condition is stoping, reset SB time
  if (data.ConditionData.ballCondition == Stoping)
    data.SBdt = 0;

}

/******************************************************************************/
/*!
\brief
Draw Special Box

\param pSB
The pointer of Special Box

\param data
Get map data
*/
/******************************************************************************/
void DrawSB(const Block *pSB, const Play &data)
{
  WEGraphics::SetTextureCoords(1, 1, 0, 0, 0);
  WEMtx44 tranform;
  WEGraphics::SetTexture(data.TextureData.SBTexture);
  for (int i = 0; i < data.pObjMgr->GetSBCount(); ++i)
  {
    WEGraphics::SetTextureColor(pSB[i].red,
      pSB[i].green,
      pSB[i].blue,
      pSB[i].alpha);
    WEMtx44::MakeTransform(tranform,
      pSB[i].scale.x,
      pSB[i].scale.y,
      pSB[i].rotation,
      pSB[i].pos.x,
      pSB[i].pos.y,
      0);
    
    WEGraphics::Draw(tranform);
  }
}