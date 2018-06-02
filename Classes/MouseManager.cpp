/*
Copyright (c) 2018 Inverse Palindrome
Apophis - MouseManager.cpp
InversePalindrome.com
*/


#include "MouseManager.hpp"

#include <cocos/base/CCEventDispatcher.h>
#include <cocos/base/CCEventListenerMouse.h>


bool MouseManager::init()
{
	if (!Node::init())
	{
		return false;
	}

	auto* mouseListener = cocos2d::EventListenerMouse::create();

	mouseListener->onMouseMove = [this](auto* event)
	{
		mousePosition = convertToNodeSpace({ event->getCursorX(), event->getCursorY() });
	};
	mouseListener->onMouseDown = [this](auto* event)
	{
		isPressed = true;
	};
	mouseListener->onMouseUp = [this](auto* event)
	{
		isPressed = false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	return true;
}

cocos2d::Vec2 MouseManager::getMousePosition() const
{
	return mousePosition;
}

bool MouseManager::isMousePressed() const
{
	return isPressed;
}