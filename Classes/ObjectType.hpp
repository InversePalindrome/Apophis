/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - ObjectType.hpp
InversePalindrome.com
*/


#pragma once

#include <enum.h>


BETTER_ENUM(ObjectType, int,
	Undefined = 0,
	Player = (1 << 0),
	Enemy = (1 << 1),
	Projectile = (1 << 2),
	Explosion = (1 << 3),
	Asteroid = (1 << 4),
	Alive = Player | Enemy,
	Obstacle = Asteroid)