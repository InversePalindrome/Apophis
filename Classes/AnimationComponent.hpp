/*
Copyright (c) 2018 Inverse Palindrome
Apophis - AnimationComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <cocos/base/CCMap.h>
#include <cocos/2d/CCAnimation.h>

#include <pugixml.hpp>


class AnimationComponent
{
public:
	explicit AnimationComponent(const pugi::xml_node& componentNode);

	cocos2d::Animation* getAnimation(const std::string& action) const;

	bool hasAnimation(const std::string& action) const;

private:
	cocos2d::Map<std::string, cocos2d::Animation*> animations;
};