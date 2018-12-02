/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PatrolContext.hpp
InversePalindrome.com
*/


#pragma once

#include "BodyComponent.hpp"
#include "SpeedComponent.hpp"
#include "PatrolComponent.hpp"

#include <entityx/Entity.h>


struct PatrolContext
{
	entityx::Entity patrolEntity;
	BodyComponent& body;
	const SpeedComponent& speed;
	PatrolComponent& patrol;
};