/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:		HBVec2.cpp
Purpose:			A 2D vector for a 2D game, use a separate variable for Z-Order.
						Can be used C style with static functions or C++ with methods.
Language:		C++
Project:			GAM250
Author:			Name : HeeJae Kwon
Email:				sfhy33@gmail.com
Creation date:	2017.06.16
----------------------------------------------------------------------------*/
#include "HBVec2.hpp"
#include "HBMath.hpp"
#include <iostream>

namespace
{
    const float EPSILON = 0.00001f; //!< EPSILON number
}//end unnnamed

//Constructor
BE::HBVec2::HBVec2(const float a, const float b) : x(a), y(b)
{
}
//Copy Constructor
BE::HBVec2::HBVec2(const HBVec2& rhs) : x(rhs.x), y(rhs.y)
{
}
BE::HBVec2::HBVec2(const glm::vec2 & rhs)  : x(rhs.x), y(rhs.y)
{
}
BE::HBVec2::HBVec2(const glm::vec3 & rhs) : x(rhs.x), y(rhs.y)
{
}
//Destructor
BE::HBVec2::~HBVec2(void)
{

}
/******************************************************************************/
/*!
\brief
Calculate the rotating vector

\param radian
The angle that how much vector will be rotated

\param x

\param y
*/
/******************************************************************************/

//Operators
/*Adds two vectors*/
BE::HBVec2
BE::HBVec2::operator+(const HBVec2& rhs) const
{
    HBVec2 Vec2(x + rhs.x, y + rhs.y);
    return Vec2;
}
/*Subtracts two vectors*/
BE::HBVec2
BE::HBVec2::operator-(const HBVec2& rhs) const
{
    HBVec2 Vec2(x - rhs.x, y - rhs.y);
    return Vec2;
}
/*Negates a vector*/
BE::HBVec2
BE::HBVec2::operator-(void) const
{
    HBVec2 Vec2(-x, -y);
    return Vec2;
}
/*Scales a vector*/
BE::HBVec2
BE::HBVec2::operator*(const float scale) const
{
    HBVec2 Vec2;
    Vec2.x = x*scale;
    Vec2.y = y*scale;
    return Vec2;
}
/*Adds a vector to this vector*/
BE::HBVec2&
BE::HBVec2::operator+=(const HBVec2& rhs)
{
    x += rhs.x;
    y += rhs.y;

    return*this;
}
/*Subtracts a vector from this vector*/
BE::HBVec2&
BE::HBVec2::operator-=(const HBVec2& rhs)
{
    x -= rhs.x;
    y -= rhs.y;

    return*this;
}
/*Scales this vector*/
BE::HBVec2&
BE::HBVec2::operator*=(const float scale)
{
    x *= scale;
    y *= scale;

    return*this;
}

/*void BE::HBVec2::operator=(const HBVec2 & rhs)
{
	x = rhs.x;
	y = rhs.y;
}

void BE::HBVec2::operator=(const glm::vec2 & rhs)
{
	x = rhs.x;
	y = rhs.y;
}

void BE::HBVec2::operator=(const glm::vec3 & rhs)
{
	x = rhs.x;
	y = rhs.y;
}*/

/*Negates this vector*/
BE::HBVec2& BE::HBVec2::operator-(void)
{
	x = -x;
	y = -y;

	return*this;
}
/*Tests if two vectors are equal*/
bool
BE::HBVec2::operator==(const HBVec2& rhs) const
{
    if (((x >= rhs.x && x - rhs.x <= EPSILON) || (x <= rhs.x &&x - rhs.x >= -EPSILON)) &&
        ((y >= rhs.y && y - rhs.y <= EPSILON) || (y <= rhs.y &&y - rhs.y >= -EPSILON)))
        return true;

    return false;
}

/*Tests if two vectors are not equal*/
bool
BE::HBVec2::operator!=(const HBVec2& rhs) const
{
    if (*this == rhs)
        return false;

    return true;
}

//Member functions**********************************************************
BE::HBVec2&
BE::HBVec2::Rotate(const float radian)
{
    HBVec2 result;
    result.x = cos(radian)*(x)-sin(radian)*(y);
    result.y = sin(radian)*(x)+cos(radian)*(y);

    if (std::abs(result.x) < EPSILON)
        result.x = 0;
    if (std::abs(result.y) < EPSILON)
        result.y = 0;

    *this = result;

    return*this;
}//My_RotateVec

BE::HBVec2
BE::HBVec2::Project(const HBVec2& rhs) const
{
    return (Dot(rhs) / rhs.LengthSquared())* rhs;
}

BE::HBVec2
BE::HBVec2::ProjectPerp(const HBVec2& rhs) const
{
    return*this - Project(rhs);
}

void
BE::HBVec2::Zero(void)
{
    x = 0;
    y = 0;
}

/*Normalizes this vector*/
BE::HBVec2&
BE::HBVec2::Normalize(void)
{
    float length = Length();
	if (length != 0) {
    x = x / length;
    y = y / length;
	}
    return*this;
}
/*Allows user to quickly set x and y*/
void
BE::HBVec2::Set(const float xx, const float yy)
{
    x = xx;
    y = yy;
}
/*Performs the dot product on two vectors*/
float
BE::HBVec2::Dot(const HBVec2& rhs) const
{
    return  x*rhs.x + y*rhs.y;
}
int
BE::HBVec2::FindDegree(const HBVec2& rhs) const
{
    return static_cast<int>(HBMath::RadianToDegree(FindRadian(rhs)));
}
float
BE::HBVec2::FindRadian(const HBVec2& rhs) const
{
    float Cosin = Dot(rhs) / (Length()*rhs.Length());
    return std::acosf(Cosin);
}

/*Gets the Z component of the cross product of two vectors*/
float
BE::HBVec2::CrossZ(const HBVec2& rhs) const
{
    return (x* rhs.y) - (y* rhs.x);
}
/*Gets the length of the vector*/
float
BE::HBVec2::Length(void) const
{
    return std::sqrt(LengthSquared());
}
/*Gets the squared length of the vector*/
float
BE::HBVec2::LengthSquared(void) const
{
    return Dot(*this);
}
/*Treats the vector as a point and gets the distace to another pointer*/
float
BE::HBVec2::Distance(const HBVec2& point) const
{
    return std::sqrt(DistanceSquared(point));
}
/*Gets the squared distance between two points*/
float
BE::HBVec2::DistanceSquared(const HBVec2& point) const
{
    HBVec2 DS(*this - point);
    return DS.Dot(DS);
}
/*Checks if this is the zero vector*/
bool 
BE::HBVec2::IsZero(void) const
{
    if (x <= EPSILON && x >= -EPSILON &&
        y <= EPSILON && y >= -EPSILON)
        return true;

    return false;
}

//Non member functions*******************************************************
/*Allows user to quickly set x and y*/
void
BE::HBVec2::Rotate(HBVec2& result, const HBVec2& vec, const float radian)
{
    result.x = cosf(radian)*(vec.x) - sinf(radian)*(vec.y);
    result.y = sinf(radian)*(vec.x) + cosf(radian)*(vec.y);

}//My_RotateVec


void
BE::HBVec2::Set(HBVec2& result, const float x, const float y)
{
    result.Set(x, y);
}
/*Negates a vector*/
void
BE::HBVec2::Negate(HBVec2& result, const HBVec2& toNegate)
{
    result = -toNegate;
}
/*Adds two vectors together*/
void
BE::HBVec2::Add(HBVec2& result, const HBVec2& vec1, const HBVec2& vec2)
{
    result = vec1 + vec2;
}
/*Subtracts two vectors*/
void BE::HBVec2::Sub(HBVec2& result, const HBVec2& vec1, const HBVec2& vec2)
{
    result = vec1 - vec2;
}
/*Scales a vector*/
void BE::HBVec2::Scale(HBVec2& result, const HBVec2& toScale, const float scale)
{
    result = toScale* scale;
}
/*Normalizes a vector*/
void BE::HBVec2::Normalize(HBVec2& result, const HBVec2& toNormalize)
{
    const float length = toNormalize.Length();

    result.x = toNormalize.x / length;
    result.y = toNormalize.y / length;
}
/*Gets the projection vector of vec1 onto vec2*/
void BE::HBVec2::Project(HBVec2& result, const HBVec2& vec1, const HBVec2& vec2)
{
    result = vec1.Project(vec2);
}
/*Gets the perpendicular projection vector of vec1 onto vec2*/
void BE::HBVec2::PerpProject(HBVec2& result, const HBVec2& vec1, const HBVec2& vec2)
{
    result = vec1.ProjectPerp(vec2);
}
/*Linearly interpolates a vector based on time*/
void BE::HBVec2::Lerp(HBVec2& /*result*/, const HBVec2& /*vec1*/, const HBVec2& /*vec2*/,
    float /*time*/)
{

}
/*Gets the Z component of the cross product*/
float BE::HBVec2::CrossZ(const HBVec2& vec1, const HBVec2& vec2)
{
    return vec1.CrossZ(vec2);
}
/*Calculates the dot product of two vectors*/
float BE::HBVec2::Dot(const HBVec2& vec1, const HBVec2& vec2)
{
    return vec1.Dot(vec2);
}
int BE::HBVec2::FindDegree(const HBVec2& vec1, const HBVec2& vec2)
{
    return vec1.FindDegree(vec2);
}
/*Get the Length of a vector*/
float BE::HBVec2::Length(const HBVec2& vec)
{
    return vec.Length();
}
/*Gets the squared length of the vector*/
float BE::HBVec2::LengthSquared(const HBVec2& vec)
{
    return vec.LengthSquared();
}
/*Get the Distance between two points.*/
float BE::HBVec2::Distance(const HBVec2& vec1, const HBVec2& vec2)
{
    return vec1.Distance(vec2);
}
/*Gets the squared distance between two points*/
float BE::HBVec2::DistanceSquared(const HBVec2& vec1, const HBVec2& vec2)
{
    return vec1.DistanceSquared(vec2);
}
/*Tests if two vectors are equal*/
bool BE::HBVec2::IsEqual(const HBVec2& vec1, const HBVec2& vec2)
{
    if (vec1 == vec2)
        return true;

    return false;
}
/*Tests if two vectors are not equal*/
bool BE::HBVec2::IsNotEqual(const HBVec2& vec1, const HBVec2& vec2)
{
    if (vec1 == vec2)
        return false;

    return true;
}
/*Test if this is the zero vector*/
bool BE::HBVec2::IsZero(const HBVec2& vec)
{
    return vec.IsZero();
}

//friend function************************************************************
/*Allows users to scale a vector*/
BE::HBVec2
BE::operator*(const float scale, const HBVec2& rhs)
{
    HBVec2 Vec2(rhs* scale);
    return Vec2;
}





