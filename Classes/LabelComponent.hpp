/*
Copyright (c) 2018 Inverse Palindrome
Apophis - LabelComponent.cpp
InversePalindrome.com
*/



#pragma once

#include <cocos/2d/CCLabel.h>

#include <pugixml.hpp>


class LabelComponent
{
public:
	explicit LabelComponent(const pugi::xml_node& componentNode);

	~LabelComponent();

	cocos2d::Label* getLabel();
	cocos2d::Label* getLabel() const;

	void setPosition(const cocos2d::Vec2& position);
	void setRotation(float angle);

	std::string getFontName() const;
	void setFontName(const std::string& fontName);

	float getFontSize() const;
	void setFontSize(float fontSize);

private:
	cocos2d::Label* label;
};