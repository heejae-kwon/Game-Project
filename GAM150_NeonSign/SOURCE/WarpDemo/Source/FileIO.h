/******************************************************************************/
/*!
\file   FileIO.h
\title  Neon sign
\author HeeJae Kwon
\par    GAM150
\brief  The header file that includes FileIO functions

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#ifndef FILEIO_H
#define FILEIO_H

#include "Data.h"
void WriteBallInfo(const char* fileName, const Play &data);
void WriteGoalInfo(const char* fileName, const Play &data);
void WriteWallInfo(const char* fileName, const Play &data);
void WriteSBInfo(const char* fileName, const Play &data);
void WriteLevelControl(const char* fileName, const Play &data);

void ReadBallInfo(const char* fileName, Play &data);
void ReadBlockInfo(const char* fileName, Play &data);
void ReadGoalInfo(const char* fileName, Play &data);
void ReadWallInfo(const char* fileName, Play &data);
void ReadButtonInfo(const char* fileName, Play &data);
void ReadSBInfo(const char* fileName, Play &data);
void ReadLevelControl(const char* fileName, Play &data);

void SaveLevelInfo(Play &data);
void LoadLevelInfo(Play &data);



#endif
