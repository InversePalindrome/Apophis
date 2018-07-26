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
		setExplosionName(explosionNameAttribute.as_string());
	}
	if (const auto explosionTimeAttribute = componentNode.attribute("time"))
	{
		setExplosionTime(std::chrono::milliseconds(explosionTimeAttribute.as_int()));
	}
}

void ExplosionComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.set_name("Explosion");

	componentNode.append_attribute("name") = explosionName.c_str();
	componentNode.append_attribute("time") = explosionTime.count();
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