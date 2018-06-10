/*
Copyright (c) 2018 Inverse Palindrome
Apophis - AppSettings.cpp
InversePalindrome.com
*/


#include "AppSettings.hpp"

#include <cocos/platform/CCFileUtils.h>

#include <pugixml.hpp>


AppSettings::AppSettings() :
	soundVolume(1.f),
	musicVolume(1.f),
	keyBindings({ { KeyAction::MoveRight, cocos2d::EventKeyboard::KeyCode::KEY_D }, { KeyAction::MoveLeft, cocos2d::EventKeyboard::KeyCode::KEY_A } ,
				  { KeyAction::MoveUp, cocos2d::EventKeyboard::KeyCode::KEY_W }, { KeyAction::MoveDown, cocos2d::EventKeyboard::KeyCode::KEY_S } })
{
	load("Settings.xml");
}

AppSettings::~AppSettings()
{
	save("Settings.xml");
}

AppSettings& AppSettings::getInstance()
{
	static AppSettings instance;

	return instance;
}

float AppSettings::getSoundVolume() const
{
	return soundVolume;
}

void AppSettings::setSoundVolume(float soundVolume)
{
	this->soundVolume = soundVolume;
}

float AppSettings::getMusicVolume() const
{
	return musicVolume;
}

void AppSettings::setMusicVolume(float musicVolume)
{
	this->musicVolume = musicVolume;
}

cocos2d::EventKeyboard::KeyCode AppSettings::getKeyCode(KeyAction keyAction) const
{
	return keyBindings.at(keyAction);
}

void AppSettings::setKeyBinding(KeyAction keyAction, cocos2d::EventKeyboard::KeyCode keyCode)
{
	keyBindings[keyAction] = keyCode;
}

void AppSettings::load(const std::string& filename)
{
	pugi::xml_document doc;
	
	if (doc.load_file(cocos2d::FileUtils::getInstance()->fullPathForFilename(filename).c_str()))
	{
		if (const auto settingsNode = doc.child("Settings"))
		{
			for (const auto keyBindingNode : settingsNode.children("KeyBinding"))
			{
				const auto keyActionAttribute = keyBindingNode.attribute("action");
				const auto keyCodeAttribute = keyBindingNode.attribute("keyCode");

				if (keyActionAttribute && keyCodeAttribute)
				{
					keyBindings[KeyAction::_from_string(keyActionAttribute.as_string())] = cocos2d::EventKeyboard::KeyCode{ keyCodeAttribute.as_int() };
				}
			}

			if (const auto soundNode = settingsNode.child("Sound"))
			{
				if (const auto volumeAttribute = soundNode.attribute("volume"))
				{
					soundVolume = volumeAttribute.as_float();
				}
			}
			if (const auto musicNode = settingsNode.child("Music"))
			{
				if (const auto volumeAttribute = musicNode.attribute("volume"))
				{
					musicVolume = volumeAttribute.as_float();
				}
			}
		}
	}
}

void AppSettings::save(const std::string& filename)
{
	pugi::xml_document doc;

	auto declaration = doc.append_child(pugi::node_declaration);
	declaration.append_attribute("version") = "1.0";
	declaration.append_attribute("encoding") = "UTF-8";

	auto settingsNode = doc.append_child("Settings");

	for (const auto&[keyAction, keyCode] : keyBindings)
	{
		auto keyBindingNode = settingsNode.append_child("KeyBinding");
		keyBindingNode.append_attribute("action") = keyAction._to_string();
		keyBindingNode.append_attribute("keyCode") = static_cast<int>(keyCode);
	}

	auto soundNode = settingsNode.append_child("Sound");
	soundNode.append_attribute("volume") = soundVolume;

	auto musicNode = settingsNode.append_child("Music");
	musicNode.append_attribute("volume") = musicVolume;

	auto path = cocos2d::FileUtils::getInstance()->getWritablePath() + filename;
	
	doc.save_file(path.c_str());
}