/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - SpriteComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <tinyxml2/tinyxml2.h>

#include <cocos/2d/CCSprite.h>

#include <string>


class SpriteComponent
{
public:
	explicit SpriteComponent(const tinyxml2::XMLElement* componentNode);

	~SpriteComponent();

	void load(const std::string& filename);

	cocos2d::Sprite* getSprite();
	cocos2d::Sprite* getSprite() const;

private:
	cocos2d::Sprite* sprite;
};