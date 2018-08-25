/*
Copyright (c) 2018 Inverse Palindrome
Apophis - AnimationComponent.cpp
InversePalindrome.com
*/


#include "AnimationComponent.hpp"

#include <imgui.h>


void AnimationComponent::load(const pugi::xml_node& componentNode)
{

}

void AnimationComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.set_name("Animation");
}

void AnimationComponent::display()
{
	if (ImGui::TreeNode("Animation"))
	{

		ImGui::TreePop();
	}
}

void AnimationComponent::addAnimation(State state, cocos2d::Animation* animation)
{
	animations.emplace(state, animation);
}

void AnimationComponent::removeAnimation(State state)
{
	animations.erase(state);
}

const cocos2d::Animation* AnimationComponent::getAnimation(State state) const
{
	return animations.at(state);
}

bool AnimationComponent::hasAnimation(State state) const
{
	return animations.count(state);
}