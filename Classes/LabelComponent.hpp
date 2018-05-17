/*
Copyright (c) 2018 Inverse Palindrome
Apophis - LabelComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <tinyxml2/tinyxml2.h>

#include <cocos/2d/CCLabel.h>


class LabelComponent 
{
public:
	explicit LabelComponent(const tinyxml2::XMLElement* componentNode);
	~LabelComponent();

	cocos2d::Label* getLabel();
	cocos2d::Label* getLabel() const;

private:
	cocos2d::Label* label;
};