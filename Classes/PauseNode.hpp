/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PauseNode.hpp
InversePalindrome.com
*/


#pragma once

#include <cocos/2d/CCNode.h>


class PauseNode : public cocos2d::Node
{
public:
	virtual bool init() override;

	CREATE_FUNC(PauseNode);
};