/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PatrolSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "PatrolContext.hpp"

#include <entityx/System.h>

#include <beehive/beehive.hpp>


class PatrolSystem : public entityx::System<PatrolSystem>
{
public:
	PatrolSystem();

	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;

private:
	beehive::Tree<PatrolContext> patrolTree;
};