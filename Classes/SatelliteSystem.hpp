/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SatelliteSystem.hpp
InversePalindrome.com
*/


#pragma once

#include <entityx/System.h>


class SatelliteSystem : public entityx::System<SatelliteSystem>
{
public:
	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;
};