/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PatrolComponent.cpp
InversePalindrome.com
*/


#include "PatrolComponent.hpp"

#include "CCIMGUI.h"

#include <imgui.h>


PatrolComponent::PatrolComponent(const pugi::xml_node& componentNode) :
	patrolIndex(0u)
{
	for (const auto pointNode : componentNode.children("Point"))
	{
		if (const auto xPositionAttribute = pointNode.attribute("x"),
			yPositionAttribute = pointNode.attribute("y");
		    xPositionAttribute && yPositionAttribute)
		{
			addPatrolPoint({ xPositionAttribute.as_float(), yPositionAttribute.as_float() });
		}
	}
}

void PatrolComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.set_name("Point");

	componentNode.append_attribute("patrolIndex") = getPatrolIndex();

	for (const auto& patrolPoint : patrolPoints)
	{
		auto pointNode = componentNode.append_child("Point");

		pointNode.append_attribute("x") = patrolPoint.x;
		pointNode.append_attribute("y") = patrolPoint.y;
	}
}

void PatrolComponent::display()
{
	if (ImGui::TreeNode("Patrol"))
	{
		auto isPointsOpen = ImGui::TreeNode("Points");
		ImGui::SameLine();
		if (CCIMGUI::getInstance()->imageButton("#AddButton", 50, 50))
		{
			addPatrolPoint({ 0.f, 0.f });
		}
		
		if (isPointsOpen)
		{
			for (std::size_t i = 0; i < patrolPoints.size(); ++i)
			{
				ImGui::PushID(i);

				ImGui::InputFloat2("Point(X, Y)", &patrolPoints[i].x);

				ImGui::SameLine();

				if (CCIMGUI::getInstance()->imageButton("#RemoveButton", 50, 50))
				{
					removePatrolPoint(i);
				}

				ImGui::PopID();
			}

			ImGui::TreePop();
		}

		ImGui::TreePop();
	}
}

const std::vector<b2Vec2>& PatrolComponent::getPatrolPoints() const
{
	return patrolPoints;
}

std::size_t PatrolComponent::getPatrolIndex() const
{
	return patrolIndex;
}

void PatrolComponent::setPatrolIndex(std::size_t patrolIndex)
{
	this->patrolIndex = patrolIndex;
}

void PatrolComponent::addPatrolPoint(const b2Vec2& patrolPoint)
{
	patrolPoints.push_back(patrolPoint);
}

void PatrolComponent::removePatrolPoint(std::size_t patrolPointIndex)
{
	patrolPoints.erase(std::begin(patrolPoints) + patrolPointIndex);
}