/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      Audio.cpp
Purpose:        Audio information 
Language:       C++
Project:        GAM250
Author:         Name : Stuat Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/
#include <Props/Audio.hpp>
#include <Core/Debugger.hpp>
#include <Utilities/JsonReader.hh>
#include <Utilities/JsonWriter.hh>

BE::Prop::Audio::Audio(std::string fileName_, std::string id_) :
    BaseProp(identifier, fileName_, id_),
    _isPaused(false), b_mute(false)
{
    type = Type::AUDIO;
    _volume = 1.0f;
}

BE::Prop::Audio::~Audio(void)
{
				AudioAbst::instance()->releaseSound(*soundData);
				soundData = nullptr;
}

void
BE::Prop::Audio::getData(Json::Value& data_)
{
    Json::Value propData = data_["Props"][fileName];

    id = JsonReader::getFieldAsString(propData["id"]);
    audioFile = JsonReader::getFieldAsString(propData["audioFile"]);
    _volume = JsonReader::getFieldAsFloat(propData["volume"]);
    _isLooping = JsonReader::getFieldAsBool(propData["isLooping"]);
    loadData();
}

void
BE::Prop::Audio::loadData()
{
    if ((soundData = AudioAbst::instance()->createSound(formatPath("./Data/Audio/" + audioFile))) == nullptr)
    {
        Core::Debugger::instance()->AddLog("[ERR][Audio::%s] Failed to create audio\n", __func__);
        return;
    }

}

void
BE::Prop::Audio::writeData(Json::Value& data_)
{
    JsonWriter::addValue(data_["Props"][fileName]["type"], "AUDIO");
    JsonWriter::addValue(data_["Props"][fileName]["id"], id);
    JsonWriter::addValue(data_["Props"][fileName]["audioFile"], audioFile);
    JsonWriter::addValue(data_["Props"][fileName]["volume"], _volume);
    JsonWriter::addValue(data_["Props"][fileName]["isLooping"], _isLooping);
}

void
BE::Prop::Audio::drawData()
{
    float textWidth = 100;
    ImGui::PushItemWidth(textWidth);

    if (ImGui::InputFloat("Volume", &_volume, 0.01f, 0.1f, 2))
    {
        if (_volume < -1.f)
        {
            _volume = -1.f;
        }
        else if (_volume > 1.f)
        {
            _volume = 1.f;
        }
        AudioAbst::instance()->setVolume(*soundData, _volume);
    }
    ImGui::Checkbox("Loop", &_isLooping);
    if (ImGui::Button("Play"))
    {
        play();
    }
    if (!_isPaused)
    {
        if (ImGui::Button("Pause"))
        {
            pause();
            _isPaused = true;
        }
    }
    else
    {
        if (ImGui::Button("Resume"))
        {
            resume();
            _isPaused = false;
        }
    }
    if (ImGui::Button("Stop"))
    {
        stop();
    }
    ImGui::PopItemWidth();
}

bool
BE::Prop::Audio::soundIsLoaded()
{
    return (soundData != nullptr) ? true : false;
}

void
BE::Prop::Audio::play()
{
				if (b_mute == false) {
								soundData->loop = _isLooping;
								AudioAbst::instance()->playSound(*soundData, _volume);
				}
}

void BE::Prop::Audio::resume()
{
    AudioAbst::instance()->resumeSound(*soundData);
}

void
BE::Prop::Audio::pause()
{
    AudioAbst::instance()->pauseSound(*soundData);
}

void
BE::Prop::Audio::stop()
{
    AudioAbst::instance()->stopSound(*soundData);
}

void BE::Prop::Audio::setVolume(float volume)
{
				_volume = volume;
}

void BE::Prop::Audio::turnon()
{
				b_mute = false;
}

void BE::Prop::Audio::turnoff()
{
				b_mute = true;
}
