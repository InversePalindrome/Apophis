/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - Events.hpp
InversePalindrome.com
*/


#pragma once

#include <entityx/Entity.h>

#include <tinyxml2/tinyxml2.h>

#include <Box2D/Common/b2Math.h>


struct EntityCreated
{
	mutable entityx::Entity entity;
};

struct EntityDied
{
	mutable entityx::Entity entity;
};

struct MoveEntity
{
	mutable entityx::Entity entity;
	b2Vec2 direction;
};

struct RotateEntity
{
	mutable entityx::Entity entity;
	b2Vec2 direction;
};

struct ShootProjectile
{
	mutable entityx::Entity entity;
	b2Vec2 targetPosition;
};

struct CreateBody
{
	mutable entityx::Entity entity;
	const tinyxml2::XMLElement* bodyData;
};

struct CreateTransform
{
	mutable entityx::Entity parentEntity;
	mutable entityx::Entity childEntity;
};

struct ApplyForce
{
	mutable entityx::Entity entity;
	b2Vec2 force;
};

struct ApplyLinearImpulse
{
	mutable entityx::Entity entity;
	b2Vec2 impulse;
};

struct ApplyAngularImpulse
{
	mutable entityx::Entity entity;
	float impulse;
};

struct SetPosition
{
	mutable entityx::Entity entity;
	b2Vec2 position;
};

struct SetVelocity
{
	mutable entityx::Entity entity;
	b2Vec2 velocity;
};

struct SetRotation
{
	mutable entityx::Entity entity;
	float angle;
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

struct Seek
{
	mutable entityx::Entity entity;
};

struct Flee
{
	mutable entityx::Entity entity;
};

struct Pursue
{
	mutable entityx::Entity entity;
};

struct Evade
{
	mutable entityx::Entity entity;
};

struct Arrive
{
	mutable entityx::Entity entity;
};

struct Follow
{
	mutable entityx::Entity entity;
};

struct Wander
{
	mutable entityx::Entity entity;
};

struct Patrol
{
	mutable entityx::Entity entity;
};

struct Avoid
{
	mutable entityx::Entity entity;
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