/******************************************************************************/
/*!
\file   play_stream.cpp
\title  Neon sign
\author Junhyung Kim
\par    GAM150
\brief  This file includes fmod functions

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#include "fmod.hpp"
#include "common.h"

int FMOD_Main()
{
  FMOD::System     *system;
  FMOD::Sound      *sound1, *sound2, *sound3;
  FMOD::Channel    *channel = 0;
  FMOD_RESULT       result;
  unsigned int      version;
  void             *extradriverdata = 0;

  Common_Init(&extradriverdata);

  /*
  Create a System object and initialize
  */
  result = FMOD::System_Create(&system);
  ERRCHECK(result);

  result = system->getVersion(&version);
  ERRCHECK(result);

  if (version < FMOD_VERSION)
  {
    Common_Fatal("FMOD lib version %08x doesn't match header version %08x", version, FMOD_VERSION);
  }

  result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
  ERRCHECK(result);

	result = system->createSound(Common_MediaPath("Reflection.ogg"), FMOD_DEFAULT, 0, &sound1);
  ERRCHECK(result);

  result = sound1->setMode(FMOD_LOOP_OFF);   
  ERRCHECK(result);                           

	result = system->createSound(Common_MediaPath("Clear2.ogg"), FMOD_DEFAULT, 0, &sound2);
  ERRCHECK(result);

	result = system->createSound(Common_MediaPath("BGM.ogg"), FMOD_DEFAULT, 0, &sound3);
  ERRCHECK(result);

  /*
  Main loop
  */
  do
  {
    Common_Update();

    if (Common_BtnPress(BTN_ACTION1))
    {
      result = system->playSound(sound1, 0, false, &channel);
      ERRCHECK(result);
    }

    if (Common_BtnPress(BTN_ACTION2))
    {
      result = system->playSound(sound2, 0, false, &channel);
      ERRCHECK(result);
    }

    if (Common_BtnPress(BTN_ACTION3))
    {
      result = system->playSound(sound3, 0, false, &channel);
      ERRCHECK(result);
    }

    result = system->update();
    ERRCHECK(result);

    {
      unsigned int ms = 0;
      unsigned int lenms = 0;
      bool         playing = 0;
      bool         paused = 0;
      int          channelsplaying = 0;

      if (channel)
      {
        FMOD::Sound *currentsound = 0;

        result = channel->isPlaying(&playing);
        if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
        {
          ERRCHECK(result);
        }

        result = channel->getPaused(&paused);
        if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
        {
          ERRCHECK(result);
        }

        result = channel->getPosition(&ms, FMOD_TIMEUNIT_MS);
        if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
        {
          ERRCHECK(result);
        }

        channel->getCurrentSound(&currentsound);
        if (currentsound)
        {
          result = currentsound->getLength(&lenms, FMOD_TIMEUNIT_MS);
          if ((result != FMOD_OK) && (result != FMOD_ERR_INVALID_HANDLE) && (result != FMOD_ERR_CHANNEL_STOLEN))
          {
            ERRCHECK(result);
          }
        }
      }

      system->getChannelsPlaying(&channelsplaying);
    }

    Common_Sleep(50);
  } while (!Common_BtnPress(BTN_QUIT));

  /*
  Shut down
  */
  result = sound1->release();
  ERRCHECK(result);
  result = sound2->release();
  ERRCHECK(result);
  result = sound3->release();
  ERRCHECK(result);
  result = system->close();
  ERRCHECK(result);
  result = system->release();
  ERRCHECK(result);

  Common_Close();

  return 0;
}
