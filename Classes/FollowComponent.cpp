/*
Copyright (c) 2018 Inverse Palindrome
Apophis - FollowComponent.cpp
InversePalindrome.com
*/


#include "FollowComponent.hpp"

#include <imgui.h>


FollowComponent::FollowComponent() :
	leaderID(-1),
	distanceFromLeader(5.f)
{
}

void FollowComponent::load(const pugi::xml_node& componentNode)
{
	if (const auto leaderIDAttribute = componentNode.attribute("leaderID"))
	{
		setLeaderID(leaderIDAttribute.as_int());
	}
	if (const auto distanceFromLeaderAttribute = componentNode.attribute("distance"))
	{
		setDistanceFromLeader(distanceFromLeaderAttribute.as_float());
	}
}

void FollowComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.set_name("Follow");

	componentNode.append_attribute("leaderID") = getLeaderID();
	componentNode.append_attribute("distance") = getDistanceFromLeader();
}

void FollowComponent::display()
{
	if (ImGui::TreeNode("Follow"))
	{
		ImGui::InputInt("Leader ID", &leaderID);
		ImGui::InputFloat("Distance", &distanceFromLeader);

		ImGui::TreePop();
	}
}

int FollowComponent::getLeaderID() const
{
	return leaderID;
}

void FollowComponent::setLeaderID(int leaderID)
{
	this->leaderID = leaderID;
}

float FollowComponent::getDistanceFromLeader() const
{
	return distanceFromLeader;
}

void FollowComponent::setDistanceFromLeader(float distanceFromLeader)
{
	this->distanceFromLeader = distanceFromLeader;
}