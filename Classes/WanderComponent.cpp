/*
Copyright (c) 2018 Inverse Palindrome
Apophis - WanderComponent.cpp
InversePalindrome.com
*/


#include "WanderComponent.hpp"

#include <cocos/base/ccRandom.h>

#include <string>


WanderComponent::WanderComponent(const tinyxml2::XMLElement* componentNode) :
	wanderDistance(5.f),
	wanderRadius(1.f),
	wanderRate(0.1f),
	wanderAngle(cocos2d::RandomHelper::random_real(0.f, 2.f * PI))
{
	if (const auto* wanderDistance = componentNode->Attribute("distance"))
	{
		this->wanderDistance = std::stof(wanderDistance);
	}
	if (const auto* wanderRadius = componentNode->Attribute("radius"))
	{
		this->wanderRadius = std::stof(wanderRadius);
	}
	if (const auto* wanderRate = componentNode->Attribute("rate"))
	{
		this->wanderRate = std::stof(wanderRate);
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

float WanderComponent::getWanderAngle() const
{
	return wanderAngle;
}

float& WanderComponent::getWanderAngle()
{
	return wanderAngle;
}