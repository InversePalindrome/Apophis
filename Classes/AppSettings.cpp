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
	keyBindings{ { cocos2d::EventKeyboard::KeyCode::KEY_D, KeyAction::MoveRight}, { cocos2d::EventKeyboard::KeyCode::KEY_A, KeyAction::MoveLeft } ,
				 { cocos2d::EventKeyboard::KeyCode::KEY_W, KeyAction::MoveUp }, { cocos2d::EventKeyboard::KeyCode::KEY_S, KeyAction::MoveDown } }
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

KeyAction AppSettings::getKeyAction(cocos2d::EventKeyboard::KeyCode keyCode) const
{
	return keyBindings.at(keyCode);
}

void AppSettings::setKeyBinding(cocos2d::EventKeyboard::KeyCode keyCode, KeyAction keyAction)
{
	auto result = keyBindings.emplace(keyCode, keyAction);

	if (!result.second)
	{
		result.first->second = keyAction;
	}
}

bool AppSettings::hasKeyAction(cocos2d::EventKeyboard::KeyCode keyCode) const
{
	return keyBindings.count(keyCode);
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
				const auto keyCodeAttribute = keyBindingNode.attribute("code");
				const auto keyActionAttribute = keyBindingNode.attribute("action");

				if (keyCodeAttribute && keyActionAttribute)
				{
					keyBindings.emplace(cocos2d::EventKeyboard::KeyCode{ keyCodeAttribute.as_int() }, KeyAction::_from_string(keyActionAttribute.as_string()));
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
	
	for (const auto&[keyCode, keyAction] : keyBindings)
	{
		auto keyBindingNode = settingsNode.append_child("KeyBinding");
		keyBindingNode.append_attribute("code") = static_cast<int>(keyCode);
		keyBindingNode.append_attribute("action") = keyAction._to_string();
	}

	auto soundNode = settingsNode.append_child("Sound");
	soundNode.append_attribute("volume") = soundVolume;

	auto musicNode = settingsNode.append_child("Music");
	musicNode.append_attribute("volume") = musicVolume;
	
	doc.save_file((cocos2d::FileUtils::getInstance()->getWritablePath() + filename).c_str());
}