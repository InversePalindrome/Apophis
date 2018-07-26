/*
Copyright (c) 2018 Inverse Palindrome
Apophis - QueueComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <pugixml.hpp>


class QueueComponent
{
public:
	explicit QueueComponent(const pugi::xml_node& componentNode);

	void save(pugi::xml_node& componentNode) const;

	float getQueueAheadDistance() const;
	void setQueueAheadDistance(float queueAheadDistance);

	float getQueueRadius() const;
	void setQueueRadius(float queueRadius);

	float getBrakeFactor() const;
	void setBrakeFactor(float brakeFactor);

	float getVelocityShrinkFactor() const;
	void setVelocityShrinkFactor(float velocityShrinkFactor);

private:
	float queueAheadDistance;
	float queueRadius;
	float brakeFactor;
	float velocityShrinkFactor;
};