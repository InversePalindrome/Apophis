/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ArriveComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <pugixml.hpp>


class ArriveComponent
{
public:
	ArriveComponent();

	void load(const pugi::xml_node& componentNode);
	void save(pugi::xml_node& componentNode) const;

	void display();

	float getSlowRadius() const;
	void setSlowRadius(float slowRadius);

private:
	float slowRadius;
};