/******************************************************************************/
/*!
\file   Ball.h
\title  Neon sign
\author Kim gue sik
\par    GAM150
\brief
Header file for Ball.cpp, to connect with Data.h

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#ifndef BALL_H
#define BALL_H

#include "Data.h"
#include "MyHelper.h"


void BallMovement(Ball *pBalls, int ballID, float dt);
void CreateBall(Play &data);
void DrawBall(const Ball *pBalls, const Play &data);
void DrawDirectionLimit(const Ball *pBalls, const Play &data);
void BallDirection(Ball *pBalls, Object *pButtons, Play &data);
void ResetBallPosition(Ball *pBalls, Object *pButtons, Object *pArrow, Play &data);
#endif //SHOTBALL_H
