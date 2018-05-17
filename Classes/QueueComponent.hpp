/*
Copyright (c) 2018 Inverse Palindrome
Apophis - QueueComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <tinyxml2/tinyxml2.h>


class QueueComponent
{
public:
	explicit QueueComponent(const tinyxml2::XMLElement* componentNode);

	float getQueueDistance() const;
	void setQueueDistance(float queueDistance);

	float getShrinkingFactor() const;
	void setShrinkingFactor(float shrinkingFactor);

	float getSteeringBrakeFactor() const;
	void setSteeringBrakeFactor(float steeringBreakFactor);

private:
	float queueDistance;
	float shrinkFactor;
	float steeringBrakeFactor;
};