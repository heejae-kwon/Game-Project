/******************************************************************************/
/*!
\file   WERandom.h
\author Matt Casanova
\par    email: mcasanov\@digipen.edu
\par    GAM150
\par    Simple 2D Game Engine
\date   2012/11/26

Prototypes for my random functions

*/
/******************************************************************************/
#ifndef WE_RANDOM_H
#define WE_RANDOM_H

namespace WERandom
{
/*Seeds the random number generator*/
void  Seed(unsigned seed);
/*Gets a new random int*/
int   GetInt(void);
/*Gets a new random int between min and max*/
int   GetInt(int min, int max);
/*Gets a new random float between 0 and 1*/
float GetFloat(void);
/*Gets a new random float between min and max*/
float GetFloat(float min, float max);
}//end namespace WERandom




#endif
