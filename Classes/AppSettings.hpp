/*
Copyright (c) 2018 Inverse Palindrome
Apophis - AppSettings.hpp
InversePalindrome.com
*/


#pragma once

#include "EnumHash.hpp"
#include "KeyAction.hpp"

#include <cocos/base/CCEventKeyboard.h>

#include <unordered_map>


class AppSettings
{
public:
	AppSettings();
    AppSettings(const AppSettings&) = delete;
	AppSettings& operator= (const AppSettings&) = delete;

	~AppSettings();

	static AppSettings& getInstance();

	float getSoundVolume() const;
	void setSoundVolume(float soundVolume);

	float getMusicVolume() const;
	void setMusicVolume(float musicVolume);

	cocos2d::EventKeyboard::KeyCode getKeyCode(KeyAction keyAction) const;
	void setKeyBinding(KeyAction keyAction, cocos2d::EventKeyboard::KeyCode keyCode);

private:
	float soundVolume;
	float musicVolume;

	std::unordered_map<KeyAction, cocos2d::EventKeyboard::KeyCode, EnumHash<KeyAction>> keyBindings;

	void load(const std::string& filename);
	void save(const std::string& filename);
};