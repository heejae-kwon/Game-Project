/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      Particle.cpp
Purpose:        crating a particle during the game
Language:       C++
Project:        GAM250
Author:         Name : wonjae.jung
Email:          wonjae0925@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/
#include <Core/Particle.hpp>
#include <Abstractions/RenderAbst.hpp>
#include <WIP/HBRandom.hpp>
#include <WIP/HBMath.hpp>

#include <cmath> /*atan2*/
#include <cstdio> /*FILE* fopen, fclose fscanf*/



namespace
{
    /*Color Info*/
    const float PI = 3.14159f;
    const int MAX_COLORS = 2;  //!<MAX COLORS
    const int RED = 0;  //!<RED COLORS
    const int YELLOW = 1;  //!<YELLOW COLORS
    unsigned  g_colors[MAX_COLORS] = { 0xFF0000FF, 0xFF00FFFF }; //!< colors
}//end unnamed namespace


BE::Core::Particle::Particle()
    : BaseCore()
{
    BaseCore::_coreStringId = "Particle";

    //CreateParticle(200);


}
BE::Core::Particle::~Particle()
{
}

void BE::Core::Particle::startNewFrame()
{

    BaseCore::startNewFrame();
    BaseCore::updateExecTime();

}
/******************************************************************************/
/*!
\brief
Update the emitter based on the type.
\param
Called the given my emitter
\param dt
time
*/
/******************************************************************************/
void BE::Core::Particle::update(float dt_)
{
    BaseCore::update();
    {
        for (uint32_t j = _actorOffset.top(); j < _actorVec.size(); ++j)
        {
            Component::ParticleEmitter*  particleEmitter = _actorVec[j]->getComponent<Component::ParticleEmitter>();

            //For Trail Type
            if (particleEmitter->particleType == ONE)
            {
                //InitExplosionSystem(particleEmitter);
				for (size_t i = 0; i < particleEmitter->m_particle.size(); ++i)
				{

					if (particleEmitter->m_particle[i].life <= 0 && particleEmitter->loop == true)
					{
						particleEmitter->m_particle[i].scale = glm::vec2(0);
						particleEmitter->m_particle[i].life = particleEmitter->lifetime;
					}

					if (particleEmitter->m_particle[i].life > 0.f)
					{
						particleEmitter->m_particle[i].life -= dt_;

						//If scale of particle is 0

						if (particleEmitter->m_particle[i].scale.x == 0.0f && particleEmitter->m_particle[i].scale.y == 0.0f)
						{
							float scale = static_cast<float>(std::rand() / particleEmitter->maxscale);
							float vel = particleEmitter->maxvel;

							float angle = std::rand() / PI;

							//Use rotation to calculate velocity x and y
							particleEmitter->m_particle[i].vel.x = std::cos(angle);
							particleEmitter->m_particle[i].vel.y = std::sin(angle);

							particleEmitter->m_particle[i].vel *= vel;

							//Set particle position to emitter position.
							particleEmitter->m_particle[i].pos = particleEmitter->owner->getComponent<Component::Transform>()->position;
							//Scale velocity random float between min/max TrailVel.
							particleEmitter->m_particle[i].scale.x = scale;
							particleEmitter->m_particle[i].scale.y = scale;

							// color
							particleEmitter->m_particle[i].color = particleEmitter->_texture.textureColor;

						}
						particleEmitter->m_particle[i].pos += glm::vec3(particleEmitter->m_particle[i].vel*dt_, 0.f);

						//Update particle scale based on scaleFactor and dt
						particleEmitter->m_particle[i].scale -= m_scaleFactor*dt_;

						//Clamp particle scale to 0 and maxTrailScale
						particleEmitter->m_particle[i].scale.x = HBMath::Clamp(particleEmitter->m_particle[i].scale.x, 0, particleEmitter->maxscale);
						particleEmitter->m_particle[i].scale.y = HBMath::Clamp(particleEmitter->m_particle[i].scale.y, 0, particleEmitter->maxscale);
					}
				}

            }//end of type 1
            else
            {
                ParticleUpdate(
                    particleEmitter->m_particle,
                    (int)(particleEmitter->m_particle.size()),
                    particleEmitter->owner,
                    particleEmitter->maxvel,
                    particleEmitter->minvel,
                    particleEmitter->maxscale,
                    particleEmitter->minscale,
                    particleEmitter->size,
                    particleEmitter->particleType,
                    dt_);

            }// 2 , 3, 4

            DrawParticles(particleEmitter, dt_);
        }
    }
    BaseCore::updateExecTime();
}

void BE::Core::Particle::endOfFrame()
{
    BaseCore::endOfFrame();
    BaseCore::updateExecTime();
    BaseCore::flushExecTimeLog();
}


/******************************************************************************/
/*!
\brief
Draw the emitter as efficiently as possible

\param pEmitter
Given the my Emitter

*/
/******************************************************************************/
void    BE::Core::Particle::DrawParticles(Component::ParticleEmitter* particle, float dt_)
{


    Prop::Image::imageData image = particle->_texture.getTexture(dt_);
    glm::vec3 position = particle->pos;
//    glm::vec2 size = particle->size;

    //Draw the particle
    for (size_t i = 0; i < particle->m_particle.size(); ++i)
    {

        if (particle->m_particle[i].life > 0.f)
        {
            RenderAbst::instance()->drawSprite(*image.texture,
                particle->m_particle[i].pos,
                particle->m_particle[i].scale,
                glm::radians(particle->m_particle[i].rotation),
                glm::vec4(1.f, 1.f, 1.f, 1.f));
        }

    } //end of for(Draw particle)

}

/******************************************************************************/
/*!
\brief
ParticleUpdate

This function doing update when particle type 2,3,4

*/
/******************************************************************************/
void BE::Core::Particle::ParticleUpdate(
    std::vector<ParticleStruct>	 & m_particle,
    int capacity,
    BE::Actor* owner,
    float maxvel,
    float,
    float maxscale,
    float minscale,
    glm::vec2 size,
    BE::ParticleType type,
    float dt)
{
    Component::ParticleEmitter *particleEmitter = owner->getComponent<Component::ParticleEmitter>();
    int frontScale = 0;
    int backScale = 0;
    int length = 0;
    float angle = 0;

//    Prop::Image::imageData image = particleEmitter->_texture.getTexture(dt);
//    glm::vec3 position = particleEmitter->pos;
//    glm::vec2 size = particleEmitter->size;


    for (int i = 0; i < capacity; ++i)
    {
        if (m_particle[i].life <= 0 && particleEmitter->loop == true)
        {
            m_particle[i].scale = glm::vec2(0);
            m_particle[i].life = particleEmitter->lifetime;
        }

        if (m_particle[i].life > 0.f)
        {
            m_particle[i].life -= dt;

            //If scale of particle is 0
            if (m_particle[i].scale == glm::vec2(0.0f))
            {
                int vel = 0;
                if (type == FOUR || type == ONE)
                {
                    vel = static_cast<int>(maxvel);
                }
                else
                {
                    if (maxvel != 0 && maxvel > 0)
                        vel = std::rand() % static_cast<int>(maxvel);
                    else if (maxvel != 0 && maxvel < 0)
                        vel = -std::rand() % static_cast<int>(maxvel);
                }
                float scale_X = std::rand() / size.x;
                float scale_Y = scale_X;

                if (maxscale != 0)
                    frontScale = rand() % static_cast<int>(maxscale);
                if (minscale != 0)
                    backScale = rand() % static_cast<int>(minscale);

                HBVec2 nomal = 0;
                //angle = HBMath::HALF_PI;
                if (type == TWO)
                {
                    angle = HBMath::HALF_PI;
                    length = frontScale - backScale;
                }
                else
                {
                    angle = std::rand() / HBMath::PI;
                }

                //float angle = HBMath::HALF_PI;

                //Use rotation to calculate velocity x and y
                m_particle[i].vel.x = std::cosf(angle);
                m_particle[i].vel.y = std::sinf(angle);

                m_particle[i].vel *= vel;

                //Set particle position to emitter position.
                m_particle[i].pos.x = owner->getComponent<Component::Transform>()->position.x + length;
                m_particle[i].pos.y = owner->getComponent<Component::Transform>()->position.y;
                m_particle[i].pos.z = owner->getComponent<Component::Transform>()->position.z -2;
                //Scale velocity random float between min/max TrailVel.
                m_particle[i].scale.x = scale_X;
                m_particle[i].scale.y = scale_Y;
                //color
                m_particle[i].color = particleEmitter->_texture.textureColor;
                m_particle[i].rotation = angle;
                m_particle[i].rotationSpeed = angle;
            }
            //Update particle position based on velocity and dt
            m_particle[i].pos += glm::vec3(m_particle[i].vel*dt, 0.f);

            //Update particle scale based on scaleFactor and dt
			if (particleEmitter->fade == true)
			{
				m_particle[i].scale -= 20 * dt;
			}

            //Clamp particle scale to 0 and maxTrailScale
            m_particle[i].scale.x = HBMath::Clamp(m_particle[i].scale.x, 0.1f, size.x);
            m_particle[i].scale.y = HBMath::Clamp(m_particle[i].scale.y, 0.1f, size.y);

            m_particle[i].rotation += (m_particle[i].rotationSpeed / 50) *dt;

//            position.z = float(i / 100.f);
//            if (m_particle[i].life > 0.f)
//            {
//                RenderAbst::instance()->drawSprite(*image.texture,
//                    m_particle[i].pos,
//                    m_particle[i].scale,
//                    glm::radians(m_particle[i].rotation),
//                    glm::vec4(1.f, 1.f, 1.f, 1.f));
//            }
        }
    }
}
