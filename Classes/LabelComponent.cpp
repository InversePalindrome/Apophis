/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - LabelComponent.cpp
InversePalindrome.com
*/


#include "LabelComponent.hpp"


LabelComponent::LabelComponent(const tinyxml2::XMLElement* componentNode) :
	label(cocos2d::Label::create())
{
	if (const auto* text = componentNode->Attribute("text"))
	{
		label->setString(text);
	}
	if (const auto* font = componentNode->Attribute("font"))
	{
		label->setSystemFontName(font);
	}
	if (const auto* fontSize = componentNode->Attribute("fontSize"))
	{
		label->setSystemFontSize(std::stof(fontSize));
	}
	if (const auto* horizontalAlignment = componentNode->Attribute("horizontalAlignment"))
	{
		label->setAlignment(static_cast<cocos2d::TextHAlignment>(std::stoi(horizontalAlignment)));
	}
	if (const auto* verticalAlignment = componentNode->Attribute("verticalAlignment"))
	{
		label->setVerticalAlignment(static_cast<cocos2d::TextVAlignment>(std::stoi(verticalAlignment)));
	}

	const auto* r = componentNode->Attribute("r");
	const auto* g = componentNode->Attribute("g");
	const auto* b = componentNode->Attribute("b");
	const auto* a = componentNode->Attribute("a");

	if (r && g && b && a)
	{
		label->setTextColor(cocos2d::Color4B(std::stof(r), std::stof(g), std::stof(b), std::stof(a)));
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