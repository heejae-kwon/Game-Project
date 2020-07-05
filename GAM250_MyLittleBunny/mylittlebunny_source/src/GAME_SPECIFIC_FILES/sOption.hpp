#pragma once
/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:    sOption.hpp
Purpose:       This file contain the Options.
Can be used C style with static functions or C++ with methods.
Language:     C++
Project:         GAM250
Author:         Name : Jihwan Oh
Email:            dkdkdkdudrn@gmail.com
date:			   2017.06.16
----------------------------------------------------------------------------*/
#include <BunnyEngine.hpp>
#include <BaseStage.hpp>
#include <Utilities/TimerManager.hpp>

namespace Stage
{
    //!  The sOption class. 
    /*!
     The sOption class is a Stage.
     It contains its own vector of Actors and its own update function.
     It is used as a popup when trying to do a destructive action (quitting game, returning to menu)
     NOTE: Currently, there is no way of knowing what the "result" of the ActionConfirm was. So that will need to be adressed
    */
    class sOption : public BE::Stage::BaseStage
    {
    public:
        sOption();
        ~sOption() = default;

        BaseStage*  cpy() final
        {
            return (new sOption());
        }

        void    start(std::string fileName_ = "") final;

        void    resume() final;
        void    pause() final;

        void    update(float dt_) final;
					
    protected:
        //
    private:
        //
			void turnoffMusicSounds(void);
			void turnoffAllSounds(void);

			void turnonMusicSounds(void);

			void turnonAllSounds(void);
							

    public:
        //
    protected:
        //
    private:
							BE::PropManager::propNamePair*	sndBG1;
						BE::PropManager::propNamePair*		sndDigilogo;
						BE::PropManager::propNamePair*		sndFly;
						BE::PropManager::propNamePair*		sndHit;
						BE::PropManager::propNamePair*		sndJump;
						BE::PropManager::propNamePair*		sndLose;
						BE::PropManager::propNamePair*		sndMenu;
						BE::PropManager::propNamePair*		sndSpecial;
						BE::PropManager::propNamePair*		sndStation;
						BE::PropManager::propNamePair*		sndWin;

        BE::Actor*  _starCursor;
        BE::Actor*  _turnonSound;

        int buttonNum;
								bool b_musicoff;
    };
}