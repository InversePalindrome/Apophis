/*
Copyright (c) 2018 Inverse Palindrome
Apophis - AnimationComponent.cpp
InversePalindrome.com
*/


#include "AnimationComponent.hpp"

#include <imgui.h>

#include <cocos/2d/CCSpriteFrameCache.h>


AnimationComponent::AnimationComponent(const pugi::xml_node& componentNode)
{
	for (const auto animationNode : componentNode.children())
	{
		std::vector<std::string> spriteFrameNames;
		
		for (const auto frameNode : animationNode.children("Frame"))
		{
	        spriteFrameNames.push_back(frameNode.text().as_string());
		}
		
		float delay = 0.f;

		if (const auto delayAttribute = animationNode.attribute("delay"))
		{
			delay = delayAttribute.as_float();
		}

		addAnimation(Animation::_from_string(animationNode.name()), spriteFrameNames, delay);
	}
}

AnimationComponent::~AnimationComponent()
{
	for (const auto& animation : animations)
	{
		animation.second.first->release();
	}
}


void AnimationComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.set_name("Animation");

	for (const auto& [name, animation] : animations)
	{
		auto animationNode = componentNode.append_child(name._to_string());

		animationNode.append_attribute("delay") = animation.first->getDelayPerUnit();

		for (const auto& animationFrame : animation.second)
		{
			animationNode.append_child("Frame").text().set(animationFrame.c_str());
		}
	}
}

void AnimationComponent::display()
{
	if (ImGui::TreeNode("Animation"))
	{
		ImGui::TreePop();
	}
}

void AnimationComponent::addAnimation(Animation animationName, const std::vector<std::string>& spriteFrameNames, float delay)
{
	auto* animation = cocos2d::Animation::create();

	for (const auto& spriteFrameName : spriteFrameNames)
	{
		animation->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameName));
	}
	
	animation->retain();

	animations.emplace(animationName, std::make_pair(animation, spriteFrameNames));
}

void AnimationComponent::removeAnimation(Animation animationName)
{
	animations.at(animationName).first->release();

	animations.erase(animationName);
}

cocos2d::Animation* AnimationComponent::getAnimation(Animation animation) const
{
	return animations.at(animation).first;
}

bool AnimationComponent::hasAnimation(Animation animation) const
{
	return animations.count(animation);
}