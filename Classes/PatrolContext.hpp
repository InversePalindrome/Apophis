/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PatrolContext.hpp
InversePalindrome.com
*/


#pragma once

#include "BodyComponent.hpp"
#include "SpeedComponent.hpp"

#include <entityx/Entity.h>


struct PatrolContext
{
	entityx::Entity patrolEntity;
	b2Vec2 targetPoint;
	BodyComponent& body;
	const SpeedComponent& speed;
};