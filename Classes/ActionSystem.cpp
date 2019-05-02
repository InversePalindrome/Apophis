/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ActionSystem.cpp
InversePalindrome.com
*/


#include "ActionSystem.hpp"
#include "SpriteComponent.hpp"

#include <cocos/2d/CCActionInterval.h>


void ActionSystem::configure(entityx::EventManager& eventManager)
{
    eventManager.subscribe<StateChanged>(*this);
}

void ActionSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
}

void ActionSystem::receive(const StateChanged& event)
{
    if (auto [sprite, animation] = event.entity.components<SpriteComponent, AnimationComponent>(); sprite && animation && animation->hasAnimation(event.state))
    {
        sprite->runAction(cocos2d::Animate::create(animation->getAnimation(event.state)));
    }
}