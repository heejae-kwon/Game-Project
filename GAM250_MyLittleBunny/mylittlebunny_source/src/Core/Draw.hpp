/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      Draw.hpp
Purpose:        Draw is the core in charge of rendering
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#pragma once

#include <Core/BaseCore.hpp>

#include <glm/glm.hpp>

namespace BE
{
namespace Core
{

    //!  The BunnyEngine's Draw Core class. 
    /*!
     The Draw class is in charge of drawing images to our screen.
     The way it works is that we feed it Actors that have a Draw component
     and the Draw core processes these if needed (discard some if they are out of the camera's range for example)
     and calls the appriopriate functions to render them to the screen.
    */
    class Draw : public BaseCore
    {
        // All type redefinitions go here
    protected:
        using DrawSmartPtr = std::unique_ptr<Draw>;

    public:
        static Draw*    instance() //!< Returns an instance of the class
        {
            static DrawSmartPtr instance(new Draw());
            return instance.get();
        }
        ~Draw() = default;

        // These 3 should be automatically called every loop
        void            startNewFrame() final;  //!< This should be used to setup anything that is essential before data starts getting processed (ex: clearing the screen buffer)
        void            update(float dt_) final;  //!< All the data get's processed in this funtrion (There will be a loop in this function for sure)
        void            endOfFrame() final;  //!< Once all the data processing is done we call the final functions if needed (ex: flipping the screen buffer)

        void            registerActor(Actor* actor_) final;
        void            addCamera(Actor* actor_);   //!< Add an actor that will serve as the camera for the Draw Core
        Actor*          getCurrentCamera();         //!< Returns the currently active camera
        void            removeCurrentCamera();   //!< Remove the top camera from the stack
        void            setClearBufferColor(glm::vec3 color_); //!< DEPRECATED because this doesn't work with letterboxing
        Actor*          checkSpriteOverlap(glm::vec4 point_);
        void            updateSort();
        void            resetSelected();
    protected:
        //
    private:
        Draw(); //!< Draw's constructor is private as it is a Singleton and should only be accessed through the instance() function
        bool                    isOnScreen(Actor* actor_);
        Component::Display *    getComponent(Actor *actor_); //!< This exists because now the draw core can have actors that have a Display component OR a ParticleEmitter component (that contains a Display comp)

    public:
        //
    protected:
        //
    private:
        std::stack<Actor*>  _cameraStack;
        glm::vec3           _clearBufferCol;
    };
}
}
