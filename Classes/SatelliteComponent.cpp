/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SatelliteComponent.hpp
InversePalindrome.com
*/


#include "SatelliteComponent.hpp"

#include <imgui.h>


SatelliteComponent::SatelliteComponent() :
	primaryID(-1),
	orbitDirection(1)
{
}

void SatelliteComponent::load(const pugi::xml_node& componentNode)
{
	if (const auto primaryIDAttribute = componentNode.attribute("primaryID"))
	{
		setPrimaryID(primaryIDAttribute.as_int());
	}
	if (const auto orbitDirectionAttribute = componentNode.attribute("direction"))
	{
		setOrbitDirection(orbitDirectionAttribute.as_int());
	}
}

void SatelliteComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.set_name("Satellite");
	
	componentNode.append_attribute("primaryID") = getPrimaryID();
	componentNode.append_attribute("direction") = getOrbitDirection();
}

void SatelliteComponent::display()
{
	if (ImGui::TreeNode("Satellite"))
	{
		ImGui::TreePop();
	}
}

int SatelliteComponent::getPrimaryID() const
{
	return primaryID;
}

void SatelliteComponent::setPrimaryID(int primaryID) 
{
	this->primaryID = primaryID;
}

std::int8_t SatelliteComponent::getOrbitDirection() const
{
	return orbitDirection;
}

void SatelliteComponent::setOrbitDirection(std::int8_t orbitDirection)
{
	this->orbitDirection = orbitDirection;
}