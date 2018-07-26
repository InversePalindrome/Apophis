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

	void save(pugi::xml_node& componentNode) const;

	cocos2d::SpriteFrame* getSpriteFrame() const;
	void setSpriteFrame(const std::string& spriteFrameName);

	cocos2d::Rect getTextureRect() const;
	void setTextureRect(const cocos2d::Rect& textureRect);

private:
	cocos2d::Sprite* sprite;

	std::string spriteFrameName;
};