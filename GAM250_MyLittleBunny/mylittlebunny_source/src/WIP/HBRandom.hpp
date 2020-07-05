/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:		HBRandom.hpp
Purpose:			The class that contains all math functions.	
Language:		C++
Project:			GAM250
Author:			Name : HeeJae Kwon
Email:				sfhy33@gmail.com
Creation date:	2017.06.16
----------------------------------------------------------------------------*/
#ifndef HB_RANDOM_H
#define HB_RANDOM_H

namespace BE
{
	class __declspec(dllexport) HBRandom {
		public:
		/*Seeds the specific random number generator*/
		static void  Seed(unsigned seed);
		/*Seeds the random number generator*/
		static void  Seed(void);
		/*Gets a new random int*/
		static const int   GetInt(void);
		/*Gets a new random int between min and max*/
		static const int   GetInt(int min, int max);
		/*Gets a new random float between 0 and 1*/
		static const float GetFloat(void);
		/*Gets a new random float between min and max*/
		static const float GetFloat(float min, float max);
	};
}//end namespace HBRandom




#endif