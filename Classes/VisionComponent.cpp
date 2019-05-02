/*
Copyright (c) 2018 Inverse Palindrome
Apophis - VisionComponent.cpp
InversePalindrome.com
*/


#include "VisionComponent.hpp"

#include <imgui.h>


VisionComponent::VisionComponent() :
    visionDistance(10.f)
{
}

void VisionComponent::load(const pugi::xml_node& componentNode)
{
    setVisionDistance(componentNode.text().as_float());
}

void VisionComponent::save(pugi::xml_node& componentNode) const
{
    componentNode.set_name("Vision");

    componentNode.text().set(getVisionDistance());
}

void VisionComponent::display()
{
    if (ImGui::TreeNode("Vision"))
    {
        ImGui::InputFloat("Distance", &visionDistance);

        ImGui::TreePop();
    }
}

float VisionComponent::getVisionDistance() const
{
    return visionDistance;
}

void VisionComponent::setVisionDistance(float visionDistance)
{
    this->visionDistance = visionDistance;
}