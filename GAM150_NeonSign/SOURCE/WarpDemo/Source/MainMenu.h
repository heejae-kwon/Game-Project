/******************************************************************************/
/*!
\file   MainMenu.h
\title  Neon sign
\author Junhyung Kim
\par    GAM150
\brief  This is the header file for the main menu state.

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#ifndef MAINMENU_H
#define MAINMENU_H

#include "Music.h"

void MainMenuStateLoad(void);
void MainMenuStateInit(void);
void MainMenuStateUpdate(float dt);
void ManiMenuStateShutdown(void);
void MainMenuStateUnload(void);


#endif /* MAINMENU_H */