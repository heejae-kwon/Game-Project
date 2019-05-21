/******************************************************************************/
/*!
\file   Button.h
\title  Neon sign
\author HeeJae Kwon
\par    GAM150
\brief  The header file that include button's functions

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#ifndef BUTTON_H
#define BUTTON_H

#include "Data.h"

void CreateButton(Play &data);
void UpdateButton(Object *pButtons, Play &data);
void InGameMenuButtonUpdate(Object *pButtons, Play &data);
void DrawButton(const Object *pButtons, const Play &data);
void DrawNumbers(const Play &data);
#endif //SHOTBALL_H
