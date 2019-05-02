/*
Copyright (c) 2018 Inverse Palindrome
Apophis - AnimationComponent.cpp
InversePalindrome.com
*/


#include "AnimationComponent.hpp"

#include "CCIMGUI.h"

#include <cocos/2d/CCAnimationCache.h>

#include <imgui.h>


AnimationComponent::AnimationComponent() :
    animationToAdd(State::Undefined, { "", 1 })
{
}

AnimationComponent::~AnimationComponent()
{
    for (const auto& animation : animations)
    {
        animation.second.first->release();
    }
}

void AnimationComponent::load(const pugi::xml_node& componentNode)
{
    for (const auto animationNode : componentNode.children("Animation"))
    {
        if (const auto stateAttribute = animationNode.attribute("state"),
            nameAttribute = animationNode.attribute("name"),
            loopsAttribute = animationNode.attribute("loops");
            stateAttribute && nameAttribute && loopsAttribute)
        {
            if (auto * animation = addAnimation(State::_from_string(stateAttribute.as_string()), nameAttribute.as_string()))
            {
                animation->setLoops(loopsAttribute.as_int());
            }
        }
    }
}

void AnimationComponent::save(pugi::xml_node& componentNode) const
{
    componentNode.set_name("Animation");

    for (const auto& [state, animation] : animations)
    {
        auto animationNode = componentNode.append_child("Animation");
        animationNode.append_attribute("state") = state._to_string();
        animationNode.append_attribute("name") = animation.second.c_str();
        animationNode.append_attribute("loops") = animation.first->getLoops();
    }
}

void AnimationComponent::display()
{
    if (ImGui::TreeNode("Animation"))
    {
        ImGui::SameLine();

        if (CCIMGUI::getInstance()->imageButton("#AddButton", 50, 50))
        {
            ImGui::OpenPopup("Add Animation");
        }

        ImGui::SameLine();

        if (ImGui::Button("Clear"))
        {
            clearAnimations();
        }

        if (auto isOpen = true; ImGui::BeginPopupModal("Add Animation", &isOpen, ImGuiWindowFlags_AlwaysAutoResize))
        {
            if (ImGui::BeginCombo("State", animationToAdd.first._to_string()))
            {
                for (const auto state : State::_values())
                {
                    if (ImGui::Selectable(state._to_string()))
                    {
                        animationToAdd.first = state;
                    }
                }

                ImGui::EndCombo();
            }

            animationToAdd.second.first.resize(64);
            ImGui::InputText("Animation Name", animationToAdd.second.first.data(), animationToAdd.second.first.length());

            ImGui::SameLine();

            ImGui::InputInt("Loops", &animationToAdd.second.second);

            if (ImGui::Button("Add"))
            {
                if (auto * animation = addAnimation(animationToAdd.first, animationToAdd.second.first.c_str()))
                {
                    animation->setLoops(animationToAdd.second.second);
                }

                animationToAdd = { State::Undefined, {"", 1} };

                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }

        for (auto animationItr = std::cbegin(animations); animationItr != std::cend(animations);)
        {
            ImGui::Text("State: %s | Name: %s | Loops: %d", animationItr->first._to_string(), animationItr->second.second.c_str(), animationItr->second.first->getLoops());
            ImGui::SameLine();
            if (CCIMGUI::getInstance()->imageButton("#RemoveButton", 50, 50))
            {
                animationItr = animations.erase(animationItr);
            }
            else
            {
                ++animationItr;
            }
        }

        ImGui::TreePop();
    }
}

cocos2d::Animation* AnimationComponent::addAnimation(State state, const std::string& animationName)
{
    auto* animation = cocos2d::AnimationCache::getInstance()->getAnimation(animationName);

    if (animation)
    {
        animation->retain();
        animations.emplace(state, std::make_pair(animation, animationName));
    }

    return animation;
}

void AnimationComponent::removeAnimation(State state)
{
    animations.erase(state);
}

void AnimationComponent::clearAnimations()
{
    for (auto& animation : animations)
    {
        animation.second.first->release();
    }

    animations.clear();
}

cocos2d::Animation* AnimationComponent::getAnimation(State state)
{
    return animations[state].first;
}

const cocos2d::Animation* AnimationComponent::getAnimation(State state) const
{
    return animations.at(state).first;
}

bool AnimationComponent::hasAnimation(State state) const
{
    return animations.count(state);
}