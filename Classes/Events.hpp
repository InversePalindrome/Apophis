/*
Copyright (c) 2018 Inverse Palindrome
Apophis - Events.hpp
InversePalindrome.com
*/


#pragma once

#include "State.hpp"
#include "AreaQuery.hpp"
#include "ObjectType.hpp"
#include "RayCastQuery.hpp"

#include <entityx/Entity.h>

#include <pugixml.hpp>


struct EntityParsed
{
	mutable entityx::Entity entity;
};

struct EntityDied
{
	mutable entityx::Entity entity;
};

template<typename T>
struct ComponentLoaded
{
	entityx::ComponentHandle<T> component;
	entityx::Entity entity;
};

struct ChangeState
{
	mutable entityx::Entity entity;
	State state;
};

struct StateChanged
{
	mutable entityx::Entity entity;
	State state;
};

struct UpdateTransform
{
	mutable entityx::Entity entity;
};

struct ShootProjectile
{
	mutable entityx::Entity shooter;
};

struct CombatOcurred
{
	mutable entityx::Entity attacker;
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

struct CrossedWaypoint
{
	mutable entityx::Entity patrolEntity;
	mutable entityx::Entity pathEntity;
};