/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SoundComponent.hpp
InversePalindrome.com
*/


#pragma once

#include "Sound.hpp"
#include "EnumHash.hpp"

#include <pugixml.hpp>

#include <string>
#include <unordered_map>


class SoundComponent
{
public:
	explicit SoundComponent(const pugi::xml_node& componentNode);

	void save(pugi::xml_node& componentNode) const;

	std::string getSoundFile(Sound sound) const;

	int getSoundID(Sound sound) const;
	const std::unordered_map<Sound, int, EnumHash<Sound>>& getSoundIDs() const;

	void addSoundID(Sound sound, int soundID);
	void removeSoundID(Sound sound);
	void clearSoundIDs();

	bool hasSoundFile(Sound sound) const;
	bool hasSoundID(Sound sound) const;

private:
	std::unordered_map<Sound, std::string, EnumHash<Sound>> soundFiles;
	std::unordered_map<Sound, int, EnumHash<Sound>> soundIDs;
};