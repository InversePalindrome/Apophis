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
	explicit FlockComponent(const pugi::xml_node& componentNode);

	void save(pugi::xml_node& componentNode) const;

	void display();

	int getGroupID() const;
	void setGroupID(int groupID);

	float getGroupRadius() const;
	void setGroupRadius(float groupRadius);

private:
	int groupID;
	float groupRadius;
};