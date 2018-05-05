/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - KeyboardManager.cpp
InversePalindrome.com
*/


#include "KeyboardManager.hpp"

#include <cocos/base/CCEventDispatcher.h>
#include <cocos/base/CCEventListenerKeyboard.h>


bool KeyboardManager::init()
{
	if (!Node::init())
	{
		return false;
	}
	
	auto* keyboardListener = cocos2d::EventListenerKeyboard::create();
	
	keyboardListener->onKeyPressed = [this](auto keyCode, auto* event)
	{
		activeKeys.insert(keyCode);
	};
	keyboardListener->onKeyReleased = [this](auto keyCode, auto* event)
	{
		activeKeys.erase(keyCode);
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	return true;
}

std::unordered_set<cocos2d::EventKeyboard::KeyCode> KeyboardManager::getActiveKeys() const
{
	return activeKeys;
}

bool KeyboardManager::isKeyPressed() const
{
	return !activeKeys.empty();
}

bool KeyboardManager::isKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode) const
{
	return activeKeys.count(keyCode);
}