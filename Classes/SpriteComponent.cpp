/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - SpriteComponent.cpp
InversePalindrome.com
*/


#include "SpriteComponent.hpp"


SpriteComponent::SpriteComponent(const tinyxml2::XMLElement* componentNode) :
	sprite(cocos2d::Sprite::create())
{
	if (const auto* name = componentNode->GetText())
	{
		sprite->initWithSpriteFrameName(name);
	}

	sprite->retain();
}

SpriteComponent::~SpriteComponent()
{
	sprite->removeFromParentAndCleanup(true);
	sprite->release();
}

cocos2d::Sprite* SpriteComponent::getSprite()
{
	return sprite;
}

cocos2d::Sprite* SpriteComponent::getSprite() const
{
	return sprite;
}