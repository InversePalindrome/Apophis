/*
Copyright (c) 2018 Inverse Palindrome
Apophis - Map.hpp
InversePalindrome.com
*/


#pragma once

#include "EntityFactory.hpp"

#include <entityx/entityx.h>

#include <Box2D/Common/b2Math.h>

#include <cocos/2d/CCNode.h>

#include <map>
#include <string>


class Map
{
public:
	Map(EntityFactory& entityFactory, entityx::EventManager& eventManager);

	void load(const std::string& fileName);

	void setMainNode(cocos2d::Node* mainNode);

	b2Vec2 getDimensions() const;

private: 
	cocos2d::Node* mainNode;
	EntityFactory& entityFactory;
	entityx::EventManager& eventManager;

	b2Vec2 dimensions;
	std::size_t maxEntityCount;

	void generateMap(const std::vector<std::string>& entities, const std::vector<int>& weights);
};