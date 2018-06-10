/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SpriteComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <pugixml.hpp>

#include <cocos/2d/CCSprite.h>

#include <string>


class SpriteComponent
{
public:
	explicit SpriteComponent(const pugi::xml_node& componentNode);

	~SpriteComponent();

	void load(const std::string& filename);

	cocos2d::Sprite* getSprite();
	cocos2d::Sprite* getSprite() const;

private:
	cocos2d::Sprite* sprite;
};