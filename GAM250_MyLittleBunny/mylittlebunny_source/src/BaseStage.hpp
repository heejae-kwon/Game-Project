/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      BaseStage.hpp
Purpose:        All other stages inherit this class
Language:       C++
Project:        GAM200
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#pragma once

#include <Actor.hpp>
#include <Props\Props.hh>

#include <memory>
#include <vector>
#include <string>

namespace BE
{
namespace Stage
{

    //!  The BaseStage class. 
    /*!
     The BaseStage class is what enables to end user to have different levels in his game.
     Each stage contains an update() function that will be called each loop and a vector in which are stored all the actors it needs.
    */
    class BaseStage
    {
    // All type redefinitions go here
    public:
        struct keepPrevActorsOnLoad // Determines for each core if it should keep the currently active actors when stacking a new stage or only use the new actors
        {
            bool drawCore;
            bool physicsCore;
            bool particleCore;
        };
        using StageSmartPtr = std::unique_ptr<BaseStage>;

    protected:
        using ActorSmartPtr = std::unique_ptr<Actor>;
        using ActorVector = std::vector<ActorSmartPtr>;
        using PropVec = std::vector<Prop::BaseProp*>;

    public:
        BaseStage(std::string stageFileName_, BaseStage* previousStage_ = nullptr);
        virtual ~BaseStage() = default;

        keepPrevActorsOnLoad&   getCoreConfig();    //!< Returns the core config (should the cores only use the actors from this stage or this one plus the stages before) for this stage

        virtual BaseStage*  cpy() = 0;  //!< Returns a copy of the current scene

        virtual void    start(std::string fileName_ = "") = 0;        //!< Starts the stage, initialise values here
        virtual void    loadProps(std::string fileName_);        //!< Should be called in start(), loads the props (image, audio...) needed by the actors
        virtual void    loadStageFile(std::string fileName_);    //!< Should be called in start(), creates actors by reading data from a .stg file
        virtual void    saveStageFile(std::string fileName_);    //!< Calling this will overwrite the .stg file with the current state of the stage

        Actor*          addActor(Actor* actor_); //!< Adds an actor the vector that store the actors in the stage, you must do this if you want to be sure that the actor is deleted correctly and that it is retrievable with getActor()
        void            removeActor(Actor* actor_); //!< Remove an actor from the array of active actors in the scene
        void            addProp(Prop::BaseProp* prop_);
        void            removeProp(Prop::BaseProp* prop_);

        virtual void    resume() = 0;   //!< Reverses whatever pause() has done
        virtual void    pause() = 0;    //!< When another stage is stacked on top of the current one we may want to pause the various timers we are using.

        virtual void    update(float dt_) = 0;   //!< Game logic goes here

        std::string getStageFileName();
    protected:
        BE::Actor*  getActor(std::string name_);    //!< Searches through the actor and returns the first actor with the same name
    private:
        //

    public:
        //
    protected:
        ActorVector             _actorVec;          /*!< All the actors that will be used in this stage. */
        PropVec                 _propVec;           /*!< The array of props that have been loaded for this stage */
        keepPrevActorsOnLoad    _stageLoadCoreConf; /*!< Determines how the cores should act when loading this stage */
        BaseStage*              _previousStage;     /*!< Pointer that can be set to a previously loaded stage. Can be used to pass data in between stages.*/
    private:
        std::string             _stageFileName;     /*!< The name of the json file to read from and write to.*/
    };

}
}
