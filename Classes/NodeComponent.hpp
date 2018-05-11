/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - NodeComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <cocos/2d/CCNode.h>


class NodeComponent
{
public:
	explicit NodeComponent(cocos2d::Node* node);

	cocos2d::Node* getNode();
	cocos2d::Node* getNode() const;

	void addChild(cocos2d::Node* node);

	void removeFromParent();

	cocos2d::Vec2 getPosition() const;
	void setPosition(const cocos2d::Vec2& position);

	float getRotation() const;
	void setRotation(float rotation);

private:
	cocos2d::Node* node;
};