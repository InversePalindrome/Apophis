/*
Copyright (c) 2018 Inverse Palindrome
Apophis - DroneContext.hpp
InversePalindrome.com
*/


#pragma once

#include "BodyComponent.hpp"
#include "FlockComponent.hpp"
#include "SpeedComponent.hpp"
#include "ArriveComponent.hpp"
#include "WanderComponent.hpp"
#include "VisionComponent.hpp"
#include "FollowComponent.hpp"

#include <entityx/Entity.h>


struct DroneContext
{
	entityx::Entity entity;
	BodyComponent& body;
	WanderComponent& wander;
	const SpeedComponent& speed;
	const ArriveComponent& arrive;
	const FollowComponent& follow;
	const FlockComponent& flock;
	const VisionComponent& vision;
};