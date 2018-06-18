/*
Copyright (c) 2018 Inverse Palindrome
Apophis - AnimationComponent.cpp
InversePalindrome.com
*/


#include "AnimationComponent.hpp"

#include <cocos/2d/CCSpriteFrameCache.h>


AnimationComponent::AnimationComponent(const pugi::xml_node& componentNode)
{
	loadAnimations(componentNode);
}

AnimationComponent::~AnimationComponent()
{
	for (const auto& action : actions)
	{
		action.second->release();
	}
	for (const auto& animation : animations)
	{
		animation.second->release();
	}
}

cocos2d::Animation* AnimationComponent::getAnimation(Animation animation) const
{
	return animations.at(animation);
}

cocos2d::Action* AnimationComponent::getAction(Animation animation) const
{
	return actions.at(animation);
}

void AnimationComponent::addAction(Animation animation, cocos2d::Action* action)
{
	action->retain();
	
	actions.emplace(animation, action);
}

void AnimationComponent::removeAction(Animation animation)
{
	actions.at(animation)->release();

	actions.erase(animation);
}

bool AnimationComponent::hasAnimation(Animation animation) const
{
	return animations.count(animation);
}

bool AnimationComponent::hasAction(Animation animation) const
{
	return actions.count(animation);
}

void AnimationComponent::loadAnimations(const pugi::xml_node& componentNode)
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

		animations.emplace(Animation::_from_string(animationNode.name()), animation);
	}
}