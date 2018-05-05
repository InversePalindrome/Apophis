/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - AudioManager.cpp
InversePalindrome.com
*/


#include "AppSettings.hpp"
#include "AudioManager.hpp"


AudioManager& AudioManager::getInstance()
{
	static AudioManager instance;
	
	return instance;
}

int AudioManager::playSound(const std::string& filename, bool loop)
{
	auto soundID = cocos2d::experimental::AudioEngine::play2d(filename, loop, AppSettings::getInstance().getSoundVolume());

	soundIDs.insert(soundID);

	cocos2d::experimental::AudioEngine::setFinishCallback(soundID, [this](auto id, const auto& filename) { soundIDs.erase(id); });

	return soundID;
}

int AudioManager::playMusic(const std::string& filename, bool loop)
{
	auto musicID = cocos2d::experimental::AudioEngine::play2d(filename, loop, AppSettings::getInstance().getMusicVolume());

	musicIDs.insert(musicID);

	cocos2d::experimental::AudioEngine::setFinishCallback(musicID, [this](auto id, const auto& filename) { musicIDs.erase(id); });

	return musicID;
}

void AudioManager::resumeAudio(int audioID)
{
	cocos2d::experimental::AudioEngine::resume(audioID);
}

void AudioManager::resumeSounds()
{
	for (auto soundID : soundIDs)
	{
		cocos2d::experimental::AudioEngine::resume(soundID);
	}
}

void AudioManager::resumeMusic()
{
	for (const auto& musicID : musicIDs)
	{
		cocos2d::experimental::AudioEngine::resume(musicID);
	}
}

void AudioManager::pauseAudio(int audioID)
{
	cocos2d::experimental::AudioEngine::pause(audioID);
}

void AudioManager::pauseSounds()
{
	for (auto soundID : soundIDs)
	{
		cocos2d::experimental::AudioEngine::pause(soundID);
	}
}

void AudioManager::pauseMusic()
{
	for (auto musicID : musicIDs)
	{
		cocos2d::experimental::AudioEngine::pause(musicID);
	}
}