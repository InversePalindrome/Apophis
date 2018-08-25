/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SoundComponent.cpp
InversePalindrome.com
*/


#include "SoundComponent.hpp"

#include "CCIMGUI.h"

#include <imgui.h>

#include <nfd.h>


SoundComponent::SoundComponent() :
	soundID(-1),
	soundToAdd{ State::Undefined, {"", false} }
{
}

void SoundComponent::load(const pugi::xml_node& componentNode)
{
	for (const auto soundNode : componentNode.children())
	{
		if (const auto stateAttribute = soundNode.attribute("state"),
			fileAttribute = soundNode.attribute("file"),
		    loopAttribute = soundNode.attribute("loop");
		    stateAttribute && fileAttribute && loopAttribute)
		{
			addSound(State::_from_string(stateAttribute.as_string()), { fileAttribute.as_string(), loopAttribute.as_bool() });
		}
	}
}

void SoundComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.set_name("Sound");

	for (const auto&[state, soundData] : sounds)
	{
		auto soundNode = componentNode.append_child("Sound");
		soundNode.append_attribute("state") = state._to_string();
		soundNode.append_attribute("file") = soundData.first.c_str();
		soundNode.append_attribute("loop") = soundData.second;
	}
}

void SoundComponent::display()
{
	if (ImGui::TreeNode("Sound"))
	{
		ImGui::SameLine();

		if (CCIMGUI::getInstance()->imageButton("#AddButton", 50, 50))
		{
			ImGui::OpenPopup("Add Sound");
		}

		if (auto isOpen = true; ImGui::BeginPopupModal("Add Sound", &isOpen, ImGuiWindowFlags_AlwaysAutoResize))
		{
			if (ImGui::BeginCombo("State", soundToAdd.first._to_string()))
			{
				for (const auto state : State::_values())
				{
					if (ImGui::Selectable(state._to_string()))
					{
						soundToAdd.first = state;
					}
				}

				ImGui::EndCombo();
			}
			
			soundToAdd.second.first.resize(64);

			ImGui::InputText("File", soundToAdd.second.first.data(), soundToAdd.second.first.length());

			ImGui::SameLine();

			if (ImGui::Button("Select"))
			{
				nfdchar_t* filename = nullptr;

				if (NFD_OpenDialog("mp3,ogg,wav", nullptr, &filename) == NFD_OKAY)
				{
					soundToAdd.second.first = filename;
				}
			}

			ImGui::Checkbox("Loop", &soundToAdd.second.second);

			if (ImGui::Button("Add"))
			{
				addSound(soundToAdd.first, soundToAdd.second);

				soundToAdd = { State::Undefined, {"", false} };

				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}

		int i = 0;

		for (auto soundItr = std::begin(sounds); soundItr != std::end(sounds);)
		{
			ImGui::PushID(i++);

			const auto&[state, soundData] = *soundItr;

			ImGui::Text(("State: " + std::string(state._to_string()) + " | Filename: " + soundData.first).c_str());
			ImGui::SameLine();
			
			auto isLoop = soundItr->second.second;
			ImGui::Checkbox("Loop", &isLoop);
		
			ImGui::SameLine();

			if (CCIMGUI::getInstance()->imageButton("#RemoveButton", 50, 50))
			{
				soundItr = sounds.erase(soundItr);
			}
			else
			{
				++soundItr;
			}

			ImGui::PopID();
		}

		ImGui::TreePop();
	}
}

int SoundComponent::getSoundID() const
{
	return soundID;
}

void SoundComponent::setSoundID(int soundID)
{
	this->soundID = soundID;
}

void SoundComponent::addSound(State state, const std::pair<std::string, bool>& soundFilename)
{
	sounds.emplace(state, soundFilename);
}

void SoundComponent::removeSound(State state)
{
	sounds.erase(state);
}

bool SoundComponent::hasSound(State state) const
{
	return sounds.count(state);
}

const std::pair<std::string, bool>& SoundComponent::getSound(State state) const
{
	return sounds.at(state);
}