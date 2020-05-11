/*
Copyright (c) 2018 Inverse Palindrome
Apophis - DropComponent.cpp
InversePalindrome.com
*/


#include "DropComponent.hpp"

#include "CCIMGUI.h"

#include <imgui.h>

#include <nfd.h>

#include <boost/range/combine.hpp>
#include <boost/range/adaptor/reversed.hpp>


void DropComponent::load(const pugi::xml_node& componentNode)
{
    for (const auto itemNode : componentNode.children("Item"))
    {
        if (const auto filenameAttribute = itemNode.attribute("filename"),
            weightAttribute = itemNode.attribute("weight");
            filenameAttribute && weightAttribute)
        {
            addItem(filenameAttribute.as_string(), weightAttribute.as_int());
        }
    }
}

void DropComponent::save(pugi::xml_node& componentNode) const
{
    componentNode.set_name("Drop");

    for (const auto& filenameAndWeight : boost::combine(itemFilenames, weights))
    {
        auto itemNode = componentNode.append_child("Item");
        itemNode.append_attribute("filename") = boost::get<0>(filenameAndWeight).c_str();
        itemNode.append_attribute("weight") = boost::get<1>(filenameAndWeight);
    }
}

void DropComponent::display()
{
    if (ImGui::TreeNode("Drop"))
    {
        ImGui::SameLine();
        if (CCIMGUI::getInstance()->imageButton("#AddButton", 50, 50))
        {
            addItem("", 1);
        }
        ImGui::SameLine();
        if (ImGui::Button("Clear"))
        {
            clearItems();
        }

        int i = 0;
        std::vector<int> indexesToRemove;

        for (auto& filenameAndWeight : boost::range::combine(itemFilenames, weights))
        {
            ImGui::PushID(i);

            auto& itemFilename = boost::get<0>(filenameAndWeight);
            itemFilename.resize(64);

            ImGui::PushItemWidth(650.f);
            ImGui::InputText("Item Filename", itemFilename.data(), itemFilename.length());
            ImGui::PopItemWidth();
            ImGui::SameLine();
            if (ImGui::Button("Select"))
            {
                nfdchar_t* filename = nullptr;

                if (NFD_OpenDialog("xml", nullptr, &filename) == NFD_OKAY)
                {
                    itemFilename = filename;
                }
            }

            ImGui::SameLine();
            ImGui::PushItemWidth(220.f);
            ImGui::InputInt("Weight", &boost::get<1>(filenameAndWeight));
            ImGui::PopItemWidth();

            ImGui::SameLine();
            if (CCIMGUI::getInstance()->imageButton("#RemoveButton", 50, 50))
            {
                indexesToRemove.push_back(i);
            }

            ++i;
            ImGui::PopID();
        }

        for (auto i : boost::adaptors::reverse(indexesToRemove))
        {
            itemFilenames.erase(std::begin(itemFilenames) + i);
            weights.erase(std::begin(weights) + i);
        }

        ImGui::TreePop();
    }
}

const std::vector<std::string>& DropComponent::getItemFilenames() const
{
    return itemFilenames;
}

const std::vector<int>& DropComponent::getWeights() const
{
    return weights;
}

void DropComponent::addItem(const std::string& itemFilename, int weight)
{
    itemFilenames.push_back(itemFilename);
    weights.push_back(weight);
}

void DropComponent::removeItem(const std::string& itemFilename)
{
    auto index = std::find(std::cbegin(itemFilenames), std::cend(itemFilenames), itemFilename) - std::cbegin(itemFilenames);

    itemFilenames.erase(std::cbegin(itemFilenames) + index);
    weights.erase(std::cbegin(weights) + index);
}

void DropComponent::clearItems()
{
    itemFilenames.clear();
    weights.clear();
}