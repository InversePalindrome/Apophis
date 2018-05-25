/*
Copyright (c) 2018 Inverse Palindrome
Apophis - OrbitalSystem.hpp
InversePalindrome.com
*/


#pragma once

#include <entityx/System.h>


class OrbitalSystem : public entityx::System<OrbitalSystem>
{
public:
	explicit OrbitalSystem(entityx::EntityManager& entityManager);

	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;

private:
	entityx::EntityManager& entityManager;
};