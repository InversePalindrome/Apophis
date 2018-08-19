/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SpeedBoostComponent.cpp
InversePalindrome.com
*/


#include "SpeedBoostComponent.hpp"

#include <imgui.h>


SpeedBoostComponent::SpeedBoostComponent() :
	speedBoostRatio(2.f),
	speedBoostDuration(1000)
{
}

void SpeedBoostComponent::load(const pugi::xml_node& componentNode)
{
	if (const auto speedBoostRatioAttribute = componentNode.attribute("ratio"))
	{
		setSpeedBoostRatio(speedBoostRatioAttribute.as_float());
	}
	if (const auto speedBoostDurationAttribute = componentNode.attribute("duration"))
	{
		setSpeedBoostDuration(std::chrono::milliseconds(speedBoostDurationAttribute.as_int()));
	}
}

void SpeedBoostComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.set_name("SpeedBoost");

	componentNode.append_attribute("ratio") = getSpeedBoostRatio();
	componentNode.append_attribute("duration") = getSpeedBoostDuration().count();
}

void SpeedBoostComponent::display()
{
	if (ImGui::TreeNode("SpeedBoost"))
	{
		ImGui::InputFloat("Ratio", &speedBoostRatio);

		if (auto durationCount = static_cast<int>(getSpeedBoostDuration().count()); ImGui::InputInt("Duration(milliseconds)", &durationCount))
		{
			setSpeedBoostDuration(std::chrono::milliseconds(durationCount));
		}

		ImGui::TreePop();
	}
}

float SpeedBoostComponent::getSpeedBoostRatio() const
{
	return speedBoostRatio;
}

void SpeedBoostComponent::setSpeedBoostRatio(float speedBoostRatio)
{
	this->speedBoostRatio = speedBoostRatio;
}

std::chrono::milliseconds SpeedBoostComponent::getSpeedBoostDuration() const
{
	return speedBoostDuration;
}

void SpeedBoostComponent::setSpeedBoostDuration(const std::chrono::milliseconds& speedBoostDuration)
{
	this->speedBoostDuration = speedBoostDuration;
}