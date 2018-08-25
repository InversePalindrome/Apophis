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

template<typename T>
struct ComponentLoaded
{
	T component;
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

template<typename T>
struct DestroyJoint
{
	entityx::ComponentHandle<T> joint;
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