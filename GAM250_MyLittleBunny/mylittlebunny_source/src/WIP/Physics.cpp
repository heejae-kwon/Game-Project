/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      Physics.cpp
Language:      C++
Project:         GAM250
Author:         Name : HeeJae Kwon
Email:            sfhy33@gmail.com
Creation date:   2017.06.16
----------------------------------------------------------------------------*/
#include "Physics.hpp"
#include <Abstractions\RenderAbst.hpp>

#include <memory>

BE::Core::Physics::Physics()
    : BaseCore(), drawCircleColliders(false)
{
    BaseCore::_coreStringId = "Physics";
}

void
BE::Core::Physics::startNewFrame()
{
    BaseCore::startNewFrame();
    BaseCore::updateExecTime();
}

void
BE::Core::Physics::update(float dt_)
{
    BaseCore::update();
    {
        //	const float currenTime = static_cast<float>(GetCurrentTime());
        //	accumulator += currenTime - frameStart;
        //	frameStart = currenTime;
        //
        //	if (accumulator > (dt_*2)) {
        //		accumulator = dt_*2;
        //	}
        ////    float dt = 16.666f; // THIS IS/WAS A SUPER CHEAT !!!
        //	std::cout <<"ACCU" <<accumulator << std::endl;
        //	if (accumulator > dt_) {

        float dt = dt_;
//        dt = 0.01666f; // Physics locked at 60fps

        Broadphase();
		for (uint32_t i = _actorOffset.top(); i < _actorVec.size(); ++i)
		{
            if (_actorVec[i]->_isActive)
            {
                Component::Transform* position = _actorVec[i]->getComponent<Component::Transform>();
                Component::Rigidbody* rigidbody = _actorVec[i]->getComponent<Component::Rigidbody>();

                if (rigidbody->getInvMass() <= 0.0f) {
                    return;
                }

                if (rigidbody->staticstate != true) {
                    HBVec2 pos(position->position.x, position->position.y);
                    HBVec2 anchor(rigidbody->gravity - pos);
                    anchor.Normalize();
                    anchor *= rigidbody->gravityscale;
                    HBVec2 acc(rigidbody->force);
                    rigidbody->vel += ((acc + anchor)* dt * (rigidbody->getInvMass()));

                    position->position.x += rigidbody->vel.x*dt;
                    position->position.y += rigidbody->vel.y*dt;

                    float angACC = rigidbody->torque * (rigidbody->getInvInertia());
                    rigidbody->rotvel += angACC * dt;

                    position->rotation += (rigidbody->rotvel*dt);

                    rigidbody->force.Zero();
                    rigidbody->torque = 0;
                }
            }
        }
        for (auto& pair : Pairlist)
        {
            pair.PositionalCorrection();
        }
        //		accumulator -= DT;
    }
    BaseCore::updateExecTime();
}

void
BE::Core::Physics::endOfFrame()
{
    BaseCore::endOfFrame();
    
    if (drawCircleColliders)
    {
        for (auto & entity : _actorVec)
        {
            Component::Transform* transform = entity->getComponent<Component::Transform>();
            Component::CircleCollider* collider = entity->getComponent<Component::CircleCollider>();

            if (collider != nullptr)
            {
                if (entity->_isActive)
                {
                    RenderAbst::instance()->drawCircle(transform->position, glm::vec2(collider->radius, collider->radius), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
                }
                else if (collider->ghost)
                {
                    RenderAbst::instance()->drawCircle(transform->position, glm::vec2(collider->radius, collider->radius), glm::vec4(255.0f, 165.0f, 0.0f, 1.0f));
                }
                else
                {
                    RenderAbst::instance()->drawCircle(transform->position, glm::vec2(collider->radius, collider->radius), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
                }
            }
        }
    }
        
    BaseCore::updateExecTime();
    BaseCore::flushExecTimeLog();
}

void BE::Core::Physics::registerActor(Actor * actor_) {
    for (auto it = _actorVec.begin(); it != _actorVec.end(); ++it) {
        if (*it != actor_) {
            Pairlist.emplace_back(*it, actor_);
        }
    }
    BaseCore::registerActor(actor_);
}

void BE::Core::Physics::unregisterActor(Actor * actor_) {
    BaseCore::unregisterActor(actor_);
    // Remove actor form pair etcetera
    // You could use registerActor to create your pairs
    for (size_t i = 0; i < Pairlist.size(); ++i) {
        if (Pairlist[i].pA == actor_ || Pairlist[i].pB == actor_) {
            std::swap(Pairlist[i], Pairlist.back());  // We move the pointer to the end of the vector
            Pairlist.pop_back();                      // and then remove it from the vector
            i = 0;
        }
    }
    BaseCore::unregisterActor(actor_);
}

BE::Core::Physics::CollisionState
BE::Core::Physics::Collision(Actor* A, Actor* B)
{
    Component::CircleCollider* colliderA = A->getComponent<Component::CircleCollider>();
    Component::CircleCollider* colliderB = B->getComponent<Component::CircleCollider>();
    for (auto & collision : colliderA->collisionVec)
    {
//        if (A->_name == "player" && B->_name == "Finalplanet3")
//        {
//            int i = 0;
//            ++i;
//        }
        if (collision.collider == colliderB)
        {
            if (collision.oldState == collision.newState)
            {
                return CS_OnCollision;
            }
            else if (collision.oldState == false)
            {
                return CS_Start;
            }
            else if (collision.newState == false)
            {
                return CS_End;
            }
        }
    }
//    for (auto & pairs : Pairlist) {
//        if (((pairs.rigidbodyA == A->getComponent<Component::Rigidbody>()) && (pairs.rigidbodyB == B->getComponent<Component::Rigidbody>())) ||
//            ((pairs.rigidbodyA == B->getComponent<Component::Rigidbody>()) && (pairs.rigidbodyB == A->getComponent<Component::Rigidbody>()))) {
//
//            if (pairs.cs_state == true && pairs.cs_state_old != true) {
//                return CS_Start;
//            }
//            else	if (pairs.cs_state == true && pairs.cs_state_old == true) {
//                return CS_OnCollision;
//            }
//            else	if (pairs.cs_state != true && pairs.cs_state_old == true) {
//                return CS_End;
//            }
//        }
//    }
    return CS_NoCollision;
}

void
BE::Core::Physics::Broadphase(void)
{
//    for (auto it = Pairlist.begin(); it != Pairlist.end(); ++it) {
//        if (it->PairInit() || (it->cs_state_old == true)) {
//            it->ResolveCollision();
//        }
//    }

    for (size_t i = 0; i < Pairlist.size(); ++i) {
        if (Pairlist[i].PairInit() || (Pairlist[i].cs_state_old == true)) {
            Pairlist[i].ResolveCollision();
        }
    }

    /*    //Pairlist.clear();
        for (auto it = entityList.begin(); it != entityList.end(); ++it)
        {
            if ((*it)->_isActive)
            {
                for (auto jt = it; jt != entityList.end(); ++jt)
                {
                    if (it != jt && (*jt)->_isActive)
                    {
                        bool exist = false;

                        for (auto kt = Pairlist.begin(); kt != Pairlist.end(); ++kt)
                        {
                            if (kt->rigidbodyA == (*it)->getComponent<Component::Rigidbody>() && kt->rigidbodyB == (*jt)->getComponent<Component::Rigidbody>() ||
                                kt->rigidbodyB == (*it)->getComponent<Component::Rigidbody>() && kt->rigidbodyA == (*jt)->getComponent<Component::Rigidbody>())
                            {
                                exist = true;
                                break;
                            }
                        }

                        if (!exist)
                        {
                            Pairlist.emplace_back(*it, *jt);
                        }

                    }
                }
            }
        }
        for (auto it = Pairlist.begin(); it != Pairlist.end(); ) {
            if (it->PairInit() || (it->cs_state_old == true))  {
                it->ResolveCollision();
                ++it;
            }
            else {
                Pairlist.erase((it++));
            }

        }*/
}
