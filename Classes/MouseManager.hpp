/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - MouseManager.hpp
InversePalindrome.com
*/


#pragma once

#include <cocos/2d/CCNode.h>
#include <cocos/base/CCEventMouse.h>


class MouseManager : public cocos2d::Node
{
public:
	MouseManager() = default;
	MouseManager(const MouseManager&) = delete;
	MouseManager& operator= (const MouseManager&) = delete;

	virtual bool init() override;

	CREATE_FUNC(MouseManager);

	cocos2d::Vec2 getMousePosition() const;
	bool isMousePressed() const;

private:
	cocos2d::Vec2 mousePosition;
	bool isPressed;
};