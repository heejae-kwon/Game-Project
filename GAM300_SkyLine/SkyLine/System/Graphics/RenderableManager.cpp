#include "RenderableManager.h"

// Add a new renderable for it to manage

 void RenderableManager::addRenderable(Component::Renderable & renderable)
{
		renderables_.push_back(&renderable);
}

// Return the vector of renderables this manager is managing

 const std::vector<Component::Renderable*>& RenderableManager::getRenderables_() const
{
		return renderables_;
}

// Remove the pointer that's pointing to the passed in renderable object

void RenderableManager::removeRenderable(Component::Renderable & renderable)
{
		for (int i = 0; i < renderables_.size(); ++i)
		{
				if (&*(renderables_[i]) == &renderable)
				{
						renderables_.erase(renderables_.begin() + i);
				}
		}
}
