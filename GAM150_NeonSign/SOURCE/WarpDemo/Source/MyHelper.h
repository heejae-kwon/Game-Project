/******************************************************************************/
/*!
\file   MyHelper.h
\title  Neon sign
\author HeeJae Kwon
\par    GAM150
\brief  The header file that includes MyHelper's functions

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#ifndef MYHELPER_H
#define MYHELPER_H

#include "Data.h"

WEVec2 My_RotateVec2(const float rotation, const float coordinateX, const float coordinateY);
void My_SetPoints_And_Lines(const WEVec2 RotatedCoordinate[], const WEVec2 pos, WEVec2 point[], WEVec2 line[]);
float My_Degreefloat(float Cos);

#endif //SHOTBALL_H
