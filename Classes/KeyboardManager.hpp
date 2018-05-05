/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - KeyboardManager.hpp
InversePalindrome.com
*/


#pragma once

#include <cocos/2d/CCNode.h>
#include <cocos/base/CCEventKeyboard.h>

#include <unordered_set>


class KeyboardManager : public cocos2d::Node
{
public:
	KeyboardManager() = default;
	KeyboardManager(const KeyboardManager&) = delete;
	KeyboardManager& operator= (const KeyboardManager&) = delete;

	virtual bool init() override;

	CREATE_FUNC(KeyboardManager);

	std::unordered_set<cocos2d::EventKeyboard::KeyCode> getActiveKeys() const;

	bool isKeyPressed() const;
	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode) const;

private:
	std::unordered_set<cocos2d::EventKeyboard::KeyCode> activeKeys;
};