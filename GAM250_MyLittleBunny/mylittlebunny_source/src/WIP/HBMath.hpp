/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:		HBMath.hpp
Purpose:			The class that contains all math functions.	
Language:		C++
Project:			GAM250
Author:			Name : HeeJae Kwon
Email:				sfhy33@gmail.com
Creation date:	2017.06.16
----------------------------------------------------------------------------*/
#pragma once

namespace BE
{
    class __declspec(dllexport) HBMath
    {
		public:
        /*!The smallest value between two floats*/
        static const float EPSILON;
        /*!The value of PI*/
        static const float PI;
        /*!The Value of PI/2*/
        static const float HALF_PI;
        /*!The value of 2PI*/
        static const float TWO_PI;
        /*Converts an angle in Radians to Degress*/
        static float RadianToDegree(float radians);
        /*Converts an angle in Degrees to Radians*/
        static float DegreeToRadian(float degrees);
        /*Keeps a value between a low and a high range*/
        static float Clamp(float x, float low, float high);
        /*If x is below the low value it will return the high value
        if x is higher than the high value, it will return the low value*/
        static float Wrap(float x, float low, float high);
        /*Returnts the Minimume of two floats*/
        static float Min(float x, float y);
        /*Returns the maximume of two floats*/
        static float Max(float x, float y);
		/*Returns the PythagoreanSolve*/
		static float PythagoreanSolve(float x, float y);
        /*Linearly interpololates between start and end*/
        static float Lerp(float start, float end, float time);
        /*Checks if a value is between a low and high*/
        static bool  IsInRange(float x, float low, float high);
        /*Test is two floats are equal*/
        static bool  IsFloatEqual(float x, float y);
        /*Checks if an int is a power of 2*/
        static bool  IsPowerOf2(int x);
        /*Given a value, this returns the next power of two*/
        static int   GetNextPowerOf2(int x);
        /*Linearly interpolates between start and end*/
        int   Lerp(int start, int end, float time);
        /*Linearly interpolates between start and end*/
        char  Lerp(char start, char end, float time);
	};//end namespace HBMath
}
