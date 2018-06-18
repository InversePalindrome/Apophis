/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SpriteComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <cocos/2d/CCSprite.h>

#include <pugixml.hpp>


class SpriteComponent 
{
public:
	explicit SpriteComponent(const pugi::xml_node& componentNode);

	~SpriteComponent();

	cocos2d::Sprite* getSprite();
	cocos2d::Sprite* getSprite() const;

	void setPosition(const cocos2d::Vec2& position);
	void setRotation(float angle);

private:
	cocos2d::Sprite* sprite;
};