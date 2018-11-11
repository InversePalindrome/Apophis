/*
Copyright (c) 2018 Inverse Palindrome
Apophis - LevelParser.hpp
InversePalindrome.com
*/


#pragma once

#include <entityx/Event.h>
#include <entityx/Entity.h>

#include <box2d/Common/b2Math.h>

#include <string>
#include <unordered_map>


namespace LevelParser
{
	void parseLevel(std::unordered_map<std::string, entityx::Entity>& entities, b2Vec2& mapDimensions, entityx::EntityManager& entityManager, entityx::EventManager& eventManager, const std::string& filename);
};