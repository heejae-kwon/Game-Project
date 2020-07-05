#pragma once
#include "Shader.hpp"
#include "Renderable.hpp"
#include "CameraManager.h"
#include "Quad.h"

class Render {
  public:
    // Constructor and destructor
    Render(std::vector<std::shared_ptr<Shader> >& shaders) : shaders_(shaders)
    {}
    ~Render() {}
    
    void drawSkybox(unsigned int cubeMapTextureID, Model& skyboxModel, const Camera& camera);
	  void drawOcean(const Quad& Ocean, const Camera& camera);

    // Takes a single renderable object and renders it. See Renderable.hpp
    void draw(const Component::Renderable& renderableObject, const Camera& camera);
  private:
    std::vector<std::shared_ptr<Shader> >& shaders_;
    unsigned int previousVAO_;
};