/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:		Pair.cpp
Purpose:			The class that contains all data of collision.
Language:		C++
Project:			GAM250
Author:			Name : HeeJae Kwon
Email:				sfhy33@gmail.com
Creation date:	2017.06.16
----------------------------------------------------------------------------*/
#include "Pair.hpp"
#include "HBMath.hpp"

namespace BE {

    Pair::Pair(Actor *A, Actor *B) {
        rigidbodyA = A->getComponent<Component::Rigidbody>();
        rigidbodyB = B->getComponent<Component::Rigidbody>();
        posA = A->getComponent<Component::Transform>();
        posB = B->getComponent<Component::Transform>();
        //        bcA = A->getComponent<Component::BoxCollider>();
        //        bcB = B->getComponent<Component::BoxCollider>();
        scA = A->getComponent<Component::CircleCollider>();
        scB = B->getComponent<Component::CircleCollider>();

        pA = A;
        pB = B;

        penetration = 0;
        cs_state = false;
        cs_state_old = false;
    }

    bool Pair::PairInit(void)
    {
        //        if (bcA != nullptr && bcB != nullptr) {
        //            AABBvsAABB(bcA, bcB);
        //        }
        //        else if (bcA != nullptr && scB != nullptr) {
        //            AABBvsCircle(bcA, scB);
        //        }
        //        else if (scA != nullptr && bcB != nullptr) {
        //            CirclevsAABB(scA, bcB);
        //        }
        if (rigidbodyA == nullptr || rigidbodyB == nullptr)
        {
            rigidbodyA = pA->getComponent<Component::Rigidbody>();
            rigidbodyB = pB->getComponent<Component::Rigidbody>();
        }
        if (scA == nullptr || scB == nullptr)
        {
            scA = pA->getComponent<Component::CircleCollider>();
            scB = pB->getComponent<Component::CircleCollider>();
        }
        if (scA != nullptr && scB != nullptr) {
            CirclevsCircle(scA, scB);
        }
        return cs_state;
    }

    void
        Pair::ResolveCollision(void) {
        if (!cs_state || scA->ghost || scB->ghost) {
            return;
        }

        HBVec2 rv = rigidbodyB->vel - rigidbodyA->vel;

        float velAlongNormal = HBVec2::Dot(rv, normal);

        if (velAlongNormal > 0) {
            return;
        }

        float e = HBMath::Min(rigidbodyA->restitution, rigidbodyB->restitution);

        HBVec2 rotA(0.f, (posA->rotation));
        HBVec2 rotB(0.f, (posB->rotation));
        float rA = HBVec2::CrossZ(rotA, normal);
        float rB = HBVec2::CrossZ(rotB, normal);

        float jN = -(1 + e) * velAlongNormal;
        jN /= rigidbodyA->getInvMass() + rigidbodyB->getInvMass() +
            rA*rA*rigidbodyA->getInvInertia() + rB*rB*rigidbodyB->getInvInertia();

        HBVec2 impulse = jN * normal;
        float mass_sum = rigidbodyA->getMass() + rigidbodyB->getMass();

        float ratio = 0;
        if (rigidbodyA->staticstate != true) {
            ratio = rigidbodyA->getMass() / mass_sum;
            rigidbodyA->vel -= ratio * impulse;
        }
        if (rigidbodyB->staticstate != true) {
            ratio = rigidbodyB->getMass() / mass_sum;
            rigidbodyB->vel += ratio*impulse;
        }
        //angularVelocity += 1.0f / inertia * Cross(contactVector, impulse);
        //angularVelocity += 1.0f / inertia * Cross(contactVector, impulse);


        // Re-calculate relative velocity after normal impulse
        // is applied (impulse from first article, this code comes
        // directly thereafter in the same resolve function)
        rv = rigidbodyB->vel - rigidbodyA->vel;

        // Solve for the tangent vector
        HBVec2 tangent = rv - HBVec2::Dot(rv, normal) * normal;
        tangent.Normalize();

        // Solve for magnitude to apply along the friction vector
        float jt = -HBVec2::Dot(rv, tangent);
        rA = HBVec2::CrossZ(rotA, tangent);
        rB = HBVec2::CrossZ(rotB, tangent);
        jt /= rigidbodyA->getInvMass() + rigidbodyB->getInvMass() +
            rA*rA*rigidbodyA->getInvInertia() + rB*rB*rigidbodyB->getInvInertia();

        // PythagoreanSolve = A^2 + B^2 = C^2, solving for C given A and B
        // Use to approximate mu given friction coefficients of each body
        float mu = HBMath::PythagoreanSolve(rigidbodyA->friction_static, rigidbodyB->friction_static);

        // Clamp magnitude of friction and create impulse vector
        HBVec2 frictionImpulse;
        if (std::abs(jt) < jN * mu)
            frictionImpulse = jt * tangent;
        else {
            float dynamicFriction = HBMath::PythagoreanSolve(rigidbodyA->friction_dynamic, rigidbodyB->friction_dynamic);
            frictionImpulse = -jN * tangent * dynamicFriction;
        }

        // Apply
        if (rigidbodyA->staticstate != true) {
            rigidbodyA->vel -= rigidbodyA->getInvMass() * frictionImpulse;
        }
        if (rigidbodyB->staticstate != true) {
            rigidbodyB->vel += rigidbodyB->getInvMass() * frictionImpulse;
        }
        //angularVelocity += 1.0f / inertia * Cross(contactVector, impulse);
        //angularVelocity += 1.0f / inertia * Cross(contactVector, impulse);
    }

    void
        Pair::PositionalCorrection(void) {

        if (!cs_state || scA->ghost || scB->ghost) {
            return;
        }

        const float percent = 1.5f;
        const float slop = 0.1f;
        HBVec2 correction = HBMath::Max(penetration - slop, 0.0f) /
            (rigidbodyA->getInvMass() + rigidbodyB->getInvMass()) * percent * normal;

        if (rigidbodyA->staticstate != true) {
            posA->position.x -= correction.x * rigidbodyA->getInvMass();
            posA->position.y -= correction.y * rigidbodyA->getInvMass();
        }
        if (rigidbodyB->staticstate != true) {
            posB->position.x += correction.x * rigidbodyB->getInvMass();
            posB->position.y += correction.y * rigidbodyB->getInvMass();
        }
    }

    void
        Pair::CirclevsCircle(Component::CircleCollider * a, Component::CircleCollider * b)
    {
        if (!a->owner->_isActive || !b->owner->_isActive)
        {
            return;
        }

        // Setup a couple pointers to each object
        cs_state_old = cs_state;

        // Vector from A to B
        HBVec2 n(posB->position.x - posA->position.x, posB->position.y - posA->position.y);

        float r = a->radius + b->radius;

        if (n.LengthSquared() > r*r) {
            a->updateCollision(b, false);
            b->updateCollision(a, false);
            cs_state = false;
            return;
        }

        // Circles have collided, now compute manifold
        float d = n.Length(); // perform actual sqrt

                              // If distance between circles is not zero
        if (d != 0) {
            // Distance is difference between radius and distance
            penetration = r - d;
            //			std::cout << penetration << std::endl;
            // Utilize our d since we performed sqrt on it already within Length( )
            // Points from A to B, and is a unit vector
            normal = n *(1 / d);
            a->updateCollision(b, true);
            b->updateCollision(a, true);
            cs_state = true;
        }
        // Circles are on same position
        else {
            // Choose random (but consistent) values
            penetration = a->radius;
            normal = { 1, 0 };
            a->updateCollision(b, true);
            b->updateCollision(a, true);
            cs_state = true;
        }
    }

    //    void
    //        Pair::AABBvsAABB(Component::BoxCollider *a, Component::BoxCollider * b) {
    //
    //        HBVec2 n(posB->x - posA->x, posB->y - posA->y);
    //
    //        float a_extent = (a->halfSize.x);
    //        float b_extent = (b->halfSize.x);
    //
    //        float x_overlap = a_extent + b_extent - std::abs(n.x);
    //
    //        if (x_overlap > 0) {
    //
    //            a_extent = (a->halfSize.y);
    //            b_extent = (b->halfSize.y);
    //
    //            float y_overlap = a_extent + b_extent - std::abs(n.y);
    //
    //            if (y_overlap > 0) {
    //
    //                if (x_overlap > y_overlap) {
    //
    //                    if (n.x < 0) {
    //                        normal = { -1, 0 };
    //                    }
    //                    else {
    //                        normal = { 1,0 };
    //                    }
    //                    penetration = x_overlap;
    //                    cs_state = true;
    //                }
    //                else {
    //                    if (n.y < 0) {
    //                        normal = { 0,-1 };
    //                    }
    //                    else {
    //                        normal = { 0,1 };
    //                    }
    //                    penetration = y_overlap;
    //                    cs_state = true;
    //                }
    //
    //            }
    //
    //        }
    //    }

    //    void
    //        Pair::AABBvsCircle(Component::BoxCollider *a, Component::SphereCollider *b)
    //    {
    //		cs_state_old = cs_state;
    //        // Setup a couple pointers to each object
    //
    //    // Vector from A to B
    //
    //        HBVec2 n(posB->x - posA->x, posB->y - posA->y);
    //        // Closest point on A to center of B
    //        HBVec2 closest = n;
    //
    //        /*	// Calculate half extents along each axis
    //            float x_extent = (a->halfSize.x);
    //            float y_extent = (a->halfSize.y);
    //
    //            // Clamp point to edges of the AABB
    //            closest.x = HBMath::Clamp(closest.x, -x_extent, x_extent);
    //            closest.y = HBMath::Clamp(closest.y, -y_extent, y_extent);
    //            */
    //        HBVec2 Vertex[4] = {
    //            {posA->x - a->halfSize.x, posA->y - a->halfSize.y},
    //            {posA->x + a->halfSize.x, posA->y - a->halfSize.y},
    //            {posA->x - a->halfSize.x, posA->y + a->halfSize.y},
    //            {posA->x + a->halfSize.x, posA->y + a->halfSize.y},
    //        };
    //        float cloestLengthSquare = n.LengthSquared();
    //        HBVec2 CircleCenter(posB->x, posB->y);
    //        for (int i = 0; i < 4; ++i) {
    //            float vertexlength = HBVec2::DistanceSquared(Vertex[i], CircleCenter);
    //            if (cloestLengthSquare > vertexlength) {
    //                closest = Vertex[i];
    //                cloestLengthSquare = vertexlength;
    //            }
    //        }
    //
    //        bool inside = false;
    //
    //        // Circle is inside the AABB, so we need to clamp the circle's center
    //        // to the closest edge
    //        if (n == closest)
    //        {
    //            inside = true;
    //
    //            /*		// Find closest axis
    //                    if (std::abs(n.x) > std::abs(n.y)) {
    //                        // Clamp to closest extent
    //                        if (closest.x > 0)
    //                            closest.x = x_extent;
    //                        else
    //                            closest.x = -x_extent;
    //                    }
    //
    //                    // y axis is shorter
    //                    else {
    //                        // Clamp to closest extent
    //                        if (closest.y > 0)
    //                            closest.y = y_extent;
    //                        else
    //                            closest.y = -y_extent;
    //                    }*/
    //        }
    //
    //        normal = n - closest;
    //        float d = normal.LengthSquared();
    //        float r = b->radius;
    //
    //        // Early out of the radius is shorter than distance to closest point and
    //        // Circle not inside the AABB
    //        if (d > r * r && !inside) {
    //            cs_state = false;
    //            return;
    //        }
    //
    //        // Avoided sqrt until we needed
    //        d = normal.Length();
    //
    //        // Collision normal needs to be flipped to point outside if circle was
    //        // inside the AABB
    //        if (inside) {
    //            normal = -n.Normalize();
    //            penetration = r - d;
    //        }
    //        else {
    //            normal = n.Normalize();
    //            penetration = r - d;
    //        }
    //
    //        cs_state = true;
    //    }

    //    void
    //        Pair::CirclevsAABB(Component::SphereCollider *a, Component::BoxCollider *b)
    //    {
    //        AABBvsCircle(b, a);
    //    }
}