/*
Copyright (c) 2018 Inverse Palindrome
Apophis - AnimationComponent.hpp
InversePalindrome.com
*/


#pragma once

#include "Action.hpp"
#include "EnumHash.hpp"

#include <cocos/2d/CCAnimation.h>

#include <pugixml.hpp>

#include <unordered_map>


class AnimationComponent
{
public:
	explicit AnimationComponent(const pugi::xml_node& componentNode);
	~AnimationComponent();

	cocos2d::Animation* getAnimation(Action action) const;

	bool hasAnimation(Action action) const;

private:
	std::unordered_map<Action, cocos2d::Animation*, EnumHash<Action>> animations;
};