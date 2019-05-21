/******************************************************************************/
/*!
\file   LevelSelect.h
\title  Neon sign
\author Junhyung Kim
\par    GAM150
\brief  This is the interface file for the level select state.

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#ifndef LEVELSELECT_H
#define LEVELSELECT_H

#include "Music.h"

void LevelSelectStateLoad(void);
void LevelSelectStateInit(void);
void LevelSelectStateUpdate(float dt);
void LevelSelectStateShutdown(void);
void LevelSelectStateUnload(void);


#endif /* DIGIPENLOGO_H */