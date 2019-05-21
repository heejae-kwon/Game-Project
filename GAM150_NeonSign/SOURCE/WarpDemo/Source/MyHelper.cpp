/******************************************************************************/
/*!
\file   MyHelper.cpp
\title  Neon sign
\author HeeJae Kwon
\par    GAM150
\brief  The file that includes MyHelper's functions

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#include "MyHelper.h"

/******************************************************************************/
/*!
\brief 
Calculate the rotating vector

\param rotation
The angle that how much vector will be rotated

\param coordinateX

\param coordinateY
*/
/******************************************************************************/
WEVec2 My_RotateVec2(const float rotation, const float coordinateX, const float coordinateY)
{
  WEVec2 Vec2;


  Vec2.x = cos(rotation)*(coordinateX)-sin(rotation)*(coordinateY);
  Vec2.y = sin(rotation)*(coordinateX)+cos(rotation)*(coordinateY);

  return Vec2;
}//My_RotateVec2

/******************************************************************************/
/*!
\brief Helper function for setting the rectangle's points and line

\param RotatedCoordinate

\param pos

\param point

\param line
*/
/******************************************************************************/
void My_SetPoints_And_Lines(const WEVec2 RotatedCoordinate[], const WEVec2 pos, WEVec2 point[], WEVec2 line[])
{
  for (int i = 0; i < REC_POINT_COUNT; ++i)
  {
    point[i] = pos + RotatedCoordinate[i];
  }

  //Get Line vectors
  line[0] = point[0] - point[1];
  line[1] = point[1] - point[2];
  line[2] = point[2] - point[3];
  line[3] = point[3] - point[0];
} // My_SetPoints_And_Lines

/******************************************************************************/
/*!
\brief 
Convert cos value to specific angle

\param Cos
*/
/******************************************************************************/
float My_Degreefloat(float Cos)
{
  float result;

  result = acos(Cos) * 180.0f / WEMath::PI;

  return result;
}// My_Degreefloat