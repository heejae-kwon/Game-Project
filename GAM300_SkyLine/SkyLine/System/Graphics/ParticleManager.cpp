#include "ParticleManager.h"
#include <random>
#include "glad.h"

ParticleManager::ParticleManager()
{
	for (unsigned int i = 0; i < maxParticles_; ++i)
		particles_.push_back(Particle(i));
}


ParticleManager::~ParticleManager()
{
}


void ParticleManager::update(float dt)
{
	unsigned newParticles = 2;
	
	for (unsigned i = 0; i < newParticles; ++i)
	{
		int unusedParticle = FirstUnusedParticle();
		unusedParticle;
		//RespawnParticle(particles_[unusedParticle], object, offset);
	}
	
	// update all particles
	for (unsigned i = 0; i < newParticles; ++i)
	{
		Particle &p = particles_[i];//particle we update
		p.life_ -= dt;              // update life
		if (p.life_ > 0.0f)
		{
			p.position_ -= p.velocity_ * dt;
			p.color_.a -= dt * 2.5f; // alpha decay
		}
	}

}

unsigned ParticleManager::FirstUnusedParticle()
{
	// get last particle used
	for (unsigned i = lastUsedParticle; i < maxParticles_; ++i)
	{
		if (particles_[i].life_ <= 0.0f)
		{
			lastUsedParticle = i;
			return i;
		}
	}

	// just brut e force it
	for (unsigned i = 0; i < lastUsedParticle; ++i)
	{
		if (particles_[i].life_ <= 0.0f)
		{
			lastUsedParticle = i;
			return i;
		}
	}

	lastUsedParticle = 0;
	return 0;

}

//void ParticleManager::RespawnParticle(Particle &particle, glm::vec3& parentPosition, glm::vec3 parentVelocity, glm::vec3 offset)
//{
//	float random = ((float)(rand() % 100) - 50) * 0.1f;
//	float rColor = 0.5f + ((rand() % 100) / 100.0f);
//	particle.position_ = parentPosition + random + offset;
//	particle.color_ = glm::vec4(rColor,rColor,rColor,1.0f);
//	particle.life_ = 1.0f;
//	particle.velocity_ = parentVelocity * 0.1f;
//
//}

void ParticleManager::RespawnParticle(Particle &particle, glm::vec3& parentPosition, glm::vec3 parentVelocity, glm::vec3 offset)
{
	GLfloat random = ((rand() % 100) - 50) / 20.0f;
	GLfloat rColor = 0.2f + ((rand() % 100) / 100.0f);
	GLfloat gColor = 0.3f + ((rand() % 100) / 100.0f);
	GLfloat bColor = 0.5f + ((rand() % 100) / 100.0f);
	particle.position_ = parentPosition + glm::vec3(random) + offset;
	particle.color_ = glm::vec4(rColor, gColor, bColor, 1.0f);
	particle.life_ = 1.0f;
	particle.velocity_ = parentVelocity * 0.1f;
}

void ParticleManager::render()
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//particleShader.use();
	for (Particle& particle : particles_)
	{
		if (particle.life_ > 0.0f)
		{
			//particleShader.setVec3("offset", particle.position_);
			//particleShader.setVec4("color", particle.color_);
			//particleTexture.Bind();
			//glBindVertexArray(particleVAO);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
	}
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}

void ParticleManager::init()
{
	GLuint VBO;
	GLfloat particle_quad[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};

	////=========
//GLfloat particle_quad[] = {
//   // positions          // colors           // texture coords
//   0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f, // top right
//   0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f, // bottom right
//  -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
//  -0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f  // top left 
//};



	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(this->VAO);
	// Fill mesh buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);
	// Set mesh attributes

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	// Create this->amount default particle instances
	for (GLuint i = 0; i < this->maxParticles_; ++i)
		this->particles_.push_back(Particle(i));
}




//// Stores the index of the last particle used (for quick access to next dead particle)
//GLuint ParticleManager::FirstUnusedParticle()
//{
//	// First search from last used particle, this will usually return almost instantly
//	for (GLuint i = lastUsedParticle; i < this->maxParticles_; ++i) {
//		if (this->particles_[i].life_ <= 0.0f) {
//			lastUsedParticle = i;
//			return i;
//		}
//	}
//	// Otherwise, do a linear search
//	for (GLuint i = 0; i < lastUsedParticle; ++i) {
//		if (this->particles_[i].life_ <= 0.0f) {
//			lastUsedParticle = i;
//			return i;
//		}
//	}
//	// All particles are taken, override the first one (note that if it repeatedly hits this case, more particles should be reserved)
//	lastUsedParticle = 0;
//	return 0;
//}

void ParticleManager::Draw(const glm::mat4& view, const glm::mat4& proj)
{
	if (view == proj)
		return;
	//// Use additive blending to give it a 'glow' effect
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//
	//this->shader.use();
	//for (Particle particle : this->particles)
	//{
	//	if (particle.Life > 0.0f)
	//	{
	//		this->shader.setMat4("projection", proj);
	//		this->shader.setMat4("view", view);

	//		this->shader.setVec4("color", particle.Color);
	//		this->shader.setVec3("offset", particle.Position);
	//		glBindTexture(GL_TEXTURE_2D, texture);//this->texture.Bind();
	//		glBindVertexArray(this->VAO);
	//		glDrawArrays(GL_TRIANGLES, 0, 6);
	//		glBindVertexArray(0);
	//	}
	//}
	//// Don't forget to reset to default blending mode
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}