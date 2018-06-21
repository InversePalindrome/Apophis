/*
Copyright (c) 2018 Inverse Palindrome
Apophis - LabelComponent.cpp
InversePalindrome.com
*/


#include "LabelComponent.hpp"


LabelComponent::LabelComponent(const pugi::xml_node& componentNode) :
	label(cocos2d::Label::create())
{
	label->setString(componentNode.text().as_string());

	if (const auto fontAttribute = componentNode.attribute("font"))
	{
		label->setSystemFontName(fontAttribute.as_string());
	}
	if (const auto sizeAttribute = componentNode.attribute("size"))
	{
		label->setSystemFontSize(sizeAttribute.as_float());
	}
	if (const auto HAlignmentAttribute = componentNode.attribute("HAlignment"))
	{
		label->setAlignment(static_cast<cocos2d::TextHAlignment>(HAlignmentAttribute.as_int()));
	}
	if (const auto VAlignmentAttribute = componentNode.attribute("VAlignment"))
	{
		label->setVerticalAlignment(static_cast<cocos2d::TextVAlignment>(VAlignmentAttribute.as_int()));
	}

	label->retain();
}

LabelComponent::~LabelComponent()
{
	label->removeFromParent();
	label->removeAllChildren();

	label->release();
}

cocos2d::Label* LabelComponent::getLabel()
{
	return label;
}

cocos2d::Label* LabelComponent::getLabel() const
{
	return label;
}

void LabelComponent::setPosition(const cocos2d::Vec2& position)
{
	label->setPosition(position);
}

void LabelComponent::setRotation(float angle)
{
	label->setRotation(angle);
}

std::string LabelComponent::getFontName() const
{
	return label->getSystemFontName();
}

void LabelComponent::setFontName(const std::string& fontName)
{
	label->setSystemFontName(fontName);
}

float LabelComponent::getFontSize() const
{
	return label->getSystemFontSize();
}

void LabelComponent::setFontSize(float fontSize)
{
	label->setSystemFontSize(fontSize);
}