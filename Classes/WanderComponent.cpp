/*
Copyright (c) 2018 Inverse Palindrome
Apophis - WanderComponent.cpp
InversePalindrome.com
*/


#include "WanderComponent.hpp"

#include <cocos/base/ccRandom.h>

#include <boost/math/constants/constants.hpp>


WanderComponent::WanderComponent(const pugi::xml_node& componentNode) :
	wanderDistance(5.f),
	wanderRadius(1.f),
	wanderRate(1.f),
	wanderAngle(cocos2d::RandomHelper::random_real(0.f, 2.f * boost::math::constants::pi<float>()))
{
	if (const auto wanderDistanceAttribute = componentNode.attribute("distance"))
	{
		setWanderDistance(wanderDistanceAttribute.as_float());
	}
	if (const auto wanderRadiusAttribute = componentNode.attribute("radius"))
	{
		setWanderRadius(wanderRadiusAttribute.as_float());
	}
	if (const auto wanderRateAttribute = componentNode.attribute("rate"))
	{
		setWanderRate(wanderRateAttribute.as_float());
	}
}

float WanderComponent::getWanderDistance() const
{
	return wanderDistance;
}

void WanderComponent::setWanderDistance(float wanderDistance)
{
	this->wanderDistance = wanderDistance;
}

float WanderComponent::getWanderRadius() const
{
	return wanderRadius;
}

void WanderComponent::setWanderRadius(float wanderRadius)
{
	this->wanderRadius = wanderRadius;
}

float WanderComponent::getWanderRate() const
{
	return wanderRate;
}

void WanderComponent::setWanderRate(float wanderRate)
{
	this->wanderRate = wanderRate;
}

float& WanderComponent::getWanderAngle()
{
	return wanderAngle;
}