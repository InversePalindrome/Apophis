/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SoundComponent.hpp
InversePalindrome.com
*/


#pragma once

#include "State.hpp"
#include "EnumHash.hpp"

#include <pugixml.hpp>

#include <string>
#include <unordered_map>


class SoundComponent
{
public:
	SoundComponent();

	void load(const pugi::xml_node& componentNode);
	void save(pugi::xml_node& componentNode) const;

	void display();

	int getSoundID() const;
	void setSoundID(int soundID);

	void addSound(State state, const std::pair<std::string, bool>& soundFilename);
	void removeSound(State state);
	void clearSounds();

	const std::pair<std::string, bool>& getSound(State state) const;

	bool hasSound(State state) const;

private:
	int soundID;
	std::unordered_map<State, std::pair<std::string, bool>, EnumHash<State>> sounds;

	std::pair<State, std::pair<std::string, bool>> soundToAdd;
};