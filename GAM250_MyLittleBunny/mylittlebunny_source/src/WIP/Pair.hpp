/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:		Pair.hpp
Purpose:			The interface of class pair.
Language:		C++
Project:			GAM250
Author:			Name : HeeJae Kwon
Email:				sfhy33@gmail.com
Creation date:	2017.06.16
----------------------------------------------------------------------------*/
#pragma once
#include <Actor.hpp>
#include <Components\Transform.hpp>
#include <Components\Rigidbody.hpp>
#include <Components\CircleCollider.hpp>

namespace BE
{
    class AABB;
    class Pair {
    public:

        Component::Rigidbody* rigidbodyA;
        Component::Rigidbody* rigidbodyB;
        Component::Transform* posA;
        Component::Transform* posB;
//		Component::BoxCollider *bcA;
//		Component::BoxCollider *bcB;
        Component::CircleCollider *scA;
        Component::CircleCollider *scB;

        float penetration;
        HBVec2 normal;
        bool cs_state;
        bool cs_state_old;

        Actor* pA;
        Actor* pB;

        Pair(Actor* A, Actor* B);
        bool PairInit(void);
        void ResolveCollision(void);
        void PositionalCorrection(void);


    private:

//		void AABBvsAABB(Component::BoxCollider * a, Component::BoxCollider * b);
//		void AABBvsCircle(Component::BoxCollider * a, Component::SphereCollider * b);
//		void CirclevsAABB(Component::SphereCollider * a, Component::BoxCollider * b);
        void CirclevsCircle(Component::CircleCollider * a, Component::CircleCollider * b);
    };
}
