/*
Copyright (c) 2018 Inverse Palindrome
Apophis - AnimationComponent.hpp
InversePalindrome.com
*/


#pragma once

#include "State.hpp"
#include "EnumHash.hpp"

#include <cocos/2d/CCAnimation.h>

#include <pugixml.hpp>

#include <unordered_map>


class AnimationComponent
{
public:
	void load(const pugi::xml_node& componentNode);
	void save(pugi::xml_node& componentNode) const;

	void display();

	void addAnimation(State state, cocos2d::Animation* animation);
	void removeAnimation(State state);

	const cocos2d::Animation* getAnimation(State state) const;

	bool hasAnimation(State state) const;

private:
	std::unordered_map<State, cocos2d::Animation*, EnumHash<State>> animations;
};