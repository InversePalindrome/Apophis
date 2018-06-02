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

#include <Box2D/Common/b2Math.h>

#include <cocos/math/Vec2.h>

#include <tinyxml2/tinyxml2.h>


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
	b2Vec2 targetPosition;
};

struct CreateBody
{
	mutable entityx::Entity entity;
	const tinyxml2::XMLElement* bodyNode;
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

struct ScheduleOnce
{
	mutable entityx::Entity entity;
	std::function<void(float)> callback;
	float delay;
	std::string key;
};

struct Schedule
{
	mutable entityx::Entity entity;
	std::function<void(float)> callback;
	float interval;
	unsigned int repeat;
	float delay;
	std::string key;
};

struct Unschedule
{
	mutable entityx::Entity entity;
	std::string key;
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