#pragma once
#include <string>
#include <vector>
#include "JsonWriter.hh"
#include "JsonReader.hh"
#include "Components.hh"
#include "ComponentType.hh"
//!  Actor class 
    /*!
     Anything that is an active part of the game is an actor (player, background, hu.
     The Actor class is a glorified container that stores Components structs.
     It also contains a few functions that let's us add, remove and search for a component that is stored in the Actor class.
    */
class Actor
{
		// All type redefinitions go here
public:
		using BaseComponentSmartPtr = std::unique_ptr<Component::BaseComponent>;

public:
		Actor();
		~Actor() = default;

		/** A static factory function to create Actors.
		* Takes a string (name) and boolean (isActive) as params
		THIS SHOULD BE ALWAYS UPDATED WHEN NEW COMPONET IS ADDED
		*/
		static Actor* CreateActor(std::string name_ = "", bool isActive_ = 0, Json::Value* data_ = nullptr);


		/** A Templated function that adds a component to the Actor.
		* If the Actor does not already have a component of the same type then it returns a pointer to the newly created component
		* otherwise the function returns a nullptr.
		*/
		template<typename TComponent>
		TComponent* addComponent()
		{
	//			if (getComponent<TComponent>() == nullptr)
				{
						BaseComponentSmartPtr newComponent = std::unique_ptr<TComponent>(new TComponent(this));

						componentVec.push_back(std::move(newComponent));

						return static_cast<TComponent*>(componentVec.back().get());
				}
	//			return nullptr;
		}

		/** A Templated function that searches for a specific component type among those stored in the actor.
		* If it finds one then it retrurns a pointer to that component.
		* otherwise it returns a nullptr.
		*/
		template<typename TComponent>
		TComponent* getComponent()
		{
				for (auto const & component : componentVec)
				{

						if (component && component->m_hashId == TComponent::identifier) {
								///*             {*/
								//													if (component){*/
								return static_cast<TComponent*>(component.get());
						}
				}
				return nullptr;
		}

		/** A Templated function that searches for a specific component type among those stored in the actor and removes it if found.
		*/
		template<typename TComponent>
		void removeComponent()
		{
				int i = 0;

				for (auto const & component : componentVec)
				{
						if (component && component->m_hashId == TComponent::identifier)
						{
								std::swap(componentVec[i], componentVec.back());  // We move the pointer to the end of the vector
								componentVec.pop_back();                           // and then remove it from the vector
								return;
						}
						++i;
				}
		}

/*Load Componetns data from file*/
		void LoadComponents(Json::Value & data_);

/*Save Componetns data from file*/
		void    SaveComponents(Json::Value& data_);

/*Draw Componetns data to IMGUI*/
		void    drawComponentData();
protected:
		//
private:
		//

public:
		bool        isActive;      /*!< Can be used by Core's to determine if an actor should be processed or not */
   bool        isPaused;    /*!< is this actor in paused level*/
		bool        _isSelected;    /*!< Is set to truze if the actor is currently been selected in the editor mode */
//  bool        _savedIsActive; /*!< Value used when reseting the entity to it's original state */
		std::string name;
		int ID;

		bool        saveActor;
private:
		std::vector<BaseComponentSmartPtr> componentVec;   /*!< The container that stores the pointers to all the components that make up the actor*/

};


