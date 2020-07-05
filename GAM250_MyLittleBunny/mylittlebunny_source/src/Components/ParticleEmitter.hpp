/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      ParticleEmitter.hpp
Purpose:        ParticleEmitter component used by the Particle core
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#pragma once

#include <Components/BaseComponent.hpp>
#include <Components/Display.hpp>
//#include <WIP/PropManager.hpp>

#include <glm\glm.hpp>
#include <json\json.h>

namespace BE
{
	enum ParticleType
	{
		ONE,
		TWO,
		THREE,
		FOUR
	};
	struct ParticleStruct
	{
		glm::vec3 pos;    //!<position
		glm::vec2 vel;    //!<velocity
		glm::vec2 scale;      //!<scale
		glm::vec4 color;   //!<color
        float rotation;
        float rotationSpeed;
		int ID;
		float life;
	};//!< struct Particle 


	namespace Component
	{
		static const std::string ParticleTypeStr[] =
		{
			"ONE",
			"TWO",
			"THREE",
			"FOUR"
		};

		class ParticleEmitter : public BaseComponent
		{
		public:
			

			COMPONENT_HASH(ParticleEmitter)
			ParticleEmitter(Actor* owner_);
			~ParticleEmitter();

			void    getData(Json::Value& data_)     final;
			void    writeData(Json::Value& data_)   final;
			void    drawData()                      final;

            void    setCapacity(int capacity_);
            void    resetParticles();

		private:
			ParticleType    stringToParticleEnum(std::string str_);

		public:
            Display _texture;

			//Particle component
			ParticleType				particleType;
			std::vector<ParticleStruct> m_particle;
			glm::vec3					pos;
			glm::vec2					size;
			float						maxscale;
			float						minscale;
			float						maxvel;
			float						minvel;
			float						lifetime;
            bool                        loop;
			bool                        fade;
		private:
			char buf1[64] = "";     // Buffer for Actor name
			int							ddType = 0;         // DropDown Type
            int							capacity;
        };

	}
}
