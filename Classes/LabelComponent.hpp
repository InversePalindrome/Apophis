/*
Copyright (c) 2018 Inverse Palindrome
Apophis - LabelComponent.hpp
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

private:
	cocos2d::Label* label;
};