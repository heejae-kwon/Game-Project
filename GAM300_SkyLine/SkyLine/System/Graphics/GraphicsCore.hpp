#pragma once
#include "BaseCore.hpp"
#include "Render.hpp"
#include <memory>
#include <vector>

#include "ModelManager.h"
#include "TextureManager.h"
#include "RenderableManager.h"
#include "CameraManager.h"
#include "ShaderType.hpp"

/*

TO DO:
Make a hierarchy. A scene tree, which is the hierarchical view of the world (for handling hierarchical animation).
Make a spatial partitioning scheme. A spatial graph, which is the spatial view of the world (for grouping nearby objects together, for culling).
Make a scene manager. A render graph, which is the state optimal view of the world (for grouping objects by states, such as shaders, materials, etc).

***** Implement batching somehow to minimize switching VAOs *****

High level view of how stuff's rendered:

initialization:
  for each batch
    generate, store, and bind a VAO
    bind all the buffers needed for a draw call
    unbind the VAO

main loop/whenever you render:
  for each batch
    bind VAO
    glDrawArrays(...); or glDrawElements(...); etc.
  unbind VAO

*/

// This is the high level Graphics system, not much here and it's all self explanatory
class GraphicsCore : public BaseCore
{
  public:
	  

    // Static singleton code, returns the GraphicsCore object
    static GraphicsCore* instance();

    GraphicsCore();

    ~GraphicsCore();

    //Initialize the GraphicsCore. Important to call this only once!
    void Initialize(void) override;

    //All systems are updated every frame
    void Update(float dt) override;

    // Return the Model Manager, this is a raw pointer because it should only be used to retrieve models
    // GraphicsCore is the owner for the ModelManager for now
    ModelManager* getModelManager() { return &(*modelManager_); }
    TextureManager* getTextureManager() { return &*(textureManager_); }
    RenderableManager* getRenderableManager() { return &(*renderableManager_); }
	  CameraManager* getCameraManager() { return &(*cameraManager_); }

    std::shared_ptr<Shader> getShader(ShaderType shaderType) { return shaders_[shaderType]; }

  private:
    std::unique_ptr<Render> render_;  // For now the render object is also singleton (only one), this may change in the future
    std::unique_ptr<ModelManager> modelManager_;
    std::unique_ptr<RenderableManager> renderableManager_;
    std::unique_ptr<TextureManager> textureManager_;
    std::unique_ptr<CameraManager> cameraManager_;

    std::vector<std::shared_ptr<Shader> > shaders_;
    //std::shared_ptr<Shader> skyboxShader_;
    //std::shared_ptr<Shader> quadShader_;
};
