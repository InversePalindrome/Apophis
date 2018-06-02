/*
Copyright (c) 2018 Inverse Palindrome
Apophis - QueueComponent.cpp
InversePalindrome.com
*/


#include "QueueComponent.hpp"

#include <string>


QueueComponent::QueueComponent(const tinyxml2::XMLElement* componentNode) :
	queueAheadDistance(5.f),
	queueRadius(1.f),
	brakeFactor(0.8f),
	velocityShrinkFactor(0.3f)
{
	if (const auto* queueAheadDistance = componentNode->Attribute("distance"))
	{
		this->queueAheadDistance = std::stof(queueAheadDistance);
	}
	if (const auto* queueRadius = componentNode->Attribute("radius"))
	{
		this->queueRadius = std::stof(queueRadius);
	}
	if (const auto* brakeFactor = componentNode->Attribute("brake"))
	{
		this->brakeFactor = std::stof(brakeFactor);
	}
	if (const auto* velocityShrinkFactor = componentNode->Attribute("shrink"))
	{
		this->velocityShrinkFactor = std::stof(velocityShrinkFactor);
	}
}

float QueueComponent::getQueueAheadDistance() const
{
	return queueAheadDistance;
}

void QueueComponent::setQueueAheadDistance(float queueAheadDistance)
{
	this->queueAheadDistance = queueAheadDistance;
}

float QueueComponent::getQueueRadius() const
{
	return queueRadius;
}

void QueueComponent::setQueueRadius(float queueRadius)
{
	this->queueRadius = queueRadius;
}

float QueueComponent::getBrakeFactor() const
{
	return brakeFactor;
}

void QueueComponent::setBrakeFactor(float brakeFactor)
{
	this->brakeFactor = brakeFactor;
}

float QueueComponent::getVelocityShrinkFactor() const
{
	return velocityShrinkFactor;
}

void QueueComponent::setVelocityShrinkFactor(float velocityShrinkFactor)
{
	this->velocityShrinkFactor = velocityShrinkFactor;
}