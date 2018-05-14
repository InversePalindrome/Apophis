/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - SteerComponent.cpp
InversePalindrome.com
*/


#include "SteerComponent.hpp"


SteerComponent::SteerComponent() :
	steeringForce(0.f, 0.f)
{
}

b2Vec2 SteerComponent::getSteeringForce() const
{
	return steeringForce;
}

void SteerComponent::setSteeringForce(const b2Vec2& steeringForce)
{
	this->steeringForce = steeringForce;
}