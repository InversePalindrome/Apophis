/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SpriteComponent.cpp
InversePalindrome.com
*/


#include "SpriteComponent.hpp"


SpriteComponent::SpriteComponent(const pugi::xml_node& componentNode) :
	sprite(cocos2d::Sprite::create())
{
	load(componentNode.text().as_string());
	
	sprite->retain();
}

SpriteComponent::~SpriteComponent()
{
	sprite->removeFromParentAndCleanup(true);
	sprite->release();
}

void SpriteComponent::load(const std::string& filename)
{
	sprite->initWithSpriteFrameName(filename);
}

cocos2d::Sprite* SpriteComponent::getSprite()
{
	return sprite;
}

cocos2d::Sprite* SpriteComponent::getSprite() const
{
	return sprite;
}