/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ActionSystem.hpp
InversePalindrome.com
*/


#pragma once

#include <entityx/System.h>


class ActionSystem : public entityx::System<ActionSystem>, public entityx::Receiver<ActionSystem>
{
public:
	virtual void configure(entityx::EventManager& eventManager) override;
	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;

private:
};