/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PatrolComponent.cpp
InversePalindrome.com
*/


#include "PatrolComponent.hpp"

#include "CCIMGUI.h"

#include <imgui.h>


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
	componentNode.set_name("Patrol");

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
		ImGui::SameLine();
		if (CCIMGUI::getInstance()->imageButton("#AddButton", 50, 50))
		{
			addPatrolPoint({ 0.f, 0.f });
		}
		ImGui::SameLine();
		if (ImGui::Button("Clear"))
		{
			clearPatrolPoints();
		}
		
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
}

b2Vec2 PatrolComponent::getCurrentPatrolPoint() const
{
	return patrolPoints.front();
}

void PatrolComponent::addPatrolPoint(const b2Vec2& patrolPoint)
{
	patrolPoints.push_back(patrolPoint);
}

void PatrolComponent::removePatrolPoint(std::size_t patrolPointIndex)
{
	patrolPoints.erase(std::begin(patrolPoints) + patrolPointIndex);
}

void PatrolComponent::clearPatrolPoints()
{
	patrolPoints.clear();
}

void PatrolComponent::nextPatrolPoint()
{
	std::rotate(std::begin(patrolPoints), std::begin(patrolPoints) + 1, std::end(patrolPoints));
}

bool PatrolComponent::hasPatrolPoints() const
{
	return !patrolPoints.empty();
}