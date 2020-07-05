/* ---------------------------------------------------------------------------
Copyright (C) 2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:		HBVec2.h
Purpose:			The interface of HBVec2 class.  
Language:		C++
Project:			GAM200
Author:			Name : HeeJae Kwon
Email:				sfhy33@gmail.com
Creation date:	2016.12.09
----------------------------------------------------------------------------*/
#pragma once
#include <glm\vec2.hpp>
#include <glm\vec3.hpp>
namespace BE
{
    /*! A 2D vector for a 2D game, use a separate variable for Z-Order.
    Can be used C style with static functions or C++ with methods.*/
    class __declspec(dllexport) HBVec2
    {
    public:
        float x;/*!< The x coordinate of the vector*/
        float y;/*!< The y coordinate of the vector*/


        //C++ additions**********************************************************

        //Constructor
        HBVec2(const float a = 0, const float b = 0);
        //Copy Constructor
        HBVec2(const HBVec2& rhs);
        HBVec2(const glm::vec2& rhs);
        HBVec2(const glm::vec3& rhs);
        //Destructor
        ~HBVec2(void);

        //Operators
        /*Adds two vectors*/
        HBVec2  operator+(const HBVec2& rhs) const;
        /*Subtracts two vectors*/
        HBVec2  operator-(const HBVec2& rhs) const;
        /*Negates a vector*/
        HBVec2 operator-(void) const;
        /*Scales a vector*/
        HBVec2  operator*(const float scale)       const;
        /*Adds a vector to this vector*/
        HBVec2& operator+=(const HBVec2& rhs);
        /*Subtracts a vector from this vector*/
        HBVec2& operator-=(const HBVec2& rhs);
        /*Scales this vector*/
        HBVec2& operator*=(const float scale);
        /*Negates this vector*/
    	HBVec2& operator-(void);
		/*Equal operators*/
        /*void operator=(const HBVec2& rhs);
        void operator=(const glm::vec2& rhs);
        void operator=(const glm::vec3& rhs); */
        /*Tests if two vectors are equal*/
        bool    operator==(const HBVec2& rhs) const;
        /*Tests if two vectors are not equal*/
        bool    operator!=(const HBVec2& rhs) const;

        //Member functions**********************************************************
        HBVec2 &Rotate(const float rotation);

        HBVec2  Project(const HBVec2& rhs) const;
        HBVec2  ProjectPerp(const HBVec2& rhs) const;
        void     Zero(void);

        /*Normalizes this vector*/
        HBVec2& Normalize(void);
        /*Allows user to quickly set x and y*/
        void  Set(const float xx = 0.f, const float yy = 0.f);
        /*Performs the dot product on two vectors*/
        float Dot(const HBVec2& rhs) const;
        /*Find Degree between two Vector*/
        int FindDegree(const HBVec2 & rhs) const;
        float FindRadian(const HBVec2 & rhs) const;
        /*Gets the Z component of the cross product of two vectors*/
        float CrossZ(const HBVec2& rhs) const;
        /*Gets the length of the vector*/
        float Length(void) const;
        /*Gets the squared length of the vector*/
        float LengthSquared(void) const;
        /*Treats the vector as a point and gets the distace to another pointer*/
        float Distance(const HBVec2& point) const;
        /*Gets the squared distance between two points*/
        float DistanceSquared(const HBVec2& point) const;
        /*Checks if this is the zero vector*/
        bool  IsZero(void) const;

        //Non member functions*******************************************************

        /*Rotate a vector*/
        static void Rotate(HBVec2& result, const HBVec2& vec, const float radian);
        /*Allows user to quickly set x and y*/
        static void Set(HBVec2& result, const float x, const float y);
        /*Negates a vector*/
        static void Negate(HBVec2& result, const HBVec2& toNegate);
        /*Adds two vectors together*/
        static void Add(HBVec2& result, const HBVec2& vec1, const HBVec2& vec2);
        /*Subtracts two vectors*/
        static void Sub(HBVec2& result, const HBVec2& vec1, const HBVec2& vec2);
        /*Scales a vector*/
        static void Scale(HBVec2& result, const HBVec2& toScale, const float scale);
        /*Normalizes a vector*/
        static void Normalize(HBVec2& result, const HBVec2& toNormalize);
        /*Gets the projection vector of vec1 onto vec2*/
        static void Project(HBVec2& result, const HBVec2& vec1, const HBVec2& vec2);
        /*Gets the perpendicular projection vector of vec1 onto vec2*/
        static void PerpProject(HBVec2& result, const HBVec2& vec1, const HBVec2& vec2);
        /*Linearly interpolates a vector based on time*/
        static void Lerp(HBVec2& result, const HBVec2& vec1, const HBVec2& vec2,
            const float time);
        /*Gets the Z component of the cross product*/
        static float CrossZ(const HBVec2& vec1, const HBVec2& vec2);
        /*Calculates the dot product of two vectors*/
        static float Dot(const HBVec2& vec1, const HBVec2& vec2);
        static int FindDegree(const HBVec2 & vec1, const HBVec2 & vec2);
        /*Get the Length of a vector*/
        static float Length(const HBVec2& vec);
        /*Gets the squared length of the vector*/
        static float LengthSquared(const HBVec2& vec);
        /*Get the Distance between two points.*/
        static float Distance(const HBVec2& vec1, const HBVec2& vec2);
        /*Gets the squared distance between two points*/
        static float DistanceSquared(const HBVec2& vec1, const HBVec2& vec2);
        /*Tests if two vectors are equal*/
        static bool IsEqual(const HBVec2& vec1, const HBVec2& vec2);
        /*Tests if two vectors are not equal*/
        static bool IsNotEqual(const HBVec2& vec1, const HBVec2& vec2);
        /*Test if this is the zero vector*/
        static bool IsZero(const HBVec2& vec);

        //friend function************************************************************
        /*Allows users to scale a vector*/
        friend HBVec2 operator*(const float scale, const HBVec2& rhs);

    };
}
