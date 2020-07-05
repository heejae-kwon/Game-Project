#pragma once

//#include <Actor.hpp>

class Actor;
#include <vector> // already in Actor

				class BaseCore
				{
				public:
					BaseCore() {};
					//Initialize the system
							virtual void Initialize(void);

					//All systems are updated every frame
					virtual void Update(float dt) = 0;

					//All systems need a virtual destructor to their desturctors called
					virtual ~BaseCore() {};

					virtual void    registerActor(Actor* actor);       //!< Adds an actor to the core's _actorStack
					virtual void    unregisterActor(Actor* actor);     //!< Remove an actor from the core's _actorStack

					std::vector<Actor*>&				   getRegisteredActors();        //!< Returns the vector of actor pointers that are registered to this core

				private:
					std::vector<Actor*>     _actorVec;             /*!< List of actors that are registered with this core */

				protected:
				};