/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - SettingsScene.hpp
InversePalindrome.com
*/


#pragma once

#include "KeyboardManager.hpp"

#include <cocos/2d/CCLayer.h>
#include <cocos/2d/CCScene.h>
#include <cocos/ui/UIRadioButton.h>


class SettingsScene : public cocos2d::Layer
{
public:
	~SettingsScene();

	virtual bool init() override;
	virtual void update(float dt) override;

	CREATE_FUNC(SettingsScene);

	static cocos2d::Scene* scene();

private:
	KeyboardManager* keyboardManager;
	cocos2d::ui::RadioButtonGroup* controlButtons;
};