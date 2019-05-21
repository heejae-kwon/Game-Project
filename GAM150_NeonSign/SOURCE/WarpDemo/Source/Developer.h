/******************************************************************************/
/*!
\file   Developer.h
\title  Neon sign
\author HeeJae Kwon
\par    GAM150
\brief  The file that includes developer's functions

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#ifndef DEVELOPER_H
#define DEVELOPER_H

#include "Data.h"
#include "MyHelper.h"

void DMIncreaseLevel(Play &data);
void DMDecreaseLevel(Play &data);

void DMRestart(Play &data);
void DMBall(Ball *pBalls, Play &data);
void DMGoal(Object *pGoals, Play &data);
void DMWall(Block *pWalls, Play &data);
void DMSB(Block *pSB, Play &data);
#endif
