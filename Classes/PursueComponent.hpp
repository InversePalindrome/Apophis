/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PursueComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <pugixml.hpp>


class PursueComponent
{
public:
	explicit PursueComponent(const pugi::xml_node& componentNode);

	float getPredictionTime() const;
	void setPredictionTime(float predictionTime);

private:
	float predictionTime;
};