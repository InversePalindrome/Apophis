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
		load(name);
	}
	
	sprite->retain();
}

SpriteComponent::~SpriteComponent()
{
	//sprite->removeFromParentAndCleanup(true);
	//sprite->release();
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