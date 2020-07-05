/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      Actor.hpp
Purpose:        Actor class that contains a collection of components
Language:       C++
Project:        GAM200
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#pragma once

#include <Components/Components.hh>
#include <Utilities/JsonReader.hh>

#include <vector>
#include <memory>

namespace BE
{
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
        */
        static Actor* createActor(std::string name_, bool isActive_, Json::Value* data_ = nullptr)
        {
            Actor* newActor = new Actor();

            newActor->_name = name_;
            newActor->_isActive = isActive_;
            newActor->addComponent<Component::Transform>();

            if (data_ != nullptr)
            {
                newActor->getComponent<Component::Transform>()->getData(*data_);

                Json::Value actorData = (*data_)["Actors"][name_];
                std::vector<std::string> componentArray = BE::JsonReader::getArrayAsString(actorData["Components"]);

                for (auto & component : componentArray)
                {
                    if (component == BE::Component::TypeStr[BE::Component::DISPLAY])
                    {
                        newActor->addComponent<BE::Component::Display>();
                    }
                    else if (component == BE::Component::TypeStr[BE::Component::CAMERA])
                    {
                        newActor->addComponent<BE::Component::Camera>();
                    }
                    else if (component == BE::Component::TypeStr[BE::Component::RIGIDBODY] ||
                        component == BE::Component::TypeStr[BE::Component::CIRCLE_COLLIDER])
                    {
                        // This is done to make sure that the actors will alwayse have a circle collider along with their rigidbody.
                        newActor->addComponent<BE::Component::CircleCollider>();
                        newActor->addComponent<BE::Component::Rigidbody>();
                    }
					else if (component == BE::Component::TypeStr[BE::Component::PARTICLEEMITTER])
					{
						newActor->addComponent<BE::Component::ParticleEmitter>();
					}
                    else if (component == BE::Component::TypeStr[BE::Component::GAMEPLAY])
                    {
                        newActor->addComponent<BE::Component::Gameplay>();
                    }
                }
            }


            return newActor;
        }

        /** A Templated function that adds a component to the Actor.
        * If the Actor does not already have a component of the same type then it returns a pointer to the newly created component
        * otherwise the function returns a nullptr.
        */
        template<typename TComponent>
        TComponent* addComponent()
        {
            if (getComponent<TComponent>() == nullptr)
            {
                BaseComponentSmartPtr newComponent = std::unique_ptr<TComponent>(new TComponent(this));

                _componentVec.push_back(std::move(newComponent));

                return static_cast<TComponent*>(_componentVec.back().get());
            }
            return nullptr;
        }
 
        /** A Templated function that searches for a specific component type among those stored in the actor.
        * If it finds one then it retrurns a pointer to that component.
        * otherwise it returns a nullptr.
        */
        template<typename TComponent>
        TComponent* getComponent()
        {
            for (auto const & component : _componentVec)
            {
                if (component && component->hashId == TComponent::identifier)
                {
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

            for (auto const & component : _componentVec)
            {
                if (component && component->hashId == TComponent::identifier)
                {
                    std::swap(_componentVec[i], _componentVec.back());  // We move the pointer to the end of the vector
                    _componentVec.pop_back();                           // and then remove it from the vector
                    return;
                }
                ++i;
            }
        }

        void    loadComponents(Json::Value& data_);
        void    saveComponents(Json::Value& data_);
        void    drawComponentData();
    protected:
        //
    private:
        //

    public:
        bool        _isActive;      /*!< Can be used by Core's to determine if an actor should be processed or not */
        bool        _isSelected;    /*!< Is set to truze if the actor is currently been selected in the editor mode */
        bool        _savedIsActive; /*!< Value used when reseting the entity to it's original state */
        std::string _name;
        bool        _saveActor;
    protected:
        //
    private:
        std::vector<BaseComponentSmartPtr> _componentVec;   /*!< The container that stores the pointers to all the components that make up the actor*/
    };
}