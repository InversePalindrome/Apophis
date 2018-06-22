/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SpriteComponent.cpp
InversePalindrome.com
*/


#include "SpriteComponent.hpp"


SpriteComponent::SpriteComponent(const pugi::xml_node& componentNode) :
	NodeComponent(cocos2d::Sprite::createWithSpriteFrameName(componentNode.text().as_string())),
	sprite(static_cast<cocos2d::Sprite*>(getNode()))
{
}

cocos2d::Rect SpriteComponent::getTextureRect() const
{
	return sprite->getTextureRect();
}

void SpriteComponent::setTextureRect(const cocos2d::Rect& textureRect)
{
	sprite->setTextureRect(textureRect);
}

cocos2d::SpriteFrame* SpriteComponent::getSpriteFrame() const
{
	return sprite->getSpriteFrame();
}

void SpriteComponent::setSpriteFrame(const std::string& spriteFrameName)
{
	sprite->setSpriteFrame(spriteFrameName);
}