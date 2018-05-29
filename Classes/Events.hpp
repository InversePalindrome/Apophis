/*
Copyright (c) 2018 Inverse Palindrome
Apophis - Events.hpp
InversePalindrome.com
*/


#pragma once

#include "AreaQuery.hpp"
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

struct SetNodePosition
{
	mutable entityx::Entity entity;
	cocos2d::Vec2 position;
};

struct SetNodeRotation
{
	mutable entityx::Entity entity;
	float rotation;
};

struct SetBodyPosition
{
	mutable entityx::Entity entity;
	b2Vec2 position;
};

struct SetBodyAngle
{
	mutable entityx::Entity entity;
	float angle;
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

struct ApplyLinearImpulse
{
	mutable entityx::Entity entity;
	b2Vec2 direction;
};

struct ApplyAngularImpulse
{
	mutable entityx::Entity entity;
	int direction;
};

struct ApplyLinearForce
{
	mutable entityx::Entity entity;
	b2Vec2 direction;
};

struct ApplyAngularForce
{
	mutable entityx::Entity entity;
	int direction;
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

struct Seek
{
	mutable entityx::Entity entity;
	b2Vec2 targetPosition;
};

struct Flee
{
	mutable entityx::Entity entity;
	b2Vec2 targetPosition;
};

struct Pursue
{
	mutable entityx::Entity entity;
	b2Vec2 targetPosition;
	b2Vec2 targetVelocity;
};

struct Evade
{
	mutable entityx::Entity entity;
	b2Vec2 targetPosition;
	b2Vec2 targetVelocity;
};

struct Arrive
{
	mutable entityx::Entity entity;
	b2Vec2 targetPosition;
};

struct Follow
{
	mutable entityx::Entity entity;
	float targetVision;
	b2Vec2 targetPosition;
	b2Vec2 targetVelocity;
};

struct Wander
{
	mutable entityx::Entity entity;
};

struct Avoid
{
	mutable entityx::Entity entity;
};

struct Orbit
{
	mutable entityx::Entity entity;
	b2Vec2 primaryPosition;
};

struct Align
{

};

struct Cohesion
{

};

struct Separate
{

};

struct Queue
{

};

struct Face
{
	mutable entityx::Entity entity;
	b2Vec2 targetPosition;
};