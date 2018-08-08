/*
Copyright (c) 2018 Inverse Palindrome
Apophis - RegenBoostComponent.cpp
InversePalindrome.com
*/


#include "RegenBoostComponent.hpp"

#include <imgui.h>


RegenBoostComponent::RegenBoostComponent(const pugi::xml_node& componentNode) :
	hitpointBoost(1.f),
	regenRate(1000),
	regenDuration(5000)
{
	if (const auto hitpointBoostAttribute = componentNode.attribute("boost"))
	{
		setHitpointBoost(hitpointBoostAttribute.as_float());
	}
	if (const auto regenRateAttribute = componentNode.attribute("rate"))
	{
		setRegenRate(std::chrono::milliseconds(regenRateAttribute.as_int()));
	}
	if (const auto regenDurationAttribute = componentNode.attribute("duration"))
	{
		setRegenDuration(std::chrono::milliseconds(regenDurationAttribute.as_int()));
	}
}

void RegenBoostComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.set_name("RegenBoost");

	componentNode.append_attribute("boost") = getHitpointBoost();
	componentNode.append_attribute("rate") = getRegenRate().count();
	componentNode.append_attribute("duration") = getRegenDuration().count();
}

void RegenBoostComponent::display()
{
	if (ImGui::TreeNode("RegenBoost"))
	{
		ImGui::TreePop();
	}
}

float RegenBoostComponent::getHitpointBoost() const
{
	return hitpointBoost;
}

void RegenBoostComponent::setHitpointBoost(float hitpointBoost)
{
	this->hitpointBoost = hitpointBoost;
}

std::chrono::milliseconds RegenBoostComponent::getRegenRate() const
{
	return regenRate;
}

void RegenBoostComponent::setRegenRate(const std::chrono::milliseconds& regenRate)
{
	this->regenRate = regenRate;
}

std::chrono::milliseconds RegenBoostComponent::getRegenDuration() const
{
	return regenDuration;
}

void RegenBoostComponent::setRegenDuration(const std::chrono::milliseconds& regenDuration)
{
	this->regenDuration = regenDuration;
}