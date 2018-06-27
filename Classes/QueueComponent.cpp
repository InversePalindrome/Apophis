/*
Copyright (c) 2018 Inverse Palindrome
Apophis - QueueComponent.cpp
InversePalindrome.com
*/


#include "QueueComponent.hpp"


QueueComponent::QueueComponent(const pugi::xml_node& componentNode) :
	queueAheadDistance(5.f),
	queueRadius(1.f),
	brakeFactor(0.8f),
	velocityShrinkFactor(0.3f)
{
	if (const auto queueAheadDistanceAttribute = componentNode.attribute("distance"))
	{
		setQueueAheadDistance(queueAheadDistanceAttribute.as_float());
	}
	if (const auto queueRadiusAttribute = componentNode.attribute("radius"))
	{
		setQueueRadius(queueRadiusAttribute.as_float());
	}
	if (const auto brakeFactorAttribute = componentNode.attribute("brake"))
	{
		setBrakeFactor(brakeFactorAttribute.as_float());
	}
	if (const auto velocityShrinkFactorAttribute = componentNode.attribute("shrink"))
	{
       setVelocityShrinkFactor(velocityShrinkFactorAttribute.as_float());
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