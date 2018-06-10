/*
Copyright (c) 2018 Inverse Palindrome
Apophis - Map.hpp
InversePalindrome.com
*/


#pragma once

#include "EntityParser.hpp"

#include <cocos/2d/CCNode.h>

#include <Box2D/Common/b2Math.h>

#include <entityx/entityx.h>

#include <map>
#include <string>


class Map
{
public:
	Map(EntityParser& entityParser, entityx::EventManager& eventManager);

	void load(const std::string& fileName);

	void setMainNode(cocos2d::Node* mainNode);

	b2Vec2 getDimensions() const;

private: 
	cocos2d::Node* mainNode;
	EntityParser& entityParser;
	entityx::EventManager& eventManager;

	b2Vec2 dimensions;
	std::size_t maxEntityCount;

	void generateMap(const std::vector<std::string>& entities, const std::vector<int>& weights);
};