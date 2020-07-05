#include "Render.hpp"
#include <iostream>
#include <glm/gtx/transform.hpp>
#include <iomanip>
#include "AllShaderClasses.hpp"
#include "ShaderType.hpp"

int SCR_WIDTH = 1280;
int SCR_HEIGHT = 720;

float FOV = 65.0f;

glm::vec4 testLightPosition(0.0f, 100.0f, 450.0f, 1.0f);
glm::vec3 testLightIntensity(1.0f, 1.0f, 1.0f);
glm::vec3 testAmbient(20.0f, 0.0f, 0.0f);
glm::vec3 testDiffuse(1.0f, 1.0f, 1.0f);

void Render::drawOcean(const Quad& ocean, const Camera& camera)
{

  ShaderOcean* oceanShader = static_cast<ShaderOcean*>(&*shaders_[ShaderType::Ocean]);
  oceanShader->use();
  oceanShader->setMat4View(camera.GetViewMatrix());
  oceanShader->setMat4Projection(camera.proj_);
	glm::mat4 scale;
	glm::mat4 rotate;
	glm::vec3 pos;
	
	glm::mat4 model;
	//model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // Translate it down a bit so it's at the center of the scene
	model = glm::translate(model, glm::vec3(0.0f, -07.60f, 0.0f)); // Translate it down a bit so it's at the center of the scene
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(10000.2f, 10000.2f, 10000.2f));	// It's a bit too big for our scene, so scale it down
	//model = glm::scale(model, glm::vec3(100.2f, 100.2f, 100.2f));	// It's a bit too big for our scene, so scale it down
  oceanShader->setMat4Model(model);

  // Bind Textures using texture units	

  //unsigned texLoc = glGetUniformLocation(oceanShader->getProgram(), "texture1");
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, ocean.texture_);
  glUniform1i(glGetUniformLocation(oceanShader->getProgram(), "texture1"), 0);							 //
  																 //a
  

  
					 //a
    

	
	glBindVertexArray(ocean.VAO_);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Render::drawSkybox(unsigned int cubeMapTextureID, Model& skyboxModel, const Camera& camera)
{
  glDisable(GL_CULL_FACE);
  glDepthFunc(GL_LEQUAL);
  ShaderSkybox* skyboxShader = static_cast<ShaderSkybox*>(&*shaders_[ShaderType::Skybox]);
  skyboxShader->use();

  // Strip translation component
  glm::mat4 view = glm::mat4(glm::mat3(camera.GetViewMatrix()));

  skyboxShader->setMat4View(view);
  skyboxShader->setMat4Projection(camera.proj_);

  // TO DO: Replace this placeholder code with something that handles managing OpenGL texture units
  glActiveTexture(GL_TEXTURE0); // activate texture unit 0
  glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTextureID); // bind the cubemap to the above texture unit
  skyboxShader->setTextureUnit(0); // Sets the OpenGL sampler cube to use texture unit 0

  // skybox model should only have one mesh, it's just a cube
  auto const &mesh = skyboxModel.getMeshes().at(0);
  glBindVertexArray(mesh.getVAO());
  glDrawElements(GL_TRIANGLES, mesh.numberIndices(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
  glDepthFunc(GL_LESS);
  glEnable(GL_CULL_FACE);
}

void Render::draw(const Component::Renderable& renderable, const Camera& camera)
{
  ShaderCel* celShader = static_cast<ShaderCel*>(&*shaders_[ShaderType::Cel]);
  celShader->use();
  
  // Model = S * R * T

  //SCALE
  glm::mat4 model = glm::scale(renderable.m_owner->getComponent<Component::Transform>()->getScale());

  //ROTATE
  glm::quat rendQuat = renderable.m_owner->getComponent<Component::Transform>()->getOrientation();
  model = glm::toMat4(rendQuat) * model;

  //TRANSLATE
  model = glm::translate(renderable.m_owner->getComponent<Component::Transform>()->getPosition()) * model;

  //VIEW
  glm::mat4 view = camera.GetViewMatrix();
  glm::mat4 projection = camera.proj_;

  celShader->setMat4Model(model);
  celShader->setMat4View(view);
  celShader->setMat4Projection(projection);

  // Lighting uniforms
  glm::vec4 lightInViewSpace = view * testLightPosition; // transform light position to view space
  celShader->setLightPosition(lightInViewSpace);
  celShader->setLightIntensity(testLightIntensity);
  celShader->setAmbient(testAmbient);
  celShader->setDiffuse(testDiffuse);
  celShader->setBoolTextured(false);

  if (renderable.getTexture() != nullptr) // renderable has a texture on it
  {
    celShader->setBoolTextured(true); // tell shader program that we will need to use textures
    glActiveTexture(GL_TEXTURE0); // activate texture unit 0, we can just re-use this texture unit for now
    glBindTexture(GL_TEXTURE_2D, renderable.getTexture()->getID()); // bind the texture associated with the ID
    celShader->setTextureUnit(0); // Sets the OpenGL sampler cube to use texture unit 0
  }

  // Main draw call
  // Gets a reference to each mesh in the vector, prevents copy
  for (auto const &mesh : renderable.getModel()->getMeshes())
  { 
    // If we already had the VAO we need bound, don't bind it again
    if (previousVAO_ != mesh.getVAO())
      glBindVertexArray(mesh.getVAO());

    // Store ID of currently bound VAO to compare to next mesh's VAO
    previousVAO_ = mesh.getVAO();

    // Draw using index mode
    glDrawElements(GL_TRIANGLES, mesh.numberIndices(), GL_UNSIGNED_INT, 0);
  }
  previousVAO_ = 0;
  glBindVertexArray(0); // proper practice is to unbind VAO at the end
  
  /*
  GLenum err;
  while ((err = glGetError()) != GL_NO_ERROR) {
  cerr << "OpenGL error: " << err << endl;
  }
  */
}