/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      AudioAbst.cpp
Purpose:        The abstraction for the audio library we use (in this case FMOD)
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#include <Abstractions/AudioAbst.hpp>
#include <Abstractions/WindowAbst.hpp>
#include <Abstractions/RenderAbst.hpp>
#include <Core/Debugger.hpp>

BE::AudioAbst::AudioAbst()
{
    WindowAbst::instance()->createWindow();         // Making sure that both of these are initialized
    RenderAbst::instance()->createOpenGlContext();  // before we attempt to init Dear FMod.

    if (FMOD::System_Create(&_system) != FMOD_OK)
    {
        Core::Debugger::instance()->AddLog("[ERR][AudioAbst::%s] Failed to create FMod instance with System_Create\n", __func__);
        return;
    }

    int driverCount = 0;
    _system->getNumDrivers(&driverCount);

    if (driverCount == 0)
    {
        Core::Debugger::instance()->AddLog("[ERR][AudioAbst::%s] No valid audio drivers where found\n", __func__);
        return;
    }
    _system->init(36, FMOD_INIT_NORMAL, nullptr); // Initialize our Instance with 36 Channels
}

BE::AudioAbst::~AudioAbst()
{
}

BE::AudioAbst::Sound*
BE::AudioAbst::createSound(const std::string& filePath_, FMOD_MODE mode_)
{
    Sound* retVal = new Sound();

    if (_system->createSound(filePath_.c_str(), mode_, 0, &retVal->pSound) != FMOD_OK)
    {
        Core::Debugger::instance()->AddLog("[ERR][AudioAbst::%s] Unable to create sound\n", __func__);
        return nullptr;
    }
    retVal->loop = false;
    retVal->channel = nullptr;
    return retVal;
}

void
BE::AudioAbst::playSound(Sound& sound_, float volume_)
{
    if (sound_.channel != nullptr)
    {
        //        pauseSound(sound_);
        //        sound_.channel = nullptr;
    }
    if (!sound_.loop)
        sound_.pSound->setMode(FMOD_LOOP_OFF);
    else
    {
        sound_.pSound->setMode(FMOD_LOOP_NORMAL);
        sound_.pSound->setLoopCount(-1);
    }

    if (_system->playSound(sound_.pSound, 0, false, &(sound_.channel)) != FMOD_OK)
    {
        Core::Debugger::instance()->AddLog("[ERR][AudioAbst::%s] Failed to play sound\n", __func__);
    }
    setVolume(sound_, volume_);
}

void BE::AudioAbst::resumeSound(Sound & sound_)
{
    if (sound_.channel != nullptr)
    {
        sound_.channel->setPaused(false);
    }
}

void
BE::AudioAbst::pauseSound(Sound& sound_)
{
    if (sound_.channel != nullptr)
    {
        sound_.channel->setPaused(true);
    }
}

void
BE::AudioAbst::stopSound(Sound& sound_)
{
//    pauseSound(sound_);
    if (sound_.channel != nullptr)
    {
        sound_.channel->stop();
    }
}

void BE::AudioAbst::setVolume(Sound& sound_, float volume_)
{
    if (sound_.channel->setVolume(volume_) != FMOD_OK)
    {
        Core::Debugger::instance()->AddLog("[ERR][AudioAbst::%s] Failed to change volume\n", __func__);
    }

}

void BE::AudioAbst::releaseSound(Sound & sound_)
{
				//stopSound(sound_);
				sound_.pSound->release();
}

