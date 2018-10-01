/*
Copyright (c) 2018 Inverse Palindrome
Apophis - AppSettings.hpp
InversePalindrome.com
*/


#pragma once

#include "KeyAction.hpp"

#include <cocos/base/CCEventKeyboard.h>

#include <vector>
#include <unordered_map>


class AppSettings
{
public:
	AppSettings();
    AppSettings(const AppSettings&) = delete;
	AppSettings& operator= (const AppSettings&) = delete;

	static AppSettings& getInstance();

	void load(const std::string& filename);
	void save(const std::string& filename) const;

    int playSound(const std::string& soundFilename, bool loop = false);
	int playMusic(const std::string& musicFilename, bool loop = false);

	void stopSound(int soundID);
	void stopMusic(int musicID);

	void stopSounds();
	void stopMusic();

	float getSoundVolume() const;
	void setSoundVolume(float soundVolume);

	float getMusicVolume() const;
	void setMusicVolume(float musicVolume);

	KeyAction getKeyAction(cocos2d::EventKeyboard::KeyCode keyCode) const;
	void addKeyBinding(cocos2d::EventKeyboard::KeyCode keyCode, KeyAction keyAction);

	bool hasKeyAction(cocos2d::EventKeyboard::KeyCode keyCode) const;

private:
	float soundVolume;
	float musicVolume;

	std::vector<int> soundIDs;
	std::vector<int> musicIDs;

	std::unordered_map<cocos2d::EventKeyboard::KeyCode, KeyAction> keyBindings;
};