/******************************************************************************/
/*!
\file   TeamLogo.h
\title  Neon sign
\author Junhyung Kim
\par    GAM150
\brief  This is the header file for team logo state.

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#ifndef TEAMLOGO_H
#define TEAMLOGO_H


void LogoStateLoad(void);
void LogoStateInit(void);
void LogoStateUpdate(float dt);
void LogoStateShutdown(void);
void LogoStateUnload(void);


#endif /* TEAMLOGO_H */