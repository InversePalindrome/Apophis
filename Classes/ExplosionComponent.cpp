/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ExplosionComponent.cpp
InversePalindrome.com
*/


#include "ExplosionComponent.hpp"


ExplosionComponent::ExplosionComponent(const pugi::xml_node& componentNode) :
	explosionTime(1000)
{
	if (const auto explosionNameAttribute = componentNode.attribute("name"))
	{
		explosionName = explosionNameAttribute.as_string();
	}
	if (const auto explosionTimeAttribute = componentNode.attribute("time"))
	{
		explosionTime = std::chrono::milliseconds(explosionTimeAttribute.as_int());
	}
}

std::string ExplosionComponent::getExplosionName() const
{
	return explosionName;
}

void ExplosionComponent::setExplosionName(const std::string& explosionName)
{
	this->explosionName = explosionName;
}

std::chrono::milliseconds ExplosionComponent::getExplosionTime() const
{
	return explosionTime;
}
void ExplosionComponent::setExplosionTime(const std::chrono::milliseconds& explosionTime)
{
	this->explosionTime = explosionTime;
}