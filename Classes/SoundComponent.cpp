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
		soundFiles.emplace(Action::_from_string(soundNode.name()), soundNode.text().as_string());
	}
}

std::string SoundComponent::getSoundFile(Action action) const
{
	return soundFiles.at(action);
}

int SoundComponent::getSoundID(Action action) const
{
	return soundIDs.at(action);
}

const std::unordered_map<Action, int, EnumHash<Action>>& SoundComponent::getSoundIDs() const
{
	return soundIDs;
}

void SoundComponent::addSoundID(Action action, int soundID)
{
	soundIDs.emplace(action, soundID);
}

void SoundComponent::removeSoundID(Action action)
{
	soundIDs.erase(action);
}

bool SoundComponent::hasSoundFile(Action action) const
{
	return soundFiles.count(action);
}

bool SoundComponent::hasSoundID(Action action) const
{
	return soundIDs.count(action);
}