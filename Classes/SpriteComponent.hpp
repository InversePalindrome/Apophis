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

	void display();

	cocos2d::SpriteFrame* getSpriteFrame() const;
	void setSpriteFrame(const std::string& spriteFrameName);

	cocos2d::Texture2D* getTexture() const;
	void setTexture(cocos2d::Texture2D* texture);

	cocos2d::Rect getTextureRect() const;
	void setTextureRect(const cocos2d::Rect& textureRect);

	bool isTextureRepeated() const;
	void setTextureRepeated(bool repeatTexture);

private:
	cocos2d::Sprite* sprite;

	std::string spriteFrameName;
	bool repeatTexture;
};