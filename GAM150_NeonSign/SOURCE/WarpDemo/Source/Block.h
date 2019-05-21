/******************************************************************************/
/*!
\file   Block.h
\title  Neon sign
\author Kim gue sik
\par    GAM150
\brief
Header file for Block.cpp, to connect with Data.h

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#ifndef BLOCK_H
#define BLOCK_H

#include "Data.h"
#include "MyHelper.h"

void CreateBlock(Play &data, int count);
void DeleteBlock(Block *pBlocks, Play &data);
void DrawBlock(const Block *pBlocks, const Play &data);
void UpdateBlockInput(Block *pBlocks, Play &data);

#endif
