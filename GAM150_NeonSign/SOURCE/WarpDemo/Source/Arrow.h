/******************************************************************************/
/*!
\file   Arrow.h
\title  Neon sign
\author Kim gue sik
\par    GAM150
\brief
Header file for Arrow.cpp, to connect with Data.h

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#ifndef ARROW_H
#define ARROW_H

#include "Data.h"
#include "MyHelper.h"

void CreateArrow(Play &data);
void UpdateArrow(Ball *pBalls, Object *pArrow, Object *pButtons, Play &data);
void DrawArrow(const Object *pArrow, const Play &data);

#endif //SHOTBALL_H
