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

	float getVisionDistance() const;
	void setVisionDistance(float visionDistance);

private:
	float visionDistance;
};