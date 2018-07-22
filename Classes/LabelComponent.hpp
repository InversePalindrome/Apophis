/*
Copyright (c) 2018 Inverse Palindrome
Apophis - LabelComponent.cpp
InversePalindrome.com
*/


#pragma once

#include "NodeComponent.hpp"

#include <cocos/2d/CCLabel.h>

#include <pugixml.hpp>


class LabelComponent : public NodeComponent
{
public:
	explicit LabelComponent(const pugi::xml_node& componentNode);

	std::string getText() const;
	void setText(const std::string& text);

	std::string getFontName() const;
	void setFontName(const std::string& fontName);

	float getFontSize() const;
	void setFontSize(float fontSize);

	cocos2d::TextHAlignment getHorizontalAlignment() const;
	void setHorizontalAlignment(cocos2d::TextHAlignment horizontalAlignment);

	cocos2d::TextVAlignment getVerticalAlignment() const;
	void setVerticalAlignment(cocos2d::TextVAlignment verticalAlignment);

	cocos2d::Color4B getTextColor() const;
	void setTextColor(const cocos2d::Color4B& textColor);

private:
	cocos2d::Label* label;
};