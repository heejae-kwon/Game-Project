#pragma once
#include <glm/glm.hpp>
#include <memory>
#include "Shader.hpp"



class Quad
{

	protected:
	glm::vec3 position_;
	glm::vec3 scale_;
	glm::vec3 rotate_;
	
	//Shader shader_;

	public:
	void bindMesh();
	void draw();

	Quad(const glm::vec3& position);
	~Quad();

	unsigned texture_;
	unsigned VBO_;
	unsigned VAO_;
	unsigned EBO_;
};

