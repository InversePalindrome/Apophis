/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SpriteComponent.hpp
InversePalindrome.com
*/


#pragma once

#include "NodeComponent.hpp"

#include <cocos/2d/CCSprite.h>

#include <pugixml.hpp>


class SpriteComponent : public NodeComponent
{
public:
	explicit SpriteComponent(const pugi::xml_node& componentNode);

	cocos2d::Rect getTextureRect() const;
	void setTextureRect(const cocos2d::Rect& textureRect);

	cocos2d::SpriteFrame* getSpriteFrame() const;
	void setSpriteFrame(const std::string& spriteFrameName);

private:
	cocos2d::Sprite* sprite;
};