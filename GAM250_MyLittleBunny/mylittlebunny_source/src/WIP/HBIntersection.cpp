/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:		HBIntersection.cpp	
Purpose:			Calculate distance or intersection between two objects. 
Language:		C++
Project:			GAM250
Author:			Name : HeeJae Kwon
Email:				sfhy33@gmail.com
Creation date:	2017.06.16
----------------------------------------------------------------------------*/
#include "HBIntersection.hpp"
#include <iostream>
#include "HBMath.hpp"

//!Functions to test the distance between two objects
namespace
{
    const int RectPointNum = 4;
}

//!Tests Distance between a point and  a circle
float
BE::HBDistance::PointCircle(const HBVec2& point, const HBVec2& circleCenter,
    float radius)
{
    return HBVec2::Distance(point, circleCenter) - radius;
}
//!Tests Distance between a point and a rectangle
float
BE::HBDistance::PointRect(const HBVec2& point, const HBVec2& max,
    const HBVec2& min)
{
    HBVec2 maxXminY = { max.x, min.y };
    HBVec2 minXmaxY = { min.x, max.y };

    return HBMath::Min(
        HBMath::Min(HBVec2::Distance(point, max), HBVec2::Distance(point, min)),
        HBMath::Min(HBVec2::Distance(point, maxXminY), HBVec2::Distance(point, minXmaxY))
    );
}
//!Tests Distance between a point and a line segment
float
BE::HBDistance::PointLine(const HBVec2& point, const HBVec2& lineStart,
    const HBVec2& lineEnd)
{
    HBVec2 Line = lineEnd - lineStart;
    HBVec2 Hypotenuse = point - lineStart;
    HBVec2 ProjectPerp;
    HBVec2::PerpProject(ProjectPerp, Hypotenuse, Line);

    return ProjectPerp.Length();
}
//!Tests Distance between two circles
float
BE::HBDistance::CircleCircle(const HBVec2& circleCenter0, float radius0,
    const HBVec2& circleCenter1, float radius1)
{
    return HBVec2::Distance(circleCenter0, circleCenter1) - (radius0 + radius1);
}
//!Tests Distance between a circle and a rectangle
float
BE::HBDistance::CircleRect(const HBVec2& circleCenter, float radius,
    const HBVec2& max, const HBVec2& min)
{
    return PointRect(circleCenter, max, min) - radius;
}
//!Tests Distance between a circle and a line segment
float
BE::HBDistance::CircleLine(const HBVec2& circleCenter, float radius,
    const HBVec2& lineStart,
    const HBVec2& lineEnd)
{
    return PointLine(circleCenter, lineStart, lineEnd) - radius;
}
//!Tests Distance between two rectangles
float
BE::HBDistance::RectRect(const HBVec2& max0, const HBVec2& min0, const HBVec2& max1, const HBVec2& min1)
{
    HBVec2 max0Xmin0Y = { max0.x, min0.y };
    HBVec2 min0Xmax0Y = { min0.x, max0.y };

    return HBMath::Min(HBMath::Min(HBMath::Min(PointRect(max0, max1, min1),
        PointRect(min0, max1, min1)),
        PointRect(max0Xmin0Y, max1, min1)),
        PointRect(min0Xmax0Y, max1, min1));
}



//!Tests Distance between a point and a line segment
bool
BE::HBIntersection::PointLine(const HBVec2& point, const HBVec2& lineStart,
    const HBVec2& lineEnd)
{
    if (BE::HBDistance::PointLine(point, lineStart, lineEnd) <= HBMath::EPSILON)
    {
        return true;
    }

    return false;
}

//! Test if a point intersects a circle
bool
BE::HBIntersection::PointCircle(const HBVec2& point, const HBVec2& circleCenter,
    float radius)
{
    if (HBVec2::DistanceSquared(point, circleCenter) <= radius*radius)
    {
        return true;
    }

    return false;
}
//! Tests if a point intersects a rectangle
bool
BE::HBIntersection::PointRect(const HBVec2& point, const HBVec2& rectCenter,
    float width, float height)
{
    if (HBMath::IsInRange(point.x, rectCenter.x - width / 2, rectCenter.x + width / 2) == true &&
        HBMath::IsInRange(point.y, rectCenter.y - height / 2, rectCenter.y + height / 2) == true)
    {
        return true;
    }

    return false;
}
//! Test if two circles intersect
bool
BE::HBIntersection::CircleCircle(const HBVec2& circleCenter0, float radius0,
    const HBVec2& circleCenter1, float radius1)
{
    if (HBVec2::DistanceSquared(circleCenter0, circleCenter1) <= (radius0 + radius1)*(radius0 + radius1))
    {
        return true;
    }

    return false;
}
//! Test if a circle interects with a rectangle
bool
BE::HBIntersection::CircleRect(const HBVec2& circleCenter, float radius,
    const HBVec2& max, const HBVec2& min)
{
    if (BE::HBDistance::PointRect(circleCenter, max, min) <= radius)
    {
        return true;
    }

    return false;
}
//! Test if a circle and a line intersect
bool
BE::HBIntersection::CircleLine(const HBVec2& circleCenter, float radius,
    const HBVec2& lineStart, const HBVec2& lineEnd)
{
    if (BE::HBDistance::PointLine(circleCenter, lineStart, lineEnd) <= radius)
    {
        return true;
    }

    return false;
}
//! Tests if two rectangles intersect
bool
BE::HBIntersection::RectRect(const HBVec2& rectCenter0, float halfwidth0, float halfheight0,
    const HBVec2& rectCenter1, float halfwidth1, float halfheight1)
{
    if (std::abs(rectCenter0.x - rectCenter1.x) > halfwidth0 + halfwidth1) return false;
    if (std::abs(rectCenter0.y - rectCenter1.y) > halfheight0 + halfheight1) return false;

    return true;

    // No separating axis found, therefor there is at least one overlapping axis
}
