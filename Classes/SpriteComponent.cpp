/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SpriteComponent.cpp
InversePalindrome.com
*/


#include "SpriteComponent.hpp"


SpriteComponent::SpriteComponent(const pugi::xml_node& componentNode) :
	sprite(cocos2d::Sprite::createWithSpriteFrameName(componentNode.text().as_string()))
{
	sprite->retain();
}

SpriteComponent::~SpriteComponent()
{
	sprite->release();
}

void SpriteComponent::setPosition(const cocos2d::Vec2& position)
{
	sprite->setPosition(position);
}

void SpriteComponent::setRotation(float angle)
{
	sprite->setRotation(angle);
}

cocos2d::Sprite* SpriteComponent::getSprite()
{
	return sprite;
}

cocos2d::Sprite* SpriteComponent::getSprite() const
{
	return sprite;
}