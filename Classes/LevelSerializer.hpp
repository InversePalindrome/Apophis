/*
Copyright (c) 2018 Inverse Palindrome
Apophis - LevelSerializer.hpp
InversePalindrome.com
*/


#pragma once

#include <entityx/Entity.h>

#include <Box2D/Common/b2Math.h>

#include <string>


namespace LevelSerializer
{
	void saveLevel(entityx::EntityManager& entityManager, const b2Vec2& mapDimensions, const std::string& filename);
};