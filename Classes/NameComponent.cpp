/*
Copyright (c) 2018 Inverse Palindrome
Apophis - NameComponent.cpp
InversePalindrome.com
*/


#include "NameComponent.hpp"

#include <imgui.h>


void NameComponent::load(const pugi::xml_node& componentNode)
{
    setName(componentNode.text().as_string());
}

void NameComponent::save(pugi::xml_node& componentNode) const
{
    componentNode.set_name("Name");

    componentNode.text().set(name.c_str());
}

void NameComponent::display()
{
    if (ImGui::TreeNode("Name"))
    {
        name.resize(64);

        ImGui::InputText("Name", name.data(), name.length());

        name.erase(std::find(std::begin(name), std::end(name), '\0'), std::end(name));

        ImGui::TreePop();
    }
}

std::string NameComponent::getName() const
{
    return name;
}

void NameComponent::setName(const std::string& name)
{
    this->name = name;
}