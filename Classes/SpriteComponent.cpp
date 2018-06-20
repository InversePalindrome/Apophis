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
	sprite->removeAllChildren();
	sprite->removeFromParent();
	
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

void SpriteComponent::setPosition(const cocos2d::Vec2& position)
{
	sprite->setPosition(position);
}

void SpriteComponent::setSize(const cocos2d::Vec2& size)
{
	sprite->setScale(size.x / sprite->getContentSize().width, size.y / sprite->getContentSize().height);
}

void SpriteComponent::setRotation(float angle)
{
	sprite->setRotation(angle);
}

cocos2d::Action* SpriteComponent::runAction(cocos2d::Action* action)
{
	return sprite->runAction(action);
}

void SpriteComponent::stopAction(cocos2d::Action* action)
{
	sprite->stopAction(action);
}