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

private:
	cocos2d::Node* node;
};