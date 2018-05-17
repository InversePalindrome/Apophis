/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SteerComponent.cpp
InversePalindrome.com
*/


#include "SteerComponent.hpp"


b2Vec2 SteerComponent::getSteeringForce() const
{
	return steeringForce;
}

void SteerComponent::setSteeringForce(const b2Vec2& steeringForce)
{
	this->steeringForce = steeringForce;
}