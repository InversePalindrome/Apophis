/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PursueComponent.cpp
InversePalindrome.com
*/


#include "PursueComponent.hpp"


PursueComponent::PursueComponent(const pugi::xml_node& componentNode) :
	predictionTime(componentNode.text().as_float(5.f))
{
}

float PursueComponent::getPredictionTime() const
{
	return predictionTime;
}

void PursueComponent::setPredictionTime(float predictionTime)
{
	this->predictionTime = predictionTime;
}