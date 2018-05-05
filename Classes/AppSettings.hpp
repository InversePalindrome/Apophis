/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - AppSettings.hpp
InversePalindrome.com
*/


#pragma once

#include <cocos/base/CCEventKeyboard.h>

#include <string>
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

	cocos2d::EventKeyboard::KeyCode getKeyCode(const std::string& action) const;
	void setKeyBinding(const std::string& action, cocos2d::EventKeyboard::KeyCode keyCode);

private:
	float soundVolume;
	float musicVolume;
	std::unordered_map<std::string, cocos2d::EventKeyboard::KeyCode> keyBindings;

	void load(const std::string& filename);
	void save(const std::string& filename);
};