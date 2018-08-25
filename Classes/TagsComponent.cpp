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
	componentNode.set_name("Tags");

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
		ImGui::SameLine();
		if (ImGui::Button("Clear"))
		{
			clearTags();
		}

		int i = 0;

		for (auto tagItr = std::begin(tags); tagItr != std::end(tags);)
		{
			tagItr->resize(64);

			ImGui::PushID(i++);

			ImGui::InputText("Tag", tagItr->data(), tagItr->length());
			ImGui::SameLine();
			if (CCIMGUI::getInstance()->imageButton("#RemoveButton", 50, 50))
			{
				tagItr = tags.erase(tagItr);
			}
			else
			{
				++tagItr;
			}

			ImGui::PopID();
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

void TagsComponent::clearTags()
{
	tags.clear();
}

bool TagsComponent::hasTag(const std::string& tag) const
{
	return std::find(std::cbegin(tags), std::cend(tags), tag) != std::cend(tags);
}