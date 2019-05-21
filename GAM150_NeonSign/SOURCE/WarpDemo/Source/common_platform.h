/******************************************************************************/
/*!
\file   common_platform.h
\title  Neon sign
\author Junhyung Kim
\par    GAM150
\brief  This file includes fmod functions

“All content © 2016 DigiPen (USA) Corporation, all rights reserved.”
*/
/******************************************************************************/
#ifndef FMOD_COMMON_PLATFORM_H
#define FMOD_COMMON_PLATFORM_H


#define Common_snprintf _snprintf
#define Common_vsnprintf _vsnprintf

#include <windows.h>

int FMOD_Main();

void Common_TTY(const char *format, ...);

typedef CRITICAL_SECTION Common_Mutex;

inline void Common_Mutex_Create(Common_Mutex *mutex)
{
    InitializeCriticalSection(mutex);
}

inline void Common_Mutex_Destroy(Common_Mutex *mutex)
{
    DeleteCriticalSection(mutex);
}

inline void Common_Mutex_Enter(Common_Mutex *mutex)
{
    EnterCriticalSection(mutex);
}

inline void Common_Mutex_Leave(Common_Mutex *mutex)
{
    LeaveCriticalSection(mutex);
}

#endif