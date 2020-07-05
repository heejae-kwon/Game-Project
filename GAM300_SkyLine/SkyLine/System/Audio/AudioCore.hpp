#pragma once
#include "BaseCore.hpp"
#include "fmod.hpp"
#include <string>
#include <iostream>


class Sound // A simple encapsulation of the sound
{
public:
	FMOD::Sound* pSound;
	bool loop;
	FMOD::Channel *channel;
	float volume;
};

class AudioCore : public BaseCore
{
public:
	//Magical singletern code
	static AudioCore* instance();
	~AudioCore();

	void Init();
	//void Loading();
	void Play(Sound& sound, float volume);
	void Stop(Sound& sound);
	void Pause(Sound& sound);
	void Resume(Sound& sound);

	void setVolume(Sound& sound, float volume);
	void ReleaseSound(Sound& Sound);
	void ErrorCheck(FMOD_RESULT _r);

	Sound*  CreateSound(const std::string& filePath_, FMOD_MODE mode_ = FMOD_DEFAULT);

	//Initialize the system
	//void Initialize(void) override;

//All systems are updated every frame
	void Update(float dt) override;

private:
	AudioCore();

	std::vector<Sound*> m_Sound;
	FMOD::System* pFmod;
	FMOD_RESULT r;
};