/*
Copyright (c) 2018 Inverse Palindrome
Apophis - LevelParser.hpp
InversePalindrome.com
*/


#pragma once

#include <entityx/Event.h>
#include <entityx/Entity.h>

#include <box2d/Common/b2Math.h>


namespace LevelParser
{
	void parseLevel(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, b2Vec2& mapDimensions, const std::string& filename);
};