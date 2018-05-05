/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - PatrolComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <tinyxml2/tinyxml2.h>

#include <Box2D/Common/b2Math.h>

#include <vector>


class PatrolComponent
{
public:
	explicit PatrolComponent(const tinyxml2::XMLElement* componentNode);

	void nextPoint();

	b2Vec2 getCurrentPoint() const;

	bool hasPoints() const;

private:
	std::vector<b2Vec2> path;
	std::size_t currentIndex;
};