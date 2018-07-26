/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SoundComponent.cpp
InversePalindrome.com
*/


#include "SoundComponent.hpp"


SoundComponent::SoundComponent(const pugi::xml_node& componentNode)
{
	for (const auto soundNode : componentNode.children())
	{
		soundFiles.emplace(Sound::_from_string(soundNode.name()), soundNode.text().as_string());
	}
}

void SoundComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.set_name("Sound");

	for (const auto&[soundID, soundFile] : soundFiles)
	{
		componentNode.append_child(soundID._to_string()).text().set(soundFile.c_str());
	}
}

std::string SoundComponent::getSoundFile(Sound sound) const
{
	return soundFiles.at(sound);
}

int SoundComponent::getSoundID(Sound sound) const
{
	return soundIDs.at(sound);
}

const std::unordered_map<Sound, int, EnumHash<Sound>>& SoundComponent::getSoundIDs() const
{
	return soundIDs;
}

void SoundComponent::addSoundID(Sound sound, int soundID)
{
	soundIDs.emplace(sound, soundID);
}

void SoundComponent::removeSoundID(Sound sound)
{
	soundIDs.erase(sound);
}

void SoundComponent::clearSoundIDs()
{
	soundIDs.clear();
}

bool SoundComponent::hasSoundFile(Sound sound) const
{
	return soundFiles.count(sound);
}

bool SoundComponent::hasSoundID(Sound sound) const
{
	return soundIDs.count(sound);
}