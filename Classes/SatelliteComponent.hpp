/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SatelliteComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <pugixml.hpp>


class SatelliteComponent
{
public:
	explicit SatelliteComponent(const pugi::xml_node& componentNode);

	int getPrimaryID() const;
	void setPrimaryID(int primaryID);

private:
	int primaryID;
};