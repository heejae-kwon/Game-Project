#pragma once
#include <glm/glm.hpp>
class Particle
{
public:
	Particle(int _id =-1);
	virtual ~Particle();

	glm::vec4 color_;
	glm::vec3 position_;
	float life_;
	float id_;
	glm::vec3 velocity_;
};

