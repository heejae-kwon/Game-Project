#pragma once
#include "Particle.h"
#include <vector>
//#include "Shader.hpp"
#include "AllShaderClasses.hpp"

class ParticleManager
{
public:
	ParticleManager();
	~ParticleManager();

	int texture;
	unsigned VAO;

	unsigned maxParticles_ = 500;
	unsigned lastUsedParticle = 0;
	std::vector<Particle> particles_;

	//Shader particleShader;
	//std::shared_ptr<Shader> ourShader_;
	//ShaderParticle* shader = static_cast<ShaderParticle*>(&*shaders_[ShaderType::Particle]);

	void update(float dt);
	unsigned FirstUnusedParticle();
	void RespawnParticle(Particle &particle, glm::vec3& parentPosition, glm::vec3 parentVelocity, glm::vec3 offset);

	void render();

	void init();

	void Draw(const glm::mat4& view, const glm::mat4& proj);
};

