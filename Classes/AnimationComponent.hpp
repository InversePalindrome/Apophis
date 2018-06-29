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

	void addAnimation(Animation animationName, cocos2d::Animation* animation);
	void removeAnimation(Animation animationName);

	cocos2d::Animation* getAnimation(Animation animationName) const;

	bool hasAnimation(Animation animationName) const;

private:
	std::unordered_map<Animation, cocos2d::Animation*, EnumHash<Animation>> animations;
};