/*
Copyright (c) 2018 Inverse Palindrome
Apophis - LevelSerializer.hpp
InversePalindrome.com
*/


#pragma once

#include <entityx/Entity.h>

#include <Box2D/Common/b2Math.h>

#include <string>
#include <unordered_map>


namespace LevelSerializer
{
	void saveLevel(const std::unordered_map<std::string, entityx::Entity>& entities, const b2Vec2& mapDimensions, const std::string& filename);
};