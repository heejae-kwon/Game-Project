/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      Rigidbody.hpp
Language:      C++
Project:         GAM250
Author:         Name : HeeJae Kwon
Email:            sfhy33@gmail.com
Creation date:   2017.06.16
----------------------------------------------------------------------------*/
#pragma once

#include <Components/BaseComponent.hpp>
#include <WIP/PropManager.hpp>
#include <WIP/HBVec2.hpp>

#include <glm\glm.hpp>
#include <json\json.h>

namespace BE
{
    namespace Component
    {

        class Rigidbody : public BaseComponent
        {
        public:
            COMPONENT_HASH(Rigidbody)
            Rigidbody(Actor* owner_);
            ~Rigidbody();

            void    getData(Json::Value& data_)     final;
            void    writeData(Json::Value& data_)   final;
            void    drawData()                      final;
			void setInertia(float input);
			void setMass(float input);
			void setInvInertia(void);
			void setInvMass(void);

			const float getInertia(void) const ;
			const float getMass(void) const ;
			const float getInvInertia(void) const ;
			const float getInvMass(void) const ;
        private:


		
            //

        public:	
	

            float   restitution;      // PLEASE COMMENT
            float   friction_static;
            float   friction_dynamic; //No negative
            HBVec2  vel;             // PLEASE COMMENT
            float   rotvel;           // PLEASE COMMENT
            HBVec2  force;           // PLEASE COMMENT
            float   torque;           // PLEASE COMMENT

            HBVec2  gravity;         // PLEASE COMMENT
            float gravityscale;
            bool    staticstate;


        private:	
			float   inertia;          // No negative
			float   inv_inertia;      // PLEASE COMMENT
			float   mass;             // No negative
			float   inv_mass;         // PLEASE COMMENT
            //
        };

    }
}
