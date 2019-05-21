/******************************************************************************/
/*!
\file   SB.h
\title  Neon sign
\author Kim gue sik, HeeJae Kwon
\par    GAM150
\brief
Header file for SB.cpp, to connect with Data.h

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#ifndef SB_H
#define SB_H

#include "Data.h"
#include "Ball.h"//!< to get ball vel

void CreateSB(Play &data);
void UpdateSB(Ball *pBalls, Block *pSB, float dt, Play &data);
void DrawSB(const Block *pSB, const Play &data);

#endif //SHOTBALL_H
