/******************************************************************************/
/*!
\file   FmodData.h
\title  Neon sign
\author Junhyung Kim
\par    GAM150
\brief  This file includes fmod functions

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#ifndef FMODDATA_H
#define FMODDATA_H

#include "fmod.hpp"
#include "common.h"

struct FmodData
{
  FMOD::System     *system;
  FMOD::Sound      *sound1, *sound2, *sound3, *sound4, *sound, *sound_to_play;
  FMOD::Channel    *channel = 0;
  FMOD_RESULT       result;
  unsigned int      version;
  void             *extradriverdata = 0;
  int               numsubsounds;
};


#endif /* FMODDATA_H */