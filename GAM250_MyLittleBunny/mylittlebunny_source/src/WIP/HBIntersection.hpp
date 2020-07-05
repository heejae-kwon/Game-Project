/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:		HBIntersection.hpp
Purpose:			Calculate the distance and intersection between 
						two objects.
Language:		C++
Project:		GAM250
Author:			Name : HeeJae Kwon
Email:          sfhy33@gmail.com
Creation date:	2017.06.16
----------------------------------------------------------------------------*/
#pragma once

#include "HBVec2.hpp"

namespace BE
{
    //!Functions to test the distance between two objects
    namespace HBDistance
    {
        //!Tests Distance between a point and  a circle
        float PointCircle(const HBVec2& point, const HBVec2& circleCenter,
            float radius);
        //!Tests Distance between a point and a rectangle
        float PointRect(const HBVec2 & point, const HBVec2 & max, const HBVec2 & min);
        //!Tests Distance between a point and a line segment
        float PointLine(const HBVec2& point, const HBVec2& lineStart,
            const HBVec2& lineEnd);
        //!Tests Distance between two circles
        float CircleCircle(const HBVec2& circleCenter0, float radius0,
            const HBVec2& circleCenter1, float radius1);
        //!Tests Distance between a circle and a rectangle
        float CircleRect(const HBVec2 & circleCenter, float radius, const HBVec2 & max, const HBVec2 & min);
        //!Tests Distance between a circle and a line segment
        float CircleLine(const HBVec2& circleCenter, float radius,
            const HBVec2& lineStart,
            const HBVec2& lineEnd);
        //!Tests Distance between two rectangles
        float RectRect(const HBVec2 & max0, const HBVec2 & min0, const HBVec2 & max1, const HBVec2 & min1);
    }//end namespace Distance


    //! Functions to test if two objects are simply intersecting
    namespace HBIntersection
    {
        //! Test if a point intersects a line
        bool PointLine(const HBVec2& point, const HBVec2& lineStart,
            const HBVec2& lineEnd);
        //! Test if a point intersects a circle
        bool PointCircle(const HBVec2& point, const HBVec2& circleCenter,
            float radius);
        //! Tests if a point intersects a rectangle
        bool PointRect(const HBVec2& point, const HBVec2& rectCenter,
            float width, float height);
        //! Test if two circles intersect
        bool CircleCircle(const HBVec2& circleCenter0, float radius0,
            const HBVec2& circleCenter1, float radius1);
        //! Test if a circle interects with a rectangle
        bool CircleRect(const HBVec2 & circleCenter, float radius, const HBVec2 & max, const HBVec2 & min);
        //! Test if a circle and a line intersect
        bool CircleLine(const HBVec2& circleCenter, float radius,
            const HBVec2& lineStart, const HBVec2& lineEnd);
        //! Tests if two rectangles intersect
        bool RectRect(const HBVec2& rectCenter0, float width0, float height0,
            const HBVec2& rectCenter1, float width1, float height1);
    }//end namespace HBIntersection
}
