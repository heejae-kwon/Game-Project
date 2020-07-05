/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      Particle.hpp
Purpose:        crating a particle during the game
Language:       C++
Project:        GAM250
Author:         Name : wonjae.jung
Email:          wonjae0925@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/
#pragma once

#include <Core/BaseCore.hpp>
#include "Actor.hpp"
#include <WIP/HBVec2.hpp>

#include <glm/glm.hpp>

namespace BE
{
	namespace Core
	{
		
		enum EmitterType
		{
			ONE,    /*!<ET_EXPLOSION */
			TWO,     /*!<ET_TRAIL     */
			THREE,
			FOUR
		};


		//!  The BunnyEngine's Particle Core class. 
		/*!
		The Particle class is in charge of drawing particle to our screen.
		The way it works is that we feed it Actors that have a Particle component
		and the Particle core processes these if needed (discard some if they are out of the camera's range for example)
		and calls the appriopriate functions to render them to the screen.
		*/
		class Particle : public BaseCore
		{
			// All type redefinitions go here
		protected:
			using ParticleSmartPtr = std::unique_ptr<Particle>;

		public:
			static Particle*    instance() //!< Returns an instance of the class
			{
				static ParticleSmartPtr instance(new Particle());
				return instance.get();
			}
			~Particle();

			// These 3 should be automatically called every loop
			void            startNewFrame() final;  //!< This should be used to setup anything that is essential before data starts getting processed (ex: clearing the screen buffer)
			void            update(float dt_)        final;  //!< All the data get's processed in this funtrion (There will be a loop in this function for sure)
			void            endOfFrame()    final;  //!< Once all the data processing is done we call the final functions if needed (ex: flipping the screen buffer)

			void			DrawParticles(Component::ParticleEmitter* particle, float dt_);
		protected:
			//
		private:
			Particle(); //!< Particle's constructor is private as it is a Singleton and should only be accessed through the instance() function

		public:
			//
		protected:
			//
		private:
			std::stack<Actor*>     _cameraStack;

			void ParticleUpdate(
				std::vector<ParticleStruct>	& m_particle,
				int capacity,
				Actor* owner,
				float maxvel,
				float minvel,
				float maxscale,
				float minscale,
				glm::vec2 size,
				BE::ParticleType type,
				float dt);




			//std::vector<ParticleStruct>        m_Particles;	//!< pParitcles
			std::vector<Actor*>                _ParticleActorVec;

			int					   m_capacity;    //!< my m_capacity
			int					   m_size;        //!< my m_size
			int					   m_currentID;   //!< my m_currentID

			float			  	   m_scaleFactor;  //!< my scaleFactor
			float				   m_expLife;      //!< my expLife



		};
	}
}
