/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SpriteComponent.cpp
InversePalindrome.com
*/


#include "SpriteComponent.hpp"


SpriteComponent::SpriteComponent(const pugi::xml_node& componentNode) :
	NodeComponent(cocos2d::Sprite::create(), componentNode),
	sprite(static_cast<cocos2d::Sprite*>(getNode()))
{
	if (const auto spriteFrameAttribute = componentNode.attribute("frame"))
	{
		setSpriteFrame(spriteFrameAttribute.as_string());
	}
	
	const auto textureXAttribute = componentNode.attribute("textureX");
	const auto textureYAttribute = componentNode.attribute("textureR");
	const auto textureWidthAttribute = componentNode.attribute("textureWidth");
	const auto textureHeightAttribute = componentNode.attribute("textureHeight");
	
	if (textureXAttribute && textureYAttribute && textureWidthAttribute && textureHeightAttribute)
	{
		setTextureRect(cocos2d::Rect(textureXAttribute.as_float(), textureYAttribute.as_float(), textureWidthAttribute.as_float(), textureHeightAttribute.as_float()));
	}
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