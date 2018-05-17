/*
Copyright (c) 2018 Inverse Palindrome
Apophis - VisionComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <tinyxml2/tinyxml2.h>


class VisionComponent
{
public:
	explicit VisionComponent(const tinyxml2::XMLElement* componentNode);

	float getVisionDistance() const;
	void setVisionDistance(float visionDistance);

private:
	float visionDistance;
};