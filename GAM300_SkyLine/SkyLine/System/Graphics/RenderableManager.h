#pragma once
#include <vector>
namespace Component {
		class Renderable;
}

// This class holds weak pointers to renderable components so the draw operation can be done independently of game logic, does not hold ownership of Renderables
class RenderableManager {
  public:
    RenderableManager() { }

    // Add a new renderable for it to manage
				void addRenderable(Component::Renderable& renderable);

    // Return the vector of renderables this manager is managing
				const std::vector<Component::Renderable* >& getRenderables_() const;

  private:
    std::vector<Component::Renderable* > renderables_;

    friend class Component::Renderable;
    // Remove the pointer that's pointing to the passed in renderable object
				void removeRenderable(Component::Renderable& renderable);

};

