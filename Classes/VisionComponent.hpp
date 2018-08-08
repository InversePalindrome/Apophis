/*
Copyright (c) 2018 Inverse Palindrome
Apophis - VisionComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <pugixml.hpp>


class VisionComponent
{
public:
	explicit VisionComponent(const pugi::xml_node& componentNode);

	void save(pugi::xml_node& componentNode) const;

	void display();

	float getVisionDistance() const;
	void setVisionDistance(float visionDistance);

private:
	float visionDistance;
};