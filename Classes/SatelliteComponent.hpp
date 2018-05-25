/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SatelliteComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <tinyxml2/tinyxml2.h>


class SatelliteComponent
{
public:
	explicit SatelliteComponent(const tinyxml2::XMLElement* componentNode);

	int getPrimaryID() const;
	void setPrimaryID(int primaryID);

private:
	int primaryID;
};