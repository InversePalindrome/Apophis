/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PursueComponent.cpp
InversePalindrome.com
*/


#include "PursueComponent.hpp"


PursueComponent::PursueComponent(const pugi::xml_node& componentNode) :
	predictionTime(componentNode.text().as_int(5.f))
{
}

void PursueComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.set_name("Pursue");

	componentNode.text().set(predictionTime.count());
}

std::chrono::milliseconds PursueComponent::getPredictionTime() const
{
	return predictionTime;
}

void PursueComponent::setPredictionTime(const std::chrono::milliseconds& predictionTime)
{
	this->predictionTime = predictionTime;
}