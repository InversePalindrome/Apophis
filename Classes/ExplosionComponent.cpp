/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ExplosionComponent.cpp
InversePalindrome.com
*/


#include "ExplosionComponent.hpp"


ExplosionComponent::ExplosionComponent(const tinyxml2::XMLElement* componentNode) :
	explosionTime(1.f)
{
	if (const auto* explosionName = componentNode->Attribute("name"))
	{
		this->explosionName = explosionName;
	}
	if (const auto* explosionTime = componentNode->Attribute("time"))
	{
		this->explosionTime = std::stof(explosionTime);
	}
}

std::string ExplosionComponent::getExplosionName() const
{
	return explosionName;
}

float ExplosionComponent::getExplosionTime() const
{
	return explosionTime;
}
void ExplosionComponent::setExplosionTime(float explosionTime)
{
	this->explosionTime = explosionTime;
}