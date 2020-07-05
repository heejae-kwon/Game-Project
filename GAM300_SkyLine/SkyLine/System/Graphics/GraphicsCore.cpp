#include "GraphicsCore.hpp"
#include "Application.hpp"
#include <memory>
#include "glad.h"
#include <SDL.h>
#include <iostream>
#include "Quad.h"
#include "ShaderType.hpp"
#include "AllShaderClasses.hpp"

// Placeholder testing globals
// Here as example
shared_ptr<Model> testModel;
shared_ptr<Component::Renderable> testRenderable;
Quad * testQuad;

static std::vector<std::string> modelFileNames = 
{
  "Assets/Models/Skybox.model",
  "Assets/Models/BasicIsland.model",
  "Assets/Models/Battleship.model",
  "Assets/Models/Cloud.model",
  "Assets/Models/PlayerPlane.model",
  "Assets/Models/Cylinder.model",
  "Assets/Models/Square.model"
};

static std::vector<std::string> skyboxTextFilename =
{
  "Assets/Skybox/skyboxTest/right.jpg",
  "Assets/Skybox/skyboxTest/left.jpg",
  "Assets/Skybox/skyboxTest/top.jpg",
  "Assets/Skybox/skyboxTest/bottom.jpg",
  "Assets/Skybox/skyboxTest/front.jpg",
  "Assets/Skybox/skyboxTest/back.jpg"
};

static std::vector<std::string> textureFileNames =
{
  "Assets/Textures/billboard5.png",
  "Assets/Textures/cloud.png",
  "Assets/Textures/ocean.png"
};

// This is truly some magical singleton
GraphicsCore * GraphicsCore::instance()  //!< Returns an instance of the class
{
	static std::unique_ptr<GraphicsCore> instance(new GraphicsCore());
	return instance.get();
}

// Constructor stuff
GraphicsCore::GraphicsCore()
{
  if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
  {
    std::cout << "Glad loading failed!" << std::endl;
  }

  modelManager_ = std::make_unique<ModelManager>(modelFileNames);
  renderableManager_ = std::make_unique<RenderableManager>();
  cameraManager_ = std::make_unique<CameraManager>();
  textureManager_ = std::make_unique<TextureManager>();

  shaders_.push_back(std::make_shared<ShaderDefault>("Assets/Shaders/default.vertex", "Assets/Shaders/default.fragment"));
  shaders_.push_back(std::make_shared<ShaderCel>("Assets/Shaders/default.vertex", "Assets/Shaders/cel_shading.fragment"));
  shaders_.push_back(std::make_unique<ShaderOcean>("Assets/Shaders/flat_ocean.vertex", "Assets/Shaders/flat_ocean.fragment"));
  shaders_.push_back(std::make_shared<ShaderSkybox>("Assets/Shaders/skybox.vertex", "Assets/Shaders/skybox.fragment"));

  render_ = std::make_unique<Render>(shaders_);

  testQuad = new Quad (glm::vec3(0.0f, 0.0f, 0.0f));
}

// Destructor, it does nothing
GraphicsCore::~GraphicsCore()
{

}

// Initialization, sets initial OpenGL options
// and initializaes the ModelManager and Shader and texturemanager
void GraphicsCore::Initialize(void)
{
  glViewport(0, 0, 1280, 720);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  //alpha
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  //glClearColor(0.0f,0.0f,0.0f,0.0f);

  // Initialize the model manager
  modelManager_->initialize();

  // Load textures  here
  textureManager_->initializeTextures(textureFileNames);
  textureManager_->loadCubemap(skyboxTextFilename, "SkyboxTest");

  // Debug code, this prints out how many texture units the computer's graphics card can handle
  int texture_units;
  glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &texture_units);
  std::cout << "This computer's graphics card can handle: " << texture_units << " textures in the fragment shader" << std::endl;
  std::cout << "This computer's graphics card can handle at most : " << GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS << " texture units bound total" << std::endl;
}

//All systems are updated every frame
void GraphicsCore::Update(float dt)
{
  // Clear da buffers
  glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  Camera* camera = cameraManager_->getCamera();
  //camera->goTo(glm::vec3(0.0f, 0.0f, 3.0f));

  for (const auto& renderable : renderableManager_->getRenderables_())
  {
    render_->draw(*renderable, *camera);
  }

  render_->drawOcean(*testQuad,*camera);
  // draw skybox last
  render_->drawSkybox(textureManager_->getCubeMapTexture("SkyboxTest")->getID(), *modelManager_->getModel("Skybox"), *camera);

  //update camera manager
  cameraManager_->update(dt);
}