/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ActionSystem.cpp
InversePalindrome.com
*/


#include "ActionSystem.hpp"
#include "SpriteComponent.hpp"
#include "AnimationComponent.hpp"

#include <cocos/2d/CCActionInterval.h>


void ActionSystem::configure(entityx::EventManager& eventManager)
{
	eventManager.subscribe<PlayAnimation>(*this);
}

void ActionSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{

}

void ActionSystem::receive(const PlayAnimation& event)
{
	auto sprite = event.entity.component<SpriteComponent>();
	auto animation = event.entity.component<AnimationComponent>();

	if (sprite && animation && animation->hasAnimation(event.animation))
	{
		auto* animate = cocos2d::Animate::create(animation->getAnimation(event.animation));

		if (event.loop)
		{
			sprite->runAction(cocos2d::RepeatForever::create(animate));
		}
		else
		{
			sprite->runAction(animate);
		}
	}
}