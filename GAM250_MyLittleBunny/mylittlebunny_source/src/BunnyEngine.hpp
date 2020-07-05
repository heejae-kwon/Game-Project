/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      BunnyEngine.hpp
Purpose:        The main part of our engine.
                Handles creating and destroying stages.
                Switching between play and editor mode.
                Also handles the main game loop.
Language:       C++
Project:        GAM200
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#pragma once

#include <Core/Draw.hpp>
#include <Core/Debugger.hpp>
#include <Core/Event.hpp>
#include <Core/Particle.hpp>
#include <WIP/Physics.hpp>
#include <BaseStage.hpp>

#include <stack>

namespace BE
{
namespace Engine
{

    //!  The BunnyEngine class. 
    /*!
     The BunnyEngine class is simply the starting point for all programs using the BunnyEngine.
     All it does is add stages to it's stack and calls their update function in a loop.
     It also does this for all the cores (physics, draw, event...)
    */
    class BunnyEngine
    {
        // All type redefinitions should be at the start of a class
    public:
        using StageVec = std::vector<Stage::BaseStage::StageSmartPtr>;
    protected:
        using StageStack = std::stack<Stage::BaseStage*>;
        using BunnyEngineSmartPtr = std::unique_ptr<BunnyEngine>;

    public:
        static BunnyEngine* instance(bool debugMode_ = false)  //!< Returns an instance of the class
        {
            static BunnyEngineSmartPtr instance(new BunnyEngine(debugMode_));
            return instance.get();
        }
        ~BunnyEngine();

        void    flushStages();      //!< Clears out the _activeStages stack making sure to call  removeCoreOffset() for each stage.
        /** Function used to add an active stage to the _activeStages
        * Pushes a new stage onto the _activeStages stack.
        * This function is ONLY responsible for calling the stage's start function which then starts all it's actors.
        * The loading of actors is up to the user.
        * When _activeStages is not empty, the pause() function of the the current stage will be called.
        */
        void    pushActiveStage(Stage::BaseStage* stage_, std::string overrideFileName = "");
        void    popActiveStage();   //!< Removes the latest active stage from the stack and if the _activeStages is not empty then the "top" stage's resume() function will be called.
        Stage::BaseStage*   getActiveStage();   //!< Returns the latest stage to be added to the array of stages

        void    run();  //!< Starts the game, loops until QUIT event has been received
        void    update();   //!< Update function used while in editor mode
        void    quit(); //!< Sets isClosing to true

        void    setDebugMode(bool isActive_);
        void    saveSceneState(std::string filename_);   //!< Call this function when you want to save the state of a stage while in debug mode
    protected:
        //
    private:
        BunnyEngine(bool debugMode_ = false);  //!< BunnyEngine's constructor is private as it is a Singleton and should only be accessed through the instance() function.
        /** Function used to seperate actors when we stack stages
        * When we stack a stage on top of another wa may want to seperate the currently loaded actors from the ones we are about load.
        * This function calls the pushNewOffset() function of all affected core, depending on the config of the stage we are loading,
        * the core may or may not seperate the old actors from the new ones
        */
        void    addCoreOffset(Stage::BaseStage::keepPrevActorsOnLoad coreConfig_);
        /** Function used to remove the previous actor seperation in the cores
        * Calls the popPreviousOffset() function of all the cores called in addCoreOffset(...).
        * popPreviousOffset() simply removes the last offset stored.
        * This will be called when poping a stage from the engine stage stack.
        */
        void    removeCoreOffset();
        /** Function used lock the game's framerate
        */
        void frameLock();
    public:
        StageVec        _availableStages;
    protected:
        //
    private:
        bool            _isClosing;             /*!< When set to true the engine will simply quite */
        bool            _debugModeIsActive;     /*!< Is set to true if debug mode is currently active*/
        bool            _sleepIsGranular;        /*!< Is set to true when we succesfully set sleep()'s precision*/

#define monitorRefreshRate 60.0f
#define gameUpdateHz (monitorRefreshRate)
        float targetSecondsPerFrame = 1.0f / gameUpdateHz;

        // EDITOR
        std::vector<Actor*>          _selectedActors;

        // LOGIC
        BE::Timer*      _mainTimer;             /*!< Main timer used by most parts of the engine including game logic */

        // CORES
        Core::Event*     _eventCoreInstance;     /*!< A pointer to the Event core*/
        Core::Debugger*  _debuggerCoreInstance;  /*!< A pointer to the Debugger core*/
        Core::Draw*      _drawCoreInstance;      /*!< A pointer to the Draw core*/
        Core::Physics*   _physicsCoreInstance;   /*!< A pointer to the Physics core*/
		Core::Particle*  _particleCoreInstance;   /*!< A pointer to the Physics core*/

        // STAGES
        StageVec            _activeStages;      /*!< This is where all the loaded stages are stored*/
        Stage::BaseStage*   _firstActiveStage;  /*!< Used when going into debug mode, we reset the stage as it was at the beginning */

        // LOOp
        const bool* _quitEvent; // We get a pointer to a boolean that will be set to true if we receive a QUIT event
        const bool* _pauseEvent; // We get a pointer to a boolean that will be set to true if we receive a QUIT event
        const bool* _unpauseEvent; // We get a pointer to a boolean that will be set to true if we receive a QUIT event
    };
}
}
