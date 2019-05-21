/******************************************************************************/
/*!
\file   Reflection.h
\title  Neon sign
\author Kim gue sik
\par    GAM150
\brief
Header file for Reflection.cpp, to connect with Data.h

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#ifndef REFLECTION_H
#define REFLECTION_H

#include "Data.h"
#include "Ball.h"

void Reflection(Ball *pBalls, Block *pBlocks, float dt, Play &data);
void WallReflection(Ball *pBalls, Block *pBlocks, float dt, Play &data);

#endif //SHOTBALL_H
