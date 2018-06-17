/*
Copyright (c) 2018 Inverse Palindrome
Apophis - AnimationComponent.cpp
InversePalindrome.com
*/


#include "AnimationComponent.hpp"

#include <cocos/2d/CCSpriteFrameCache.h>


AnimationComponent::AnimationComponent(const pugi::xml_node& componentNode)
{
	for (const auto animationNode : componentNode.children())
	{
		auto* animation = cocos2d::Animation::create();
		animation->retain();
		
		for (const auto frameNode : animationNode.children("Frame"))
		{
			animation->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(frameNode.text().as_string()));
		}

		if (const auto delayAttribute = animationNode.attribute("delay"))
		{
			animation->setDelayPerUnit(delayAttribute.as_float());
		}
		
		animations.emplace(Action::_from_string(animationNode.name()), animation);
	}
}

AnimationComponent::~AnimationComponent()
{
	for (const auto& animation : animations)
	{
		animation.second->release();
	}
}

cocos2d::Animation* AnimationComponent::getAnimation(Action action) const
{
	return animations.at(action);
}

bool AnimationComponent::hasAnimation(Action action) const
{
	return animations.find(action) != std::cend(animations);
}