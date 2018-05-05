/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - HitpointComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <tinyxml2/tinyxml2.h>

#include <string>


template<typename T>
class HitpointComponent
{
public:
	explicit HitpointComponent(const tinyxml2::XMLElement* componentNode);

	int getHitpoints() const;
	void setHitpoints(int hitpoints);

private:
	int hitpoints;
};

template<typename T>
HitpointComponent<T>::HitpointComponent(const tinyxml2::XMLElement* componentNode) :
	hitpoints(0)
{
	if (const auto* hitpoints = componentNode->GetText())
	{
		this->hitpoints = std::stoi(hitpoints);
	}
}

template<typename T>
int HitpointComponent<T>::getHitpoints() const
{
	return hitpoints;
}

template<typename T>
void HitpointComponent<T>::setHitpoints(int hitpoints)
{
	this->hitpoints = hitpoints;
}

using HealthComponent = HitpointComponent<struct Health>;
using DamageComponent = HitpointComponent<struct Damage>;