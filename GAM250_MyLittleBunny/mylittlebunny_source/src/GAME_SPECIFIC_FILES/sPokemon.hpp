/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      sPokemon.hpp
Purpose:        This file contain the Options.
Can be used C style with static functions or C++ with methods.
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/
#pragma once

#include <BaseStage.hpp>
#include <Utilities/TimerManager.hpp>

namespace Stage
{
    //!  The sPokemon class. 
    /*!
    The sPokemon class is a Stage.
    It contains its own vector of Actors and its own update function.
    At the moment it does not serve any purpose other than to be used to test out the engine
    */
    class sPokemon : public BE::Stage::BaseStage
    {
    public:
        sPokemon();
        ~sPokemon() override final;

        BaseStage*  cpy() final
        {
            return (new sPokemon());
        }

        void    start(std::string fileName_ = "") final;

        void    resume() final;
        void    pause() final;

        void    update(float dt_) final;
    protected:
        //
    private:
        void healthBarReduction(float dt_);

    public:
        //
    protected:
        //
    private:
        //
        BE::Actor*  _poke1;
        BE::Actor*  _poke2;
        BE::Actor*  _poke2HP;
        int       _currentPoke2HP;
        std::vector<BE::Actor*> _tmpActorVec;
        BE::Actor* _selectedActor;
        bool    btlStartPlay;
        bool    btlEndPlay;
        BE::PropManager::propNamePair* _battleStart;
        BE::PropManager::propNamePair* _battleEnd;
        BE::PropManager::propNamePair* _tackle;
        float   _cooldownTimer;
        std::vector<glm::vec4>   _hPColors;
    };
}

