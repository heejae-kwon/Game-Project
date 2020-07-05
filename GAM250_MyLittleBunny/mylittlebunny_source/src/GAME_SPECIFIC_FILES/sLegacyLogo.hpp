/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      sLegacyLogo.hpp
Purpose:        create the logo stage.
Language:       C++
Project:        GAM250
Author:         Name : Wonjae Jung
Email:          wonjae0925@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/
#pragma once

#include <BaseStage.hpp>
#include <Utilities/TimerManager.hpp>

namespace Stage
{
    //!  The sLegacyLogo class. 
    /*!
     The sLegacyLogo class is a Stage.
     This is a recreation of our old logo presentaion stage with the new architecture.
    */
    class sLegacyLogo : public BE::Stage::BaseStage
    {
    public:
        sLegacyLogo();
        ~sLegacyLogo() = default;

        BaseStage*  cpy() final
        {
            return (new sLegacyLogo());
        }

        void    start(std::string fileName_ = "") final;

        void    resume() final;
        void    pause() final;

        void    update(float dt_) final;
    protected:
        //
    private:
        //

    public:
        //
    protected:
        //
    private:
        float       _elapsedTime;    /*!< [TEMPORARY] Used for testing purposes, to check if state stacking works.*/

        BE::Actor*  _digiLogo;
        BE::Actor*  _fmodLogo;
        BE::Actor*  _teamLogo;
        BE::Actor*  _gamepadLogo;
		BE::Actor*  _story;
		BE::Actor*  _storyToStart;
		
	    BE::PropManager::propNamePair* sndDigilogo;
	    BE::PropManager::propNamePair* sndStory;
					bool b_phaseout;
				bool b_sound;

    };
}

