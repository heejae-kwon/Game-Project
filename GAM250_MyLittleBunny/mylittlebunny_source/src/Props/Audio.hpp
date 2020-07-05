/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      Audio.hpp
Purpose:        Audio prop is the object that contains the data of the audio files we load in
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#pragma once

#include <Props/BaseProp.hpp>
#include <Abstractions/AudioAbst.hpp>

namespace BE
{
namespace Prop
{
    class Audio : public BaseProp
    {
    public:
        PROP_HASH(Audio)
        Audio(std::string fileName_, std::string id_);
								~Audio(void);

        void    getData(Json::Value& data_)     final;
        void    loadData()                      final;
        void    writeData(Json::Value& data_)   final;
        void    drawData()                      final;

        bool        soundIsLoaded();

        // Saved
        std::string             audioFile;   /*!< The file that the image will be loaded from (ex: music.mp3). */

//    private:
    public:
        void        play();
        void        resume();
        void        pause();
        void        stop();
								void								setVolume(float volume);
								void								turnoff();
								void								turnon();

        // Saved
        float               _volume;
        bool               _isLooping;

        // Temporary
        AudioAbst::Sound*   soundData;
        bool                _isPaused;
								bool																b_mute;
    };
}
}
