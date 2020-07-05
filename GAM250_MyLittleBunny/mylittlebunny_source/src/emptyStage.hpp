/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      emptyStage.hpp
Purpose:        This is just used as a quick hack to pause the game when we alt tab
Language:       C++
Project:        GAM200
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#pragma once

#include <BaseStage.hpp>

namespace BE
{
namespace Stage
{
    //!  The emptyStage class. 
    /*!
    The emptyStage class is a Stage.
    This only exists as a hacky fix for pausing the game audio
    */
    class emptyStage : public BE::Stage::BaseStage
    {
    public:
        emptyStage();
        ~emptyStage() = default;

        BaseStage*  cpy() final
        {
            return (new emptyStage());
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
        //
    };
}
}
