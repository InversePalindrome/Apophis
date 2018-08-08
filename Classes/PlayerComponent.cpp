/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PlayerComponent.cpp
InversePalindrome.com
*/


#include "PlayerComponent.hpp"

#include <imgui.h>


void PlayerComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.set_name("Player");
}

void PlayerComponent::display()
{
	if (ImGui::TreeNode("Player"))
	{
		ImGui::TreePop();
	}
}