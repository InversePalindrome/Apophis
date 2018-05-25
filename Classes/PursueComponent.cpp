/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PursueComponent.cpp
InversePalindrome.com
*/


#include "PursueComponent.hpp"

#include <string>


PursueComponent::PursueComponent(const tinyxml2::XMLElement* componentNode) :
	predictionTime(5.f)
{
	if (const auto* predictionTime = componentNode->GetText())
	{
		this->predictionTime = std::stof(predictionTime);
	}
}

float PursueComponent::getPredictionTime() const
{
	return predictionTime;
}

void PursueComponent::setPredictionTime(float predictionTime)
{
	this->predictionTime = predictionTime;
}