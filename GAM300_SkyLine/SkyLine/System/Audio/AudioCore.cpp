#include "AudioCore.hpp"

AudioCore * AudioCore::instance()
{
	static std::unique_ptr<AudioCore> instance(new AudioCore());
	return instance.get();
}

AudioCore::~AudioCore()
{
	r = pFmod->release();
	for (auto& sound : m_Sound)
	{
			//		ReleaseSound(*sound);
					delete sound;
					sound = nullptr;
	}
}

void AudioCore::Init()
{
	r = FMOD::System_Create(&pFmod);
	ErrorCheck(r);
	r = pFmod->init(20, FMOD_INIT_NORMAL, NULL);
	ErrorCheck(r);
}
//
//void AudioCore::Loading()
//{
//	r = pFmod->createSound(("./Assets/Sound/test.ogg"), FMOD_LOOP_NORMAL, NULL, &music[TEST]);
//	
//}

void AudioCore::Play(Sound& sound, float volume)
{
	//pFmod->update();
	if (sound.channel != nullptr)
	{
	}
	if (!sound.loop)
		sound.pSound->setMode(FMOD_LOOP_OFF);
	else
	{
		sound.pSound->setMode(FMOD_LOOP_NORMAL);
		sound.pSound->setLoopCount(-1);
	}
	if (pFmod->playSound(sound.pSound, 0, false, &(sound.channel)) != FMOD_OK)
	{
		//Core::Debugger::instance()->AddLog("[ERR][AudioAbst::%s] Failed to play sound\n", __func__);
	}
	setVolume(sound, volume);
}

void AudioCore::setVolume(Sound & sound, float volume)
{
	if (sound.channel->setVolume(volume) != FMOD_OK)
	{
		//Core::Debugger::instance()->AddLog("[ERR][AudioAbst::%s] Failed to change volume\n", __func__);
	}
}

void AudioCore::Stop(Sound& sound)
{
	if (sound.channel != nullptr)
	{
		sound.channel->stop();
	}
}

void AudioCore::Pause(Sound & sound)
{
	if (sound.channel != nullptr)
	{
		sound.channel->setPaused(true);
	}
}

void AudioCore::Resume(Sound & sound)
{
	if (sound.channel != nullptr)
	{
		sound.channel->setPaused(false);
	}
}

void AudioCore::ReleaseSound(Sound& Sound)
{
				Sound.pSound->release();
}

void AudioCore::ErrorCheck(FMOD_RESULT _r)
{
	if (_r != FMOD_OK)
	{
		std::cout << "Error occured !!";
	}
}

Sound * AudioCore::CreateSound(const std::string & filePath_, FMOD_MODE mode_)
{
	Sound* retVal = new Sound();

	if (pFmod->createSound(filePath_.c_str(), mode_, 0, &retVal->pSound) != FMOD_OK)
	{
		//Core::Debugger::instance()->AddLog("[ERR][AudioAbst::%s] Unable to create sound\n", __func__);
		return nullptr;
	}
	retVal->loop = false;
	retVal->channel = nullptr;
	m_Sound.push_back(retVal);
	ErrorCheck(r);
	return retVal;
}

void AudioCore::Update(float /*dt*/)
{
	pFmod->update();
	//playList.clear();
}

AudioCore::AudioCore()
{
	Init();
	//Loading();
}
