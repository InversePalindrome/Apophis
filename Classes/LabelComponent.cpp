/*
Copyright (c) 2018 Inverse Palindrome
Apophis - LabelComponent.cpp
InversePalindrome.com
*/


#include "LabelComponent.hpp"


LabelComponent::LabelComponent(const pugi::xml_node& componentNode) :
	NodeComponent(cocos2d::Label::create(), componentNode),
	label(static_cast<cocos2d::Label*>(getNode()))
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
	
	const auto rAttribute = componentNode.attribute("R");
	const auto gAttribute = componentNode.attribute("G");
	const auto bAttribute = componentNode.attribute("B");

	if (rAttribute && gAttribute && bAttribute)
	{
		label->setTextColor(cocos2d::Color4B(cocos2d::Color3B(rAttribute.as_uint(), gAttribute.as_uint(), bAttribute.as_uint())));
	}
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

cocos2d::Color4B LabelComponent::getTextColor() const
{
	return label->getTextColor();
}

void LabelComponent::setTextColor(const cocos2d::Color4B& textColor)
{
	label->setTextColor(textColor);
}