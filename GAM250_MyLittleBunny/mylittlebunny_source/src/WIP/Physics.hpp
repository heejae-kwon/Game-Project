/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:		Physics.hpp
Language:		C++
Project:			GAM250
Author:			Name : HeeJae Kwon
Email:				sfhy33@gmail.com
Creation date:	2017.06.16
----------------------------------------------------------------------------*/
#pragma once

#include <Core/BaseCore.hpp>
#include <WIP/Pair.hpp>

#include <glm/glm.hpp>

namespace BE
{
    namespace Core
    {

        //!  The BunnyEngine's Physics Core class. 
        /*!
        The Physics class is in charge of Physicsing images to our screen.
        The way it works is that we feed it Actors that have a Physics component
        and the Physics core processes these if needed (discard some if they are out of the camera's range for example)
        and calls the appriopriate functions to render them to the screen.
        */
        class Physics : public BaseCore
        {
            // All type redefinitions go here
        public:
            enum CollisionState
            {
                CS_Start,
                CS_OnCollision,
                CS_End,
                CS_NoCollision
            };

        protected:
            using PhysicsSmartPtr = std::unique_ptr<Physics>;

        public:
            static Physics*    instance() //!< Returns an instance of the class
            {
                static PhysicsSmartPtr instance(new Physics());
                return instance.get();
            }
            ~Physics() = default;

            // These 3 should be automatically called every loop
            void            startNewFrame() final;  //!< This should be used to setup anything that is essential before data starts getting processed (ex: clearing the screen buffer)
            void            update(float dt)        final;  //!< All the data get's processed in this funtrion (There will be a loop in this function for sure)
            void            endOfFrame()    final;  //!< Once all the data processing is done we call the final functions if needed (ex: flipping the screen buffer)
			void			   registerActor(Actor* actor_) final;       //!< Adds an actor to the core's _actorStack
            void            unregisterActor(Actor* actor_) final;

            CollisionState Collision(Actor* A, Actor* B);
        protected:
            //
        private:
            Physics(); //!< Physics's constructor is private as it is a Singleton and should only be accessed through the instance() function
			void Broadphase(void);

        public:
            bool drawCircleColliders;
        protected:
            //
        private:
            std::vector<Pair>        Pairlist;
        };
    }
}
