/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - VisionComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <tinyxml2/tinyxml2.h>


class VisionComponent
{
public:
	explicit VisionComponent(const tinyxml2::XMLElement* componentNode);

	float getVisionRadius() const;
	void setVisionRadius(float visionRadius);

private:
	float visionRadius;
};