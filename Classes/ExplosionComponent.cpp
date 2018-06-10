/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ExplosionComponent.cpp
InversePalindrome.com
*/


#include "ExplosionComponent.hpp"


ExplosionComponent::ExplosionComponent(const pugi::xml_node& componentNode) :
	explosionTime(1.f)
{
	if (const auto explosionNameAttribute = componentNode.attribute("name"))
	{
		explosionName = explosionNameAttribute.as_string();
	}
	if (const auto explosionTimeAttribute = componentNode.attribute("time"))
	{
		explosionTime = explosionTimeAttribute.as_float();
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