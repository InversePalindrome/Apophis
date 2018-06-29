/*
Copyright (c) 2018 Inverse Palindrome
Apophis - Events.hpp
InversePalindrome.com
*/


#pragma once

#include "Sound.hpp"
#include "Animation.hpp"
#include "AreaQuery.hpp"
#include "ObjectType.hpp"
#include "RayCastQuery.hpp"

#include <entityx/Entity.h>

#include <pugixml.hpp>


struct EntityCreated
{
	mutable entityx::Entity entity;
};

struct CreateBody
{
	mutable entityx::Entity entity;
	pugi::xml_node bodyNode;
};

struct CreateDistanceJoint
{
	mutable entityx::Entity jointEntity;
	mutable entityx::Entity entityA;
	mutable entityx::Entity entityB;
};

struct ShootProjectile
{
	mutable entityx::Entity shooter;
};

struct PlayAudio
{
	mutable entityx::Entity entity;
	Sound sound;
	bool loop;
};

struct StopAudio
{
	mutable entityx::Entity entity;
	Sound sound;
};

struct StopAllAudio
{
	mutable entityx::Entity entity;
};

struct PlayAnimation
{
	mutable entityx::Entity entity;
	Animation animation;
	bool loop;
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