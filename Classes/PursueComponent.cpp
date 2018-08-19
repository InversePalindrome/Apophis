/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PursueComponent.cpp
InversePalindrome.com
*/


#include "PursueComponent.hpp"

#include <imgui.h>


PursueComponent::PursueComponent() :
	predictionTime(5000)
{
}

void PursueComponent::load(const pugi::xml_node& componentNode)
{
	setPredictionTime(std::chrono::milliseconds(componentNode.text().as_int()));
}

void PursueComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.set_name("Pursue");

	componentNode.text().set(predictionTime.count());
}

void PursueComponent::display()
{
	if (ImGui::TreeNode("Pursue"))
	{
		if (auto predictionTimeCount = static_cast<int>(getPredictionTime().count()); ImGui::InputInt("Prediction Time(milliseconds)", &predictionTimeCount))
		{
			setPredictionTime(std::chrono::milliseconds(predictionTimeCount));
		}

		ImGui::TreePop();
	}
}

std::chrono::milliseconds PursueComponent::getPredictionTime() const
{
	return predictionTime;
}

void PursueComponent::setPredictionTime(const std::chrono::milliseconds& predictionTime)
{
	this->predictionTime = predictionTime;
}