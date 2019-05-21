/******************************************************************************/
/*!
\file   Ending.h
\title  Neon sign
\author Junhyung Kim
\par    GAM150
\brief  This is the header file for the ending state.

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#ifndef ENDING_H
#define ENDING_H


void EndingStateLoad(void);
void EndingStateInit(void);
void EndingStateUpdate(float dt);
void EndingStateShutdown(void);
void EndingStateUnload(void);


#endif /* ENDING_H */