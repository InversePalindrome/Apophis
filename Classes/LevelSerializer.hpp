/*
Copyright (c) 2018 Inverse Palindrome
Apophis - LevelSerializer.hpp
InversePalindrome.com
*/


#pragma once

#include <entityx/Entity.h>

#include <Box2D/Common/b2Math.h>

#include <string>
#include <vector>


namespace LevelSerializer
{
	void saveLevel(const std::vector<entityx::Entity>& entities, const b2Vec2& mapDimensions, const std::string& filename);
};