/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - AppSettings.cpp
InversePalindrome.com
*/


#include "AppSettings.hpp"

#include <tinyxml2/tinyxml2.h>

#include <cocos/platform/CCFileUtils.h>


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
	auto* fileUtils = cocos2d::FileUtils::getInstance();
	const auto& path = fileUtils->fullPathForFilename(filename);
	const auto& data = fileUtils->getStringFromFile(path);

	tinyxml2::XMLDocument doc;
	doc.Parse(data.c_str());

	if (const auto* settingsNode = doc.RootElement())
	{
		if (const auto* soundNode = settingsNode->FirstChildElement("Sound"))
		{
			if (const auto* soundVolume = soundNode->Attribute("volume"))
			{
				this->soundVolume = std::stof(soundVolume);
			}
		}
		if (const auto* musicNode = settingsNode->FirstChildElement("Music"))
		{
			if (const auto* musicVolume = musicNode->Attribute("volume"))
			{
				this->musicVolume = std::stof(musicVolume);
			}
		}

		for (const auto* keyBindingNode = settingsNode->FirstChildElement("KeyBinding"); keyBindingNode; keyBindingNode = keyBindingNode->NextSiblingElement("KeyBinding"))
		{
			const auto* keyAction = keyBindingNode->Attribute("action");
			const auto* keyCode = keyBindingNode->Attribute("keyCode");

			if (keyAction && keyCode)
			{
				keyBindings[KeyAction::_from_string(keyAction)] = cocos2d::EventKeyboard::KeyCode{ std::stoi(keyCode) };
			}
		}
	}
}

void AppSettings::save(const std::string& filename)
{
	tinyxml2::XMLDocument doc;

	auto* decl = doc.NewDeclaration();
	doc.LinkEndChild(decl);

	auto* settingsNode = doc.NewElement("Settings");

	auto* soundNode = doc.NewElement("Sound");
	soundNode->SetAttribute("volume", soundVolume);

	auto* musicNode = doc.NewElement("Music");
	musicNode->SetAttribute("volume", musicVolume);

	settingsNode->LinkEndChild(soundNode);
	settingsNode->LinkEndChild(musicNode);

	for (const auto& [keyAction, keyCode] : keyBindings)
	{
		auto* keyBindingNode = doc.NewElement("KeyBinding");
		keyBindingNode->SetAttribute("action", keyAction._to_string());
		keyBindingNode->SetAttribute("keyCode", static_cast<int>(keyCode));

		settingsNode->LinkEndChild(keyBindingNode);
	}

	doc.LinkEndChild(settingsNode);

	const auto& path = cocos2d::FileUtils::getInstance()->getWritablePath() + filename;

	doc.SaveFile(path.c_str());
}