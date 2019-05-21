/******************************************************************************/
/*!
\file   Goal.h
\title  Neon sign
\author HeeJae Kwon
\par    GAM150
\brief  The header file that includes Goal's functions

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#ifndef GOAL_H
#define GOAL_H

#include "Data.h"
#include "Music.h"

void CreateGoal(Play &data);
void UpdateGoal(Ball *pBalls, Object *pGoals, Play &data, float dt);
void DrawGoal(const Object *pGoals, const Play &data);

#endif
