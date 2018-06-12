/*
Copyright (c) 2018 Inverse Palindrome
Apophis - Events.hpp
InversePalindrome.com
*/


#pragma once

#include "AreaQuery.hpp"
#include "ObjectType.hpp"
#include "RayCastQuery.hpp"

#include <entityx/Entity.h>

#include <pugixml.hpp>

#include <blaze/math/StaticVector.h>


struct EntityParsed
{
	mutable entityx::Entity entity;
};

struct EntityDied
{
	mutable entityx::Entity entity;
};

struct ShootProjectile
{
	mutable entityx::Entity shooter;
	blaze::StaticVector<float, 2UL> targetPosition;
};

struct CreateBody
{
	entityx::Entity entity;
	const pugi::xml_node bodyNode;
};

struct CreateDistanceJoint
{
	mutable entityx::Entity entityA;
	mutable entityx::Entity entityB;	
};

struct PlayAction
{
	mutable entityx::Entity entity;
	std::string action;
	bool loop;
};

struct ProjectileHit
{
	mutable entityx::Entity projectile;
	mutable entityx::Entity victim;
};

struct PickedUpItem
{
	mutable entityx::Entity entity;
	mutable entityx::Entity itemEntity;
};

struct Avoid
{
	mutable entityx::Entity entity;
	ObjectType object;
};

struct Align
{
	mutable entityx::Entity entity;
};

struct Cohesion
{
	mutable entityx::Entity entity;
};

struct Separate
{
	mutable entityx::Entity entity;
};

struct Queue
{
	mutable entityx::Entity entity;
};