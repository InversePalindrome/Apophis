/*
Copyright (c) 2018 Inverse Palindrome
Apophis - FlockComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <pugixml.hpp>


class FlockComponent
{
public:
	FlockComponent();

	void load(const pugi::xml_node& componentNode);
	void save(pugi::xml_node& componentNode) const;

	void display();

	int getGroupID() const;
	void setGroupID(int groupID);

	float getGroupRadius() const;
	void setGroupRadius(float groupRadius);

	float getAlignmentForce() const;
	void setAlignmentForce(float alignmentForce);

	float getCohesionForce() const;
	void setCohesionForce(float cohesionForce);

	float getSeparationForce() const;
	void setSeparationForce(float separationForce);

private:
	int groupID;
	float groupRadius;

	float alignmentForce;
	float cohesionForce;
	float separationForce;
};