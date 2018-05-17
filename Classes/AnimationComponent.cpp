/*
Copyright (c) 2018 Inverse Palindrome
Apophis - AnimationComponent.cpp
InversePalindrome.com
*/


#include "AnimationComponent.hpp"

#include <cocos/2d/CCSpriteFrameCache.h>


AnimationComponent::AnimationComponent(const tinyxml2::XMLElement* componentNode)
{
	for (const auto* actionNode = componentNode->FirstChildElement("Action"); actionNode; actionNode = actionNode->NextSiblingElement("Action"))
	{
		auto* animation = cocos2d::Animation::create();
 	
		for (const auto* frameNode = actionNode->FirstChildElement("Frame"); frameNode; frameNode = frameNode->NextSiblingElement("Frame"))
		{
			if (const auto* frameName = frameNode->GetText())
			{
				animation->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
			}
		}

		if (const auto* name = actionNode->Attribute("name"))
		{
			animations.insert(name, animation);
		}
		if (const auto* delay = actionNode->Attribute("delay"))
		{
			animation->setDelayPerUnit(std::stof(delay));
		}
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