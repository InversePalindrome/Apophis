/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - AnimationComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <tinyxml2/tinyxml2.h>

#include <cocos/base/CCMap.h>
#include <cocos/2d/CCAnimation.h>


class AnimationComponent
{
public:
	explicit AnimationComponent(const tinyxml2::XMLElement* componentNode);

	cocos2d::Animation* getAnimation(const std::string& action) const;

	bool hasAnimation(const std::string& action) const;

private:
	cocos2d::Map<std::string, cocos2d::Animation*> animations;
};