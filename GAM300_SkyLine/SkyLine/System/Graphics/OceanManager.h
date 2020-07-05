#pragma once
#include <glm/glm.hpp>
#include "glad.h"
#include "Shader.hpp"
#include "Wave.h"


class OceanManager
{
	// make sure N and M are the same b/c I need a square to have nlogn timee instead of n^2
	int N_;
	int M_;

	// imagine this is the dimension we want to see, just make this a square
	float width_;
	float depth_;

	
	float A_;		  // wave height or amplitude
	float V_;		  // speed
	glm::vec2 omega_; // direction

	glm::vec3* vertexArray_; 
	unsigned * indices_;
	


	Wave * wave_;
	float time_;



	void init();
	
public:
	OceanManager(unsigned power, unsigned width, unsigned depth);
	~OceanManager();
	void makeWave(float dt);

	//for lighting
	float height;
	float heightMax = 0;
	float heightMin = 0;

	unsigned VAO_;
	unsigned VBO_;
	unsigned EBO_;

	unsigned indexSize_;

	float modelScaleMult_;
	float modelScale_;
};

