/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      AudioAbst.hpp
Purpose:        The abstraction for the audio library we use (in this case FMOD)
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#pragma once

#include <_External/Includes/fmod/fmod.hpp>

#include <memory>
#include <string>

namespace BE
{

    //!  AudioAbst(raction) class. 
    /*!
    AudioAbst is a very basic abstraction of Dear ImGui, I don't think I'll switch it out for another Immediat Mode GUI library that is why it is so barebones.
    This class is used by the Debugger core.
    It has to be called every frame that we wish to render debug info to the screen
    that is why it has the startNewFrame() and endOfFrame() that you might see often throughout this engine.
    */

    class AudioAbst
    {
        // All type redefinitions go here
    protected:
        using AudioAbstSmartPtr = std::unique_ptr<AudioAbst>;
    public:
        struct Sound // A simple encapsulation of the sound
        {
            FMOD::Sound* pSound;
            // Additional info goes here
            // It's function is similar to the Texture class...I wonder if it's worth making a class out of it
            // but for now we'll leave it like this.
            bool loop;
            FMOD::Channel *channel;
        };

    public:
        static AudioAbst* instance() //!< Returns an instance of the class
        {
            static AudioAbstSmartPtr instance(new AudioAbst());
            return instance.get();
        }
        ~AudioAbst();

        Sound*  createSound(const std::string& filePath_, FMOD_MODE mode_ = FMOD_DEFAULT);
        
        void    playSound(Sound& sound_, float volume_);
        void    resumeSound(Sound& sound_);
        void    pauseSound(Sound& sound_);
        void    stopSound(Sound& sound_);
        void    setVolume(Sound& sound_, float volume_);

								void				releaseSound(Sound& sound_);

    protected:
        //
    private:
        AudioAbst();    //!< AudioAbst's constructor is private as it is a Singleton and should only be accessed through the instance() function

    public:
        //
    protected:
        //
    private:
        FMOD::System*   _system; //!< Pointer to the FMOD instance
    };
}