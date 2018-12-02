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
	void load(const pugi::xml_node& componentNode);
	void save(pugi::xml_node& componentNode) const;

	void display();

	b2Vec2 getCurrentPatrolPoint() const;

	void addPatrolPoint(const b2Vec2& patrolPoint);

	void removePatrolPoint(std::size_t patrolPointIndex);
	void clearPatrolPoints();

	void nextPatrolPoint();

	bool hasPatrolPoints() const;

private:
	std::vector<b2Vec2> patrolPoints;
};