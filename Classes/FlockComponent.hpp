/*
Copyright (c) 2018 Inverse Palindrome
Apophis - FlockComponent.hpp
InversePalindrome.com
*/


#pragma once

#include "tinyxml2/tinyxml2.h"

#include <vector>


class FlockComponent
{
public:
	explicit FlockComponent(const tinyxml2::XMLElement* componentNode);

	float getGroupRadius() const;
	void setGroupRadius(float groupRadius);

	const std::vector<int>& getGroupIDs();

private:
	float groupRadius;
	std::vector<int> groupIDs;
};