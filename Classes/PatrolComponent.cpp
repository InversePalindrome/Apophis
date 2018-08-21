/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PatrolComponent.cpp
InversePalindrome.com
*/


#include "PatrolComponent.hpp"

#include "CCIMGUI.h"

#include <imgui.h>


PatrolComponent::PatrolComponent() :
	patrolIndex(0u)
{
}

void PatrolComponent::load(const pugi::xml_node& componentNode)
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
			int i = 0;

			for (auto patrolPointItr = std::begin(patrolPoints); patrolPointItr != std::end(patrolPoints);)
			{
				ImGui::PushID(i++);

				ImGui::InputFloat2("Point(X, Y)", &patrolPointItr->x);

				ImGui::SameLine();

				if (CCIMGUI::getInstance()->imageButton("#RemoveButton", 50, 50))
				{
					patrolPointItr = patrolPoints.erase(patrolPointItr);
				}
				else
				{
					++patrolPointItr;
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