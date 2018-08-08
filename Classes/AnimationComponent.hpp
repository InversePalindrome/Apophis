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

	void save(pugi::xml_node& componentNode) const;

	void display();

	void addAnimation(Animation animationName, const std::vector<std::string>& spriteFrameNames, float delay = 0.f);
	void removeAnimation(Animation animationName);

	cocos2d::Animation* getAnimation(Animation animationName) const;

	bool hasAnimation(Animation animationName) const;

private:
	std::unordered_map<Animation, std::pair<cocos2d::Animation*, std::vector<std::string>>, EnumHash<Animation>> animations;
};