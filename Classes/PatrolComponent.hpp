/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PatrolComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <Box2D/Common/b2Math.h>

#include <pugixml.hpp>

#include <vector>


class PatrolComponent
{
public:
	explicit PatrolComponent(const pugi::xml_node& componentNode);

	void nextPoint();

	b2Vec2 getCurrentPoint() const;

	bool hasPoints() const;

private:
	std::vector<b2Vec2> path;
	std::size_t currentIndex;
};