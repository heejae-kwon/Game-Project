/******************************************************************************/
/*!
\file   Music.cpp
\title  Neon sign
\author Junhyung Kim
\par    GAM150
\brief  This is the interface file for playing music.

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#include "Music.h"

void MusicInit(FmodData &Fmod)
{
  ///////////////////////////////////////////////////////////////////////////////////////////Test
  Common_Init(&Fmod.extradriverdata);

  Fmod.result = FMOD::System_Create(&Fmod.system);
  ERRCHECK(Fmod.result);

  Fmod.result = Fmod.system->getVersion(&Fmod.version);
  ERRCHECK(Fmod.result);

  if (Fmod.version < FMOD_VERSION)
  {
    Common_Fatal("FMOD lib version %08x doesn't match header version %08x", Fmod.version, FMOD_VERSION);
  }

   Fmod.result = Fmod.system->init(32, FMOD_INIT_NORMAL, Fmod.extradriverdata);
  ERRCHECK(Fmod.result);

  Fmod.result = Fmod.system->createSound(Common_MediaPath("Reflection.ogg"), FMOD_DEFAULT, 0, &Fmod.sound1);
  ERRCHECK(Fmod.result);

  Fmod.result = Fmod.sound1->setMode(FMOD_LOOP_OFF);
  ERRCHECK(Fmod.result);

  Fmod.result = Fmod.system->createSound(Common_MediaPath("Clear2.ogg"), FMOD_DEFAULT, 0, &Fmod.sound2);
  ERRCHECK(Fmod.result);

  Fmod.result = Fmod.sound2->setMode(FMOD_LOOP_OFF);
  ERRCHECK(Fmod.result);


  Fmod.result = Fmod.system->createSound(Common_MediaPath("BGM.ogg"), FMOD_DEFAULT, 0, &Fmod.sound3);
  ERRCHECK(Fmod.result);

  Fmod.result = Fmod.system->createSound(Common_MediaPath("SpecialBox.ogg"), FMOD_DEFAULT, 0, &Fmod.sound4);
  ERRCHECK(Fmod.result);

  Fmod.result = Fmod.sound3->setMode(FMOD_LOOP_NORMAL);
  ERRCHECK(Fmod.result);
}
