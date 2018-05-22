/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SteerForce.cpp
InversePalindrome.com
*/


#include "SteerForce.hpp"


b2Vec2 SteerForce::getSteeringForce() const
{
	return steeringForce;
}

void SteerForce::setSteeringForce(const b2Vec2& steeringForce)
{
	this->steeringForce = steeringForce;
}