/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ObjectType.hpp
InversePalindrome.com
*/


#pragma once

#include <enum.h>


BETTER_ENUM(ObjectType, int,
	Player = (1 << 0),
	Enemy = (1 << 1),
	Projectile = (1 << 2),
	Explosion = (1 << 3),
	Asteroid = (1 << 4),
	Item = (1 << 5),
	Alive = Player | Enemy,
	Obstacle = Asteroid | Item)