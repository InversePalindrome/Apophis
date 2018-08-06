/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SpriteComponent.cpp
InversePalindrome.com
*/


#include "SpriteComponent.hpp"


SpriteComponent::SpriteComponent(const pugi::xml_node& componentNode) :
	NodeComponent(cocos2d::Sprite::create(), componentNode),
	sprite(static_cast<cocos2d::Sprite*>(getNode())),
	repeatTexture(false)
{
	if (const auto spriteFrameAttribute = componentNode.attribute("frame"))
	{
		setSpriteFrame(spriteFrameAttribute.as_string());
	}
	if (const auto repeatAttribute = componentNode.attribute("repeat"))
	{
		setRepeatedTexture(repeatAttribute.as_bool());
	}
	if (const auto textureXAttribute = componentNode.attribute("textureX"),
	    textureYAttribute = componentNode.attribute("textureY"),
	    textureWidthAttribute = componentNode.attribute("textureWidth"),
	    textureHeightAttribute = componentNode.attribute("textureHeight"); 
	    textureXAttribute && textureYAttribute && textureWidthAttribute && textureHeightAttribute)
	{
		setTextureRect({ textureXAttribute.as_float(), textureYAttribute.as_float(), textureWidthAttribute.as_float(), textureHeightAttribute.as_float() });
	}
}

void SpriteComponent::save(pugi::xml_node& componentNode) const
{
	NodeComponent::save(componentNode);
	
	componentNode.set_name("Sprite");
	
	if (!spriteFrameName.empty())
	{
		componentNode.append_attribute("frame") = spriteFrameName.c_str();
	}

	componentNode.append_attribute("repeat") = isTextureRepeated();
	componentNode.append_attribute("textureX") = getTextureRect().origin.x;
	componentNode.append_attribute("textureY") = getTextureRect().origin.y;
	componentNode.append_attribute("textureWidth") = getTextureRect().size.width;
	componentNode.append_attribute("textureHeight") = getTextureRect().size.height;
}

cocos2d::SpriteFrame* SpriteComponent::getSpriteFrame() const
{
	return sprite->getSpriteFrame();
}

void SpriteComponent::setSpriteFrame(const std::string& spriteFrameName)
{
	this->spriteFrameName = spriteFrameName;

	sprite->setSpriteFrame(spriteFrameName);
}

cocos2d::Texture2D* SpriteComponent::getTexture() const
{
	return sprite->getTexture();
}

void SpriteComponent::setTexture(cocos2d::Texture2D* texture)
{
	sprite->setTexture(texture);
}

cocos2d::Rect SpriteComponent::getTextureRect() const
{
	return sprite->getTextureRect();
}

void SpriteComponent::setTextureRect(const cocos2d::Rect& textureRect)
{
	sprite->setTextureRect(textureRect);
}

bool SpriteComponent::isTextureRepeated() const
{
	return repeatTexture;
}

void SpriteComponent::setRepeatedTexture(bool repeatTexture)
{
	this->repeatTexture = repeatTexture;

	if (repeatTexture)
	{
		getTexture()->setTexParameters({ GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT });
	}
}