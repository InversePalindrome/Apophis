/*
Copyright (c) 2018 Inverse Palindrome
Apophis - Events.hpp
InversePalindrome.com
*/


#pragma once

#include <entityx/Entity.h>

#include <tinyxml2/tinyxml2.h>

#include <Box2D/Common/b2Math.h>

#include <cocos/math/Vec2.h>


struct EntityParsed
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

struct SetBodyPosition
{
	mutable entityx::Entity entity;
	b2Vec2 position;
};

struct SetNodePosition
{
	mutable entityx::Entity entity;
	cocos2d::Vec2 position;
};

struct SetBodyAngle
{
	mutable entityx::Entity entity;
	float angle;
};

struct SetNodeRotation
{
	mutable entityx::Entity entity;
	float rotation;
};

struct SetLinearVelocity
{
	mutable entityx::Entity entity;
	b2Vec2 velocity;
};

struct SetAngularVelocity
{
	mutable entityx::Entity entity;
	float velocity;
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

template<typename T>
struct Steer
{
	mutable entityx::Entity entity;
};

using Seek = Steer<struct SeekBehavior>;
using Flee = Steer<struct FleeBehavior>;
using Pursue = Steer<struct PursueBehavior>;
using Evade = Steer<struct EvadeBehavior>;
using Arrive = Steer<struct ArriveBehavior>;
using Follow = Steer<struct FollowBehavior>;
using Wander = Steer<struct WanderBehavior>;
using Patrol = Steer<struct PatrolBehavior>;
using Avoid = Steer<struct AvoidBehavior>;
using Align = Steer<struct AlignBehavior>;
using Cohesion = Steer<struct CohesionBehavior>;
using Separate = Steer<struct SeparateBehavior>;
using Queue = Steer<struct QueueBehavior>;