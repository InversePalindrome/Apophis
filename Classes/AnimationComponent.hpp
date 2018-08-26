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
	AnimationComponent();
	~AnimationComponent();

	void load(const pugi::xml_node& componentNode);
	void save(pugi::xml_node& componentNode) const;

	void display();

	cocos2d::Animation* addAnimation(State state, const std::string& animationName);
	void removeAnimation(State state);
	void clearAnimations();

	cocos2d::Animation* getAnimation(State state);
	const cocos2d::Animation* getAnimation(State state) const;

	bool hasAnimation(State state) const;

private:
	std::unordered_map<State, std::pair<cocos2d::Animation*, std::string>, EnumHash<State>> animations;

	std::pair<State, std::pair<std::string, int>> animationToAdd;
};