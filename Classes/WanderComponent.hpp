/*
Copyright (c) 2018 Inverse Palindrome
Apophis - WanderComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <pugixml.hpp>


class WanderComponent
{
public:
	explicit WanderComponent(const pugi::xml_node& componentNode);

	void save(pugi::xml_node& componentNode) const;

	void display();

	float getWanderDistance() const;
	void setWanderDistance(float wanderDistance);

	float getWanderRadius() const;
	void setWanderRadius(float wanderRadius);

	float getWanderRate() const;
	void setWanderRate(float wanderRate);

	float& getWanderAngle();

private:
	float wanderDistance;
	float wanderRadius;
	float wanderRate;
	float wanderAngle;
};