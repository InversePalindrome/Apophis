/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - SettingsNode.hpp
InversePalindrome.com
*/


#pragma once

#include "KeyAction.hpp"
#include "KeyboardManager.hpp"

#include <cocos/2d/CCNode.h>
#include <cocos/2d/CCScene.h>
#include <cocos/ui/UIRadioButton.h>


class SettingsNode : public cocos2d::Node
{
public:
	SettingsNode();
	~SettingsNode();

	virtual bool init() override;
	virtual void update(float dt) override;

	CREATE_FUNC(SettingsNode);

	static cocos2d::Scene* scene();

private:
	KeyboardManager* keyboardManager;
	cocos2d::ui::RadioButtonGroup* controlButtons;

	KeyAction moveRight;
	KeyAction moveLeft;
	KeyAction moveUp;
	KeyAction moveDown;
};