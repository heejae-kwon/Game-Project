/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      emptyStage.cpp
Purpose:        This is just used as a quick hack to pause the game when we alt tab
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#include <emptyStage.hpp>

BE::Stage::emptyStage::emptyStage()
    : BaseStage("emptyStage.stg")
{
    // Setting up the core config, by default everything is set to false
    {
        _stageLoadCoreConf.drawCore = true; // We want the draw core to keep drawing whatever was present while we display the confirm action pop up
    }
}

void
BE::Stage::emptyStage::start(std::string fileName_)
{
}

void
BE::Stage::emptyStage::resume()
{
}

void
BE::Stage::emptyStage::pause()
{
}

void
BE::Stage::emptyStage::update(float /*dt_*/)
{
}
