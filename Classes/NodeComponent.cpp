/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - NodeComponent.cpp
InversePalindrome.com
*/


#include "NodeComponent.hpp"


NodeComponent::NodeComponent(cocos2d::Node* node) :
	node(node)
{
}

cocos2d::Node* NodeComponent::getNode()
{
	return node;
}

cocos2d::Node* NodeComponent::getNode() const
{
	return node;
}