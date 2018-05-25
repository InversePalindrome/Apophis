/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PursueComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <tinyxml2/tinyxml2.h>


class PursueComponent
{
public:
	explicit PursueComponent(const tinyxml2::XMLElement* componentNode);

	float getPredictionTime() const;
	void setPredictionTime(float predictionTime);

private:
	float predictionTime;
};