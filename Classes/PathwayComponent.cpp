/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PathwayComponent.cpp
InversePalindrome.com
*/


#include "PathwayComponent.hpp"

#include "CCIMGUI.h"

#include <imgui.h>


void PathwayComponent::load(const pugi::xml_node& componentNode)
{
	for (const auto pointNode : componentNode.children("Point"))
	{
		if (const auto xPositionAttribute = pointNode.attribute("x"),
			yPositionAttribute = pointNode.attribute("y");
		    xPositionAttribute && yPositionAttribute)
		{
			addPathwayPoint({ xPositionAttribute.as_float(), yPositionAttribute.as_float() });
		}
	}
}

void PathwayComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.set_name("Pathway");

	for (const auto& patrolPoint : pathwayPoints)
	{
		auto pointNode = componentNode.append_child("Point");

		pointNode.append_attribute("x") = patrolPoint.x;
		pointNode.append_attribute("y") = patrolPoint.y;
	}
}

void PathwayComponent::display()
{
	if (ImGui::TreeNode("Pathway"))
	{
		ImGui::SameLine();
		if (CCIMGUI::getInstance()->imageButton("#AddButton", 50, 50))
		{
			addPathwayPoint({ 0.f, 0.f });
		}
		ImGui::SameLine();
		if (ImGui::Button("Clear"))
		{
			clearPathwayPoints();
		}

		int i = 0;

		for (auto patrolPointItr = std::begin(pathwayPoints); patrolPointItr != std::end(pathwayPoints);)
		{
			ImGui::PushID(i++);

			ImGui::InputFloat2("Point(X, Y)", &patrolPointItr->x);

			ImGui::SameLine();

			if (CCIMGUI::getInstance()->imageButton("#RemoveButton", 50, 50))
			{
				patrolPointItr = pathwayPoints.erase(patrolPointItr);
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

void PathwayComponent::addPathwayPoint(const b2Vec2& pathwayPoint)
{
	pathwayPoints.push_back(pathwayPoint);
}

void PathwayComponent::removePathwayPoint(std::size_t pathwayPointIndex)
{
	pathwayPoints.erase(std::begin(pathwayPoints) + pathwayPointIndex);
}

void PathwayComponent::clearPathwayPoints()
{
	pathwayPoints.clear();
}

std::size_t PathwayComponent::getPathwayPointsCount() const
{
	return pathwayPoints.size();
}

bool PathwayComponent::hasPathwayPoints() const
{
	return !pathwayPoints.empty();
}

b2Vec2& PathwayComponent::operator[](std::size_t pathwayPointIndex)
{
	return pathwayPoints[pathwayPointIndex];
}

const b2Vec2& PathwayComponent::operator[](std::size_t pathwayPointIndex) const
{
	return pathwayPoints[pathwayPointIndex];
}

std::vector<b2Vec2>::iterator PathwayComponent::begin()
{
	return std::begin(pathwayPoints);
}

std::vector<b2Vec2>::iterator PathwayComponent::end()
{
	return std::end(pathwayPoints);
}

std::vector<b2Vec2>::const_iterator PathwayComponent::begin() const
{
	return std::cbegin(pathwayPoints);
}

std::vector<b2Vec2>::const_iterator PathwayComponent::end() const
{
	return std::cend(pathwayPoints);
}