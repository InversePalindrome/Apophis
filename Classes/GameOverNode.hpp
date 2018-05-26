/*
Copyright (c) 2018 Inverse Palindrome
Apophis - GameOverNode.hpp
InversePalindrome.com
*/


#pragma once

#include <cocos/2d/CCNode.h>


class GameOverNode : public cocos2d::Node
{
public:
	virtual bool init() override;

	CREATE_FUNC(GameOverNode);
};