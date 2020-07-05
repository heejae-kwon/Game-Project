#include "Renderable.hpp"
#include "GraphicsCore.hpp"
#include <imgui.h>

 Component::Renderable::Renderable(Actor * owner_) : /*BaseComponent(0)*/ model_(nullptr)
{
	m_owner = owner_;
  m_type = Component::Type::RENDERABLE;
	m_hashId = identifier;

}

	// Construct a Renderable by directly giving it a model and texture

 Component::Renderable::Renderable(shared_ptr<Texture> texture) : texture_(&(*texture)) {}

	// Default destructor, doesn't do anything


	// Setters, generally don't use these and instead just construct a Renderable using the constructors

	void Component::Renderable::setModel(shared_ptr<Model> model)
	{
			model_ = model.get();
	}

	void Component::Renderable::setTexture(shared_ptr<Texture> texture)
	{
			texture_ = texture.get();
	}

	// Renderable should not be doing anything during update

	void Component::Renderable::Update(float /*dt*/)
	{
	}

	// Setters, generally don't use these and instead just construct a Renderable using the constructors

	// Construct a Renderable by directly giving it a model

  Component::Renderable::Renderable(shared_ptr<Model> model) : model_(model.get()) { }


	// Return the model this object is using

const Model * Component::Renderable::getModel() const { return model_; }


	// Return the texture this object is using

const Texture * Component::Renderable::getTexture() const { return texture_; }

void Component::Renderable::getData(Json::Value & /*data_*/)
{
}

void Component::Renderable::writeData(Json::Value & /*data_*/)
{
}

void Component::Renderable::drawData()
{
		if (ImGui::CollapsingHeader("Rendarable"))
		{
				//ImGui::PushItemWidth(160);
				//{
				//	ImGui::InputFloat("Some value", &someVal, 1.f, 10.f, 2);
				//}
				//ImGui::PopItemWidth();
		}
}

// Destructor
Component::Renderable::~Renderable()
{
		GraphicsCore::instance()->getRenderableManager()->removeRenderable(*this);
}
