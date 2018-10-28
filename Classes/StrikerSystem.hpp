/*
Copyright (c) 2018 Inverse Palindrome
Apophis - StrikerSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "StrikerContext.hpp"

#include <entityx/System.h>

#include <beehive/beehive.hpp>


class StrikerSystem : public entityx::System<StrikerSystem>, public entityx::Receiver<StrikerSystem>
{
public:
	explicit StrikerSystem(entityx::EventManager& eventManager);

	virtual void configure(entityx::EventManager& eventManager) override;
	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;

private:
	beehive::Tree<StrikerContext> strikerTree;
};