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

	void save(pugi::xml_node& componentNode) const;

	void display();

	const std::vector<b2Vec2>& getPatrolPoints() const;

	std::size_t getPatrolIndex() const;
	void setPatrolIndex(std::size_t patrolIndex);

private:
	std::vector<b2Vec2> patrolPoints;
	std::size_t patrolIndex;
};