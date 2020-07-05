/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:		HBMath.cpp
Purpose:			The functions that basic math helper.
Language:		C++
Project:			GAM250
Author:			Name : HeeJae Kwon
Email:				sfhy33@gmail.com
Creation date:	2017.06.16
----------------------------------------------------------------------------*/
#include "HBMath.hpp"
#include <iostream>

//!Basic math helper functions and values
    /******************************************************************************/
    /*!
    \brief
    Convert cos value to specific angle

    \param Cos
    */
    /******************************************************************************/
	/*!The smallest value between two floats*/
 const float BE::HBMath::EPSILON = 0.00001f;
/*!The value of PI*/
 const float BE::HBMath::PI = 3.1415926535897932384626433832795f;
/*!The Value of PI/2*/
 const float BE::HBMath::HALF_PI = (PI* .5f);
/*!The value of 2PI*/
 const float BE::HBMath::TWO_PI = (PI* 2.0f);
    /*Converts an angle in Radians to Degress*/
float
BE::HBMath::RadianToDegree(float radians)
{
    return (radians / HBMath::PI) * 180;
}
/*Converts an angle in Degrees to Radians*/
float
BE::HBMath::DegreeToRadian(float degrees)
{
    return (degrees / 180)* PI;
}

//Keeps a value between a low and a high range
float
BE::HBMath::Clamp(float x, float low, float high)
{
    if (x <= low)
    {
        x = low;
    }
    else if (x >= high)
    {
        x = high;
    }

    return x;
}

/*If x is below the low value it will return the high value
if x is higher than the high value, it will return the low value*/
float
BE::HBMath::Wrap(float x, float low, float high)
{
    if (x < low)
    {
        return high;
    }
    else if (x > high)
    {
        return low;
    }
    return x;
}

/*Returnts the Minimume of two floats*/
float
BE::HBMath::Min(float x, float y)
{
    if (x >= y)
    {
        return y;
    }
    return x;
}

/*Returns the maximume of two floats*/
float
BE::HBMath::Max(float x, float y)
{
    if (x >= y)
    {
        return x;
    }

    return y;
}

/*Returns the PythagoreanSolve*/
float BE::HBMath::PythagoreanSolve(float x, float y) {
	return std::sqrt(x*x + y*y);
}

/*Checks if a value is between a low and high*/
bool
BE::HBMath::IsInRange(float x, float low, float high)
{
    if (x <= high && x >= low)
    {
        return true;
    }

    return false;
}

/*Test is two floats are equal*/
bool 
BE::HBMath::IsFloatEqual(float x, float y)
{
    if (x - y <= EPSILON || x - y >= -EPSILON)
    {
        return true;
    }

    return false;
}

/*Checks if an int is a power of 2*/
bool
BE::HBMath::IsPowerOf2(int x)
{
    int i = 1;
    while (i < x)
    {
        i *= 2;
    }
    if (i == x)
    {
        return true;
    }

    return false;
}

/*Given a value, this returns the next power of two*/
int
BE::HBMath::GetNextPowerOf2(int x)
{
    int result = 1;
    while (result <= x)
    {
        result *= 2;
    }

    return result;
}

/*Linearly interpolates between start and end*/
int
BE::HBMath::Lerp(int start, int end, float time)
{
    start += static_cast<int>(time);

    if (start >= end)
    {
        start = end;
    }

    return start;
}

/*Linearly interpololates between start and end*/
float
BE::HBMath::Lerp(float start, float end, float time)
{
    start += time;

    if (start >= end)
    {
        start = end;
    }

    return start;
}

/*Linearly interpolates between start and end*/
char
BE::HBMath::Lerp(char start, char end, float time)
{
    start += static_cast<char>(time);

    if (start >= end)
    {
        start = end;
    }

    return start;
}
