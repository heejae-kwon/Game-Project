/******************************************************************************/
/*!
\file   Developer.cpp
\title  Neon sign
\author HeeJae Kwon
\par    GAM150
\brief  The file that includes developer's functions

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#include "Developer.h"
/******************************************************************************/
/*!
\brief
Cheat code that control the game play level.

\param data
Get map data
*/
/******************************************************************************/
void DMIncreaseLevel(Play &data)
{
	if (WEInput::IsTriggered(WE_I) && WEInput::IsPressed(WE_SHIFT))
  {
    ++data.LevelControl;
    data.FmodData.result = data.FmodData.sound->release();
    WEStateManager::Restart();
  }
}
/******************************************************************************/
/*!
\brief
Cheat code that control the game play level.

\param data
Get map data
*/
/******************************************************************************/
void DMDecreaseLevel(Play &data)
{
	if (WEInput::IsTriggered(WE_U) && WEInput::IsPressed(WE_SHIFT))
  {
    --data.LevelControl;
    data.FmodData.result = data.FmodData.sound->release();
    WEStateManager::Restart();
  }
}

/******************************************************************************/
/*!
\brief
Cheat code that restart the level.

\param data
Get map data
*/
/******************************************************************************/
void DMRestart(Play &data)
{
  //ResetButton
	if (WEInput::IsTriggered(WE_O) && WEInput::IsPressed(WE_SHIFT))
  {
    data.FmodData.result = data.FmodData.sound->release();
    WEStateManager::Restart();
  }
}

/******************************************************************************/
/*!
\brief Update Wall's Input
*/
/******************************************************************************/
void DMWall(Block *pWalls, Play &data)
{
  //UpdateWallMovement

  //Rotating the ball
  if (WEInput::IsTriggered(WE_MOUSE_MIDDLE_UP) && WEInput::IsPressed(WE_P))
  {
    
    WEVec2 click;
    WEInput::GetMouse(click);
    WEGraphics::ConvertScreenToWorld(click.x, click.y);

    for (int i = 0; i < data.pObjMgr->GetWallCount(); ++i)
    {
      if (WEIntersection::PointRect(click, pWalls[i].pos,
        pWalls[i].scale.x, pWalls[i].scale.y)
        && data.ConditionData.ballCondition == Stoping && data.ConditionData.RwallModCondition == CanModRotate)
      {
        pWalls[i].Rotateclicked = true;
      }
      if (pWalls[i].Rotateclicked == true)
      {
        data.ConditionData.RwallModCondition = CannotModRotate;
        pWalls[i].rotation += WEMath::DegreeToRadian(15);

        for (int k = 0; k < REC_POINT_COUNT; ++k)
        {
          pWalls[i].point[k] -= pWalls[i].pos;
        }

        WEVec2 RotatedCoordinate[REC_POINT_COUNT];

        //Rotating points in zero
        RotatedCoordinate[0] = My_RotateVec2(pWalls[i].rotation, pWalls[i].scale.x * 0.5f, pWalls[i].scale.y * 0.5f);
        RotatedCoordinate[1] = My_RotateVec2(pWalls[i].rotation, pWalls[i].scale.x * 0.5f, -pWalls[i].scale.y * 0.5f);
        RotatedCoordinate[2] = My_RotateVec2(pWalls[i].rotation, -pWalls[i].scale.x * 0.5f, -pWalls[i].scale.y * 0.5f);
        RotatedCoordinate[3] = My_RotateVec2(pWalls[i].rotation, -pWalls[i].scale.x * 0.5f, pWalls[i].scale.y * 0.5f);

        My_SetPoints_And_Lines(RotatedCoordinate, pWalls[i].pos, pWalls[i].point, pWalls[i].line);

        WEDEBUG_PRINT("%f\n", pWalls[i].rotation);
      }
    }//for
  }//WE_MOUSE_MIDDLE_UP
  else if (WEInput::IsTriggered(WE_MOUSE_MIDDLE_DOWN) && WEInput::IsPressed(WE_P))
  {
    WEVec2 click;
    WEInput::GetMouse(click);
    WEGraphics::ConvertScreenToWorld(click.x, click.y);

    for (int i = 0; i < data.pObjMgr->GetWallCount(); ++i)
    {

      if (WEIntersection::PointRect(click, pWalls[i].pos,
        pWalls[i].scale.x, pWalls[i].scale.y)
        && data.ConditionData.ballCondition == Stoping && data.ConditionData.RwallModCondition == CanModRotate)
      {
        pWalls[i].Rotateclicked = true;
      }
      if (pWalls[i].Rotateclicked == true)
      {
        data.ConditionData.RwallModCondition = CannotModRotate;

        pWalls[i].rotation -= WEMath::DegreeToRadian(15);

        for (int k = 0; k < REC_POINT_COUNT; ++k)
        {
          pWalls[i].point[k] -= pWalls[i].pos;
        }

        WEVec2 RotatedCoordinate[REC_POINT_COUNT];

        //Rotating points in zero
        RotatedCoordinate[0] = My_RotateVec2(pWalls[i].rotation, pWalls[i].scale.x * 0.5f, pWalls[i].scale.y * 0.5f);

        RotatedCoordinate[1] = My_RotateVec2(pWalls[i].rotation, pWalls[i].scale.x * 0.5f, -pWalls[i].scale.y * 0.5f);
        RotatedCoordinate[2] = My_RotateVec2(pWalls[i].rotation, -pWalls[i].scale.x * 0.5f, -pWalls[i].scale.y * 0.5f);
        RotatedCoordinate[3] = My_RotateVec2(pWalls[i].rotation, -pWalls[i].scale.x * 0.5f, pWalls[i].scale.y * 0.5f);

        My_SetPoints_And_Lines(RotatedCoordinate, pWalls[i].pos, pWalls[i].point, pWalls[i].line);

        WEDEBUG_PRINT("%f\n", WEMath::RadianToDegree(pWalls[i].rotation));
      }
    }//for
  } //WEInput::IsTriggered(WE_MOUSE_MIDDLE_DOWN)
  //Drag the Wall
  else if (WEInput::IsPressed(WE_MOUSE_LEFT) && WEInput::IsPressed(WE_P))
  {
    WEVec2 click;
    WEInput::GetMouse(click);

    WEGraphics::ConvertScreenToWorld(click.x, click.y);


    for (int i = 0; i < data.pObjMgr->GetWallCount(); ++i)
    {
      if (WEIntersection::PointRect(click, pWalls[i].pos,
        pWalls[i].scale.x, pWalls[i].scale.y)
        && data.ConditionData.ballCondition == Stoping && data.ConditionData.wallModCondition == CanMod)
      {
        pWalls[i].clicked = true;
      }

      if (pWalls[i].clicked == true)
      {
        //Disturb the other ball's movement
        data.ConditionData.wallModCondition = CannotMod;

        pWalls[i].pos = click;

        //Move to zero cooridinate

        WEVec2 RotatedCoordinate[REC_POINT_COUNT];

        //Rotating points in zero
        RotatedCoordinate[0] = My_RotateVec2(pWalls[i].rotation, pWalls[i].scale.x * 0.5f, pWalls[i].scale.y * 0.5f);
        RotatedCoordinate[1] = My_RotateVec2(pWalls[i].rotation, pWalls[i].scale.x * 0.5f, -pWalls[i].scale.y * 0.5f);
        RotatedCoordinate[2] = My_RotateVec2(pWalls[i].rotation, -pWalls[i].scale.x * 0.5f, -pWalls[i].scale.y * 0.5f);
        RotatedCoordinate[3] = My_RotateVec2(pWalls[i].rotation, -pWalls[i].scale.x * 0.5f, pWalls[i].scale.y * 0.5f);

        My_SetPoints_And_Lines(RotatedCoordinate, pWalls[i].pos, pWalls[i].point, pWalls[i].line);
      }
    } //for loop
  }//WEInput::IsPressed(WE_MOUSE_LEFT)
  else
  {
    for (int i = 0; i < data.pObjMgr->GetWallCount(); ++i)
    {
      pWalls[i].clicked = false;
      pWalls[i].Rotateclicked = false;
      data.ConditionData.RwallModCondition = CanModRotate;
      data.ConditionData.wallModCondition = CanMod;
    }
  }//Defalut

  

} //UpdateWallInput


//DEVELOPER MODE
/******************************************************************************/
/*!
\brief
Cheat code that allow move balls position with mouse.

\param pBalls
The pointer of balls

\param data
Get map data
*/
/******************************************************************************/
void DMBall(Ball *pBalls, Play &data)
{
  //BALL DEVELOPE MODE (Drag)
  if (WEInput::IsPressed(WE_MOUSE_LEFT) && WEInput::IsPressed(WE_P))
  {
    WEVec2 click;

    WEInput::GetMouse(click);
    WEGraphics::ConvertScreenToWorld(click.x, click.y);

    for (int i = 0; i < data.pObjMgr->GetBallCount(); ++i)
    {
      if (WEIntersection::PointCircle(click, pBalls[i].pos,
        pBalls[i].radius) && data.ConditionData.ballModCondition == CanMod)
      {
        pBalls[i].clicked = true;
      }

      if (pBalls[i].clicked == true)
      {

        //Disturb the other ball's movement
        data.ConditionData.ballModCondition = CannotMod;

        pBalls[i].pos = click;

      }
    }
  } //WEInput::IsPressed(WE_MOUSE_LEFT) && WEInput::IsPressed(WE_P)
  else
  {
    for (int i = 0; i < data.pObjMgr->GetBallCount(); ++i)
    {
      pBalls[i].clicked = false;
      data.ConditionData.ballModCondition = CanMod;
    }
  } // default


}

/******************************************************************************/
/*!
\brief
Cheat code that allow move goal position with mouse.

\param pGoals
The pointer of goal

\param data
Get map data
*/
/******************************************************************************/
void DMGoal(Object *pGoals, Play &data)
{
  //GOAL DEVELOPE MODE (Drag)
  if (WEInput::IsPressed(WE_MOUSE_LEFT) && WEInput::IsPressed(WE_P))
  {
    WEVec2 click;

    WEInput::GetMouse(click);
    WEGraphics::ConvertScreenToWorld(click.x, click.y);

    for (int i = 0; i < data.pObjMgr->GetGoalCount(); ++i)
    {
      if (WEIntersection::PointCircle(click, pGoals[i].pos,
        pGoals[i].radius) && data.ConditionData.goalModCondition == CanMod)
      {
        pGoals[i].clicked = true;
      }

      if (pGoals[i].clicked == true)
      {

        //Disturb the other ball's movement
        data.ConditionData.goalModCondition = CannotMod;

        pGoals[i].pos = click;
      }
    }
  } //WEInput::IsPressed(WE_MOUSE_LEFT) && WEInput::IsPressed(WE_P)
  else
  {
    for (int i = 0; i < data.pObjMgr->GetGoalCount(); ++i)
    {
      pGoals[i].clicked = false;
      data.ConditionData.goalModCondition = CanMod;
    }
  } // default
}

/******************************************************************************/
/*!
\brief
Cheat code that allow move SB position with mouse.

\param pGoals
The pointer of SB

\param data
Get map data
*/
/******************************************************************************/
void DMSB(Block *pSB, Play &data)
{
  //UpdateWallMovement

  //Rotating the ball
  if (WEInput::IsTriggered(WE_MOUSE_MIDDLE_UP) && WEInput::IsPressed(WE_P))
  {

    WEVec2 click;
    WEInput::GetMouse(click);
    WEGraphics::ConvertScreenToWorld(click.x, click.y);

    for (int i = 0; i < data.pObjMgr->GetSBCount(); ++i)
    {
      if (WEIntersection::PointRect(click, pSB[i].pos,
        pSB[i].scale.x, pSB[i].scale.y)
        && data.ConditionData.ballCondition == Stoping && data.ConditionData.RSBModCondition == CanModRotate)
      {
        pSB[i].Rotateclicked = true;
      }
      if (pSB[i].Rotateclicked == true)
      {
        data.ConditionData.RSBModCondition = CannotModRotate;
        pSB[i].rotation += WEMath::DegreeToRadian(15);
      }
    }//for
  }//WE_MOUSE_MIDDLE_UP
  else if (WEInput::IsTriggered(WE_MOUSE_MIDDLE_DOWN) && WEInput::IsPressed(WE_P))
  {
    WEVec2 click;
    WEInput::GetMouse(click);
    WEGraphics::ConvertScreenToWorld(click.x, click.y);

    for (int i = 0; i < data.pObjMgr->GetSBCount(); ++i)
    {
      if (WEIntersection::PointRect(click, pSB[i].pos,
        pSB[i].scale.x, pSB[i].scale.y)
        && data.ConditionData.ballCondition == Stoping && data.ConditionData.RSBModCondition == CanModRotate)
      {
        pSB[i].Rotateclicked = true;
      }
      if (pSB[i].Rotateclicked == true)
      {
        data.ConditionData.RSBModCondition = CannotModRotate;
        pSB[i].rotation -= WEMath::DegreeToRadian(15);
      }
    }//for
  } //WEInput::IsTriggered(WE_MOUSE_MIDDLE_DOWN)
  //Drag the Wall
  else if (WEInput::IsPressed(WE_MOUSE_LEFT) && WEInput::IsPressed(WE_P))
  {
    WEVec2 click;
    WEInput::GetMouse(click);

    WEGraphics::ConvertScreenToWorld(click.x, click.y);

    for (int i = 0; i < data.pObjMgr->GetSBCount(); ++i)
    {

      if (WEIntersection::PointRect(click, pSB[i].pos,
        pSB[i].scale.x, pSB[i].scale.y)
        && data.ConditionData.ballCondition == Stoping && data.ConditionData.SBModCondition == CanMod)
      {
        pSB[i].clicked = true;
      }

      if (pSB[i].clicked == true)
      {
        //Disturb the other ball's movement
        data.ConditionData.SBModCondition = CannotMod;

        pSB[i].pos = click;
      }
    } //for loop
  }//WEInput::IsPressed(WE_MOUSE_LEFT)
  else
  {
    for (int i = 0; i < data.pObjMgr->GetSBCount(); ++i)
    {
      pSB[i].clicked = false;
      pSB[i].Rotateclicked = false;
      data.ConditionData.RSBModCondition = CanModRotate;
      data.ConditionData.SBModCondition = CanMod;
    }
  }//Defalut

  

}