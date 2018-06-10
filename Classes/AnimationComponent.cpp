/*
Copyright (c) 2018 Inverse Palindrome
Apophis - AnimationComponent.cpp
InversePalindrome.com
*/


#include "AnimationComponent.hpp"

#include <cocos/2d/CCSpriteFrameCache.h>


AnimationComponent::AnimationComponent(const pugi::xml_node& componentNode)
{
	for (const auto actionNode : componentNode.children())
	{
		auto* animation = cocos2d::Animation::create();

		for (const auto frameNode : actionNode.children("Frame"))
		{
			animation->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(frameNode.text().as_string()));
		}

		if (const auto delayAttribute = actionNode.attribute("delay"))
		{
			animation->setDelayPerUnit(delayAttribute.as_float());
		}

		animations.insert(actionNode.value(), animation);
	}
}

cocos2d::Animation* AnimationComponent::getAnimation(const std::string& action) const
{
	return animations.at(action);
}

bool AnimationComponent::hasAnimation(const std::string& action) const
{
	return animations.find(action) != std::cend(animations);
}