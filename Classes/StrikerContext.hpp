/*
Copyright (c) 2018 Inverse Palindrome
Apophis - StrikerContext.hpp
InversePalindrome.com
*/


#pragma once

#include "BodyComponent.hpp"
#include "SpeedComponent.hpp"
#include "WanderComponent.hpp"
#include "HealthComponent.hpp"
#include "VisionComponent.hpp"

#include <entityx/Entity.h>


struct StrikerContext
{
	entityx::Entity striker;
	BodyComponent& body;
	const SpeedComponent& speed;
	WanderComponent& wander;
	const VisionComponent& vision;
	const HealthComponent& health;
};