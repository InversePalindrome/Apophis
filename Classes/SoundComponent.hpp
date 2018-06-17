/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SoundComponent.hpp
InversePalindrome.com
*/


#pragma once

#include "Action.hpp"
#include "EnumHash.hpp"

#include <pugixml.hpp>

#include <string>
#include <unordered_map>


class SoundComponent
{
public:
	explicit SoundComponent(const pugi::xml_node& componentNode);

	std::string getSoundFile(Action action) const;

	int getSoundID(Action action) const;
	const std::unordered_map<Action, int, EnumHash<Action>>& getSoundIDs() const;

	void addSoundID(Action action, int soundID);
	void removeSoundID(Action action);

	bool hasSoundFile(Action action) const;
	bool hasSoundID(Action action) const;

private:
	std::unordered_map<Action, std::string, EnumHash<Action>> soundFiles;
	std::unordered_map<Action, int, EnumHash<Action>> soundIDs;
};