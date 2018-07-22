/*
Copyright (c) 2018 Inverse Palindrome
Apophis - Map.hpp
InversePalindrome.com
*/


#pragma once

#include <cocos/2d/CCNode.h>

#include <Box2D/Common/b2Math.h>

#include <string>


class Map
{
public:
	Map();

	void init(cocos2d::Node* gameNode);

	void load(const std::string& fileName);

	b2Vec2 getDimensions() const;

private: 
	cocos2d::Node* gameNode;

	b2Vec2 dimensions;
};