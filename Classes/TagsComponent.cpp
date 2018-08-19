/*
Copyright (c) 2018 Inverse Palindrome
Apophis - TagsComponent.cpp
InversePalindrome.com
*/


#include "TagsComponent.hpp"

#include "CCIMGUI.h"

#include <imgui.h>


void TagsComponent::load(const pugi::xml_node& componentNode)
{
	for (const auto tagNode : componentNode.children("Tag"))
	{
		addTag(tagNode.text().as_string());
	}
}

void TagsComponent::save(pugi::xml_node& componentNode) const
{
	for (const auto& tag : tags)
	{
		componentNode.append_child("Tag").text().set(tag.c_str());
	}
}

void TagsComponent::display()
{
	if (ImGui::TreeNode("Tags"))
	{
		ImGui::SameLine();

		if (CCIMGUI::getInstance()->imageButton("#AddButton", 50, 50))
		{
			addTag();
		}

		std::vector<std::string> tagsToRemove;
		int i = 0;

		for (auto& tag : tags)
		{
			tag.resize(64);

			ImGui::PushID(i++);

			ImGui::InputText("Tag", tag.data(), tag.length());
			ImGui::SameLine();
			if (CCIMGUI::getInstance()->imageButton("#RemoveButton", 50, 50))
			{
				tagsToRemove.push_back(tag);
			}

			ImGui::PopID();
		}
		
		for (const auto& tagToRemove : tagsToRemove)
		{
			removeTag(tagToRemove);
		}

		ImGui::TreePop();
	}
}

void TagsComponent::addTag(const std::string& tag)
{
	tags.push_back(tag);
}

void TagsComponent::removeTag(const std::string& tag)
{
	tags.erase(std::remove(std::begin(tags), std::end(tags), tag), std::end(tags));
}

bool TagsComponent::hasTag(const std::string& tag) const
{
	return std::find(std::cbegin(tags), std::cend(tags), tag) != std::cend(tags);
}