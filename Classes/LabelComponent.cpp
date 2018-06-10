/*
Copyright (c) 2018 Inverse Palindrome
Apophis - LabelComponent.cpp
InversePalindrome.com
*/


#include "LabelComponent.hpp"


LabelComponent::LabelComponent(const pugi::xml_node& componentNode) :
	label(cocos2d::Label::create())
{
	if (const auto textAttribute = componentNode.attribute("text"))
	{
		label->setString(textAttribute.as_string());
	}
	if (const auto fontAttribute = componentNode.attribute("font"))
	{
		label->setSystemFontName(fontAttribute.as_string());
	}
	if (const auto fontSizeAttribute = componentNode.attribute("fontSize"))
	{
		label->setSystemFontSize(fontSizeAttribute.as_float());
	}
	if (const auto horizontalAlignmentAttribute = componentNode.attribute("horizontalAlignment"))
	{
		label->setAlignment(static_cast<cocos2d::TextHAlignment>(horizontalAlignmentAttribute.as_int()));
	}
	if (const auto verticalAlignmentAttribute = componentNode.attribute("verticalAlignment"))
	{
		label->setVerticalAlignment(static_cast<cocos2d::TextVAlignment>(verticalAlignmentAttribute.as_int()));
	}

	const auto rAttribute = componentNode.attribute("r");
	const auto gAttribute = componentNode.attribute("g");
	const auto bAttribute = componentNode.attribute("b");
	const auto aAttribute = componentNode.attribute("a");

	if (rAttribute && gAttribute && bAttribute && aAttribute)
	{
		label->setTextColor(cocos2d::Color4B(rAttribute.as_int(), gAttribute.as_int(), bAttribute.as_int(), aAttribute.as_int()));
	}
    
	label->retain();
}

LabelComponent::~LabelComponent()
{
	label->removeFromParentAndCleanup(true);
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