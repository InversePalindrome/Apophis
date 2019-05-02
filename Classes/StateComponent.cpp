/*
Copyright (c) 2018 Inverse Palindrome
Apophis - StateComponent.cpp
InversePalindrome.com
*/


#include "StateComponent.hpp"

#include <imgui.h>


StateComponent::StateComponent() :
    state(State::Undefined)
{
}

void StateComponent::load(const pugi::xml_node& componentNode)
{
    setState(State::_from_string(componentNode.text().as_string()));
}

void StateComponent::save(pugi::xml_node& componentNode) const
{
    componentNode.set_name("State");

    componentNode.text().set(getState()._to_string());
}

void StateComponent::display()
{
    if (ImGui::TreeNode("State"))
    {
        if (ImGui::BeginCombo("State", state._to_string()))
        {
            for (const auto state : State::_values())
            {
                if (ImGui::Selectable(state._to_string()))
                {
                    setState(state);
                }
            }

            ImGui::EndCombo();
        }


        ImGui::TreePop();
    }
}

State StateComponent::getState() const
{
    return state;
}

void StateComponent::setState(State state)
{
    this->state = state;
}