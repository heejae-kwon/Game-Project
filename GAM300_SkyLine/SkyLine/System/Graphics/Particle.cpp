#include "Particle.h"



Particle::Particle(int /*_id*/)
	: 
	position_({ 0.0f ,0.0f,0.0f}),
	velocity_({ 0.0f ,0.0f,0.0f }),
	color_({ 0.0f, 0.0f, 0.0f,0.0f }),
	life_(0.0f) 
{ 
}


Particle::~Particle()
{
}
