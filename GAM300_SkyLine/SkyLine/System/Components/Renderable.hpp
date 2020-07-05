#pragma once
#include "Model.hpp"
#include "Texture.h"
#include "BaseComponent.hpp"
#include "Transform.hpp"
#include <memory>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "Actor.hpp"

//test
// Renderable is a Component that allows a gameobject to render something
// Renderable needs to be given a model (using ModelManager)
// in order to render anything
using namespace std;
//namespace Component
//{
namespace Component {
		class Renderable : public BaseComponent {
		public:
				//result = perspective * parent * translate * rotate * point translate * scale * vertex
				COMPONENT_HASH(Renderable)
						Renderable(Actor* owner_); // not all Renderables will have models

						// Construct a Renderable by directly giving it a model
				Renderable(shared_ptr<Model> model);

				// Construct a Renderable by directly giving it a model and texture
				Renderable(shared_ptr<Texture> texture);

				// Default destructor, doesn't do anything
				~Renderable();

				// Setters, generally don't use these and instead just construct a Renderable using the constructors
				void setModel(shared_ptr<Model> model);

				void setTexture(shared_ptr<Texture> texture);

				// Renderable should not be doing anything during update
				void Update(float dt);

				// Return the model this object is using
				const Model* getModel() const;

				// Return the texture this object is using
				const Texture* getTexture() const;

				void    getData(Json::Value& data_)     final;
				void    writeData(Json::Value& data_)   final;
				void    drawData();

		private:
				Model* model_;
				Texture* texture_;
		};
}
//}