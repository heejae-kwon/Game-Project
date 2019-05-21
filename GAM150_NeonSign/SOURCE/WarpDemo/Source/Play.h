/******************************************************************************/
/*!
\file   Play.h
\title  Neon sign
\author HeeJae Kwon
\par    GAM150
\brief  The header file that includes Play state's functions

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#ifndef PLAY_H
#define PLAY_H

#include "Ball.h"
#include "Block.h"
#include "Arrow.h"
#include "Goal.h"
#include "Button.h"
#include "Reflection.h"
#include "FileIO.h"
#include "Developer.h"
#include "Wall.h"
#include "Music.h"
#include "SB.h"
#include "InGameMenu.h"
#include "Building.h"

  void Play_Load(void);
  void Play_Init(void);
  void Play_Update(float dt);
  void Play_Shutdown(void);
  void Play_Unload(void);

#endif //SHOTBALL_H
