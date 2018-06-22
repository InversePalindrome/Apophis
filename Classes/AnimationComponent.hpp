/*
Copyright (c) 2018 Inverse Palindrome
Apophis - AnimationComponent.hpp
InversePalindrome.com
*/


#pragma once

#include "EnumHash.hpp"
#include "Animation.hpp"

#include <cocos/2d/CCAnimation.h>

#include <pugixml.hpp>

#include <unordered_map>


class AnimationComponent
{
public:
	explicit AnimationComponent(const pugi::xml_node& componentNode);
	~AnimationComponent();

	cocos2d::Animation* getAnimation(Animation animation) const;

	bool hasAnimation(Animation animation) const;

private:
	std::unordered_map<Animation, cocos2d::Animation*, EnumHash<Animation>> animations;
};