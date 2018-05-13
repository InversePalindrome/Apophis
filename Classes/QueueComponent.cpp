/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - QueueComponent.cpp
InversePalindrome.com
*/


#include "QueueComponent.hpp"

#include <string>


QueueComponent::QueueComponent(const tinyxml2::XMLElement* componentNode) :
	queueDistance(5.f),
	shrinkFactor(0.3f),
	steeringBrakeFactor(0.8f)
{
	if (const auto* queueDistance = componentNode->Attribute("distance"))
	{
		this->queueDistance = std::stof(queueDistance);
	}
	if (const auto* shrinkFactor = componentNode->Attribute("shrinkFactor"))
	{
		this->shrinkFactor = std::stof(shrinkFactor);
	}
	if (const auto* steeringBrakeFactor = componentNode->Attribute("brakeFactor"))
	{
		this->steeringBrakeFactor = std::stof(steeringBrakeFactor);
	}
}

float QueueComponent::getQueueDistance() const
{
	return queueDistance;
}

void QueueComponent::setQueueDistance(float queueDistance)
{
	this->queueDistance = queueDistance;
}

float QueueComponent::getShrinkingFactor() const
{
	return shrinkFactor;
}

void QueueComponent::setShrinkingFactor(float shrinkFactor)
{
	this->shrinkFactor = shrinkFactor;
}

float QueueComponent::getSteeringBrakeFactor() const
{
	return steeringBrakeFactor;
}

void QueueComponent::setSteeringBrakeFactor(float steeringBrakeFactor)
{
	this->steeringBrakeFactor = steeringBrakeFactor;
}