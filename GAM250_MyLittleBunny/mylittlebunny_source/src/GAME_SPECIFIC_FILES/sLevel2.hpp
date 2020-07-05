#pragma once

#include <BaseStage.hpp>
#include <Utilities/TimerManager.hpp>
#include <WIP/Keyboard.hpp>
#include <GAME_SPECIFIC_FILES\LevelSetting.hpp>
#include <GAME_SPECIFIC_FILES\oPlayer.hpp>
#include <GAME_SPECIFIC_FILES\oEnemy.hpp>
#include <GAME_SPECIFIC_FILES\oPlanet.hpp>
#include <GAME_SPECIFIC_FILES\oCamera.hpp>


namespace
{

}

namespace Stage
{
    //!  The sLevel2 class. 
    /*!
     The sLevel2 class is a Stage.
     It contains its own vector of Actors and its own update function.
     At the moment it does not serve any purpose other than to be used to test out the engine
    */
	class sLevel2 : public BE::Stage::BaseStage
    {
    public:
        sLevel2();
        ~sLevel2() = default;

        BaseStage*  cpy() final
        {
            return (new sLevel2());
        }

        void    start(std::string fileName_ = "") final;

        void    resume() final;
        void    pause() final;

		float   pointObj(BE::Actor* act1, BE::Actor* act2);

        void    update(float dt_) final;
		void	WinCondition(LevelSetting& levelSetting, float dt);
		void    LoseCondition(LevelSetting& levelSetting, float dt);

		void ShootPlayer(float dt);

	protected:
        //
    private:
        //

    public:
        //
    protected:
        //
    private:
        //
		BE::Actor*  _player;
		BE::Actor*  _camera;
		BE::Actor*  _backStar; // Useless
		BE::Actor*  _waveAlarm;
		BE::Actor*  _1to3Button;
		BE::Actor*  _3to5Button;
		BE::Actor*  _hud;//compass(arrow)
		BE::Actor*  _dangerPoint;//where it is pointing at
		BE::Actor* _superstandHUD;
		BE::Actor* _xKey;
		BE::Actor* _feverTime;
		oCamera m_camera;

		//BE::Actor* _LightHud1;
		//BE::Actor* _LightHud2;
		//BE::Actor* _LightHud3;

		Player m_player;
		
		LevelSetting LevelSetting1;
		float winTimer;
		float loseTimer;

	};


}
