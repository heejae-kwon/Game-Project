/******************************************************************************/
/*!
\file   SplashState.h
\author Matt Casanova
\par    email: mcasanov\@digipen.edu
\par    class:
\par    Assignment:
\date   2012/12/6

This is a state for the WarpEngine Demo project. A Splash state is a good
place to load data and/or resources that you will need for all of your states.
*/
/******************************************************************************/
#ifndef STORY_H
#define STORY_H

#include "Music.h"

void StoryStateLoad(void);
void StoryStateInit(void);
void StoryStateUpdate(float dt);
void StoryStateShutdown(void);
void StoryStateUnload(void);


#endif /* STORY_H */