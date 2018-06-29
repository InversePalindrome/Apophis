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

		for (const auto frameNode : animationNode.children("Frame"))
		{
			animation->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(frameNode.text().as_string()));
		}

		if (const auto delayAttribute = animationNode.attribute("delay"))
		{
			animation->setDelayPerUnit(delayAttribute.as_float());
		}

		addAnimation(Animation::_from_string(animationNode.name()), animation);
	}
}

AnimationComponent::~AnimationComponent()
{
	for (const auto& animation : animations)
	{
		animation.second->release();
	}
}

void AnimationComponent::addAnimation(Animation animationName, cocos2d::Animation* animation)
{
	animation->retain();

	animations.emplace(animationName, animation);
}

void AnimationComponent::removeAnimation(Animation animationName)
{
	animations.at(animationName)->release();

	animations.erase(animationName);
}

cocos2d::Animation* AnimationComponent::getAnimation(Animation animation) const
{
	return animations.at(animation);
}

bool AnimationComponent::hasAnimation(Animation animation) const
{
	return animations.count(animation);
}