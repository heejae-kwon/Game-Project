#pragma once

#include <BaseStage.hpp>
#include <Utilities/TimerManager.hpp>

namespace Stage
{
    //!  The sLevel1 class. 
    /*!
     The sLevel1 class is a Stage.
     It contains its own vector of Actors and its own update function.
     At the moment it does not serve any purpose other than to be used to test out the engine
    */
    class sLevel1 : public BE::Stage::BaseStage
    {
    public:
        sLevel1(std::string fileName_ = "");
        ~sLevel1() = default;

        BaseStage*  cpy() final
        {
            return (new sLevel1(fileName));
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
		BE::Actor* player;
		BE::Actor* hud;
        std::string fileName = "";
    };
}

