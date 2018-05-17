/*
Copyright (c) 2018 Inverse Palindrome
Apophis - HudNode.hpp
InversePalindrome.com
*/


#pragma once

#include <cocos/2d/CCNode.h>
#include <cocos/ui/UILoadingBar.h>


class HudNode : public cocos2d::Node
{
public:
	~HudNode();

	virtual bool init() override;
	
	CREATE_FUNC(HudNode);

	cocos2d::ui::LoadingBar* getHealthBar();

private:
	cocos2d::ui::LoadingBar* healthBar;
};