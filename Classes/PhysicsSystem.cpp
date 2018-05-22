/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PhysicsSystem.cpp
InversePalindrome.com
*/


#include "PhysicsSystem.hpp"
#include "AnchorPointComponent.hpp"
#include "DistanceJointComponent.hpp"

#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>

#include <sstream>
#include <variant>


PhysicsSystem::PhysicsSystem(entityx::EntityManager& entityManager, entityx::EventManager& eventManager) :
	world({ 0.f, 0.f }),
	collisionManager(eventManager),
	entityManager(entityManager)
{
	world.SetContactListener(&collisionManager);
}

void PhysicsSystem::configure(entityx::EventManager& eventManager)
{
	eventManager.subscribe<entityx::EntityDestroyedEvent>(*this);
	eventManager.subscribe<entityx::ComponentRemovedEvent<BodyComponent>>(*this);
	eventManager.subscribe<CreateBody>(*this);
	eventManager.subscribe<CreateDistanceJoint>(*this);
	eventManager.subscribe<SetBodyPosition>(*this);
	eventManager.subscribe<SetBodyAngle>(*this);
	eventManager.subscribe<SetLinearVelocity>(*this);
	eventManager.subscribe<SetAngularVelocity>(*this);
	eventManager.subscribe<ApplyForce>(*this);
	eventManager.subscribe<ApplyLinearImpulse>(*this);
	eventManager.subscribe<ApplyAngularImpulse>(*this);
}

void PhysicsSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
	const float timeStep = 1.f / 60.f;
	const int velocityIterations = 6;
	const int positionIterations = 2;

	world.Step(timeStep, velocityIterations, positionIterations);
}

void PhysicsSystem::receive(const entityx::EntityDestroyedEvent& event)
{
	auto entity = event.entity;

	if (auto body = entity.component<BodyComponent>())
	{
		delete static_cast<entityx::Entity*>(body->getUserData());

		world.DestroyBody(body->getBody());
	}
}

void PhysicsSystem::receive(const entityx::ComponentRemovedEvent<BodyComponent>& event)
{
	delete static_cast<entityx::Entity*>(event.component->getUserData());

    world.DestroyBody(event.component->getBody());
}

void PhysicsSystem::receive(const CreateBody& event)
{
	event.entity.assign<BodyComponent>(event.bodyNode, world)->setUserData(new entityx::Entity(event.entity));
}

void PhysicsSystem::receive(const CreateDistanceJoint& event)
{
	auto bodyA = event.entityA.component<BodyComponent>();
	auto bodyB = event.entityB.component<BodyComponent>();
	auto anchorA = event.entityA.component<AnchorPointComponent>();
	auto anchorB = event.entityB.component<AnchorPointComponent>();

	if (bodyA && bodyB && anchorA && anchorB)
	{
		entityManager.create().assign<DistanceJointComponent>(world, bodyA->getBody(), bodyB->getBody(), anchorA->getAnchorPoint(), anchorB->getAnchorPoint());
	}
}

void PhysicsSystem::receive(const SetBodyPosition& event)
{
	if (auto body = event.entity.component<BodyComponent>())
	{
		body->setPosition(event.position);
	}
}

void PhysicsSystem::receive(const SetBodyAngle& event)
{
	if (auto body = event.entity.component<BodyComponent>())
	{
		body->setAngle(event.angle);
	}
}

void PhysicsSystem::receive(const SetLinearVelocity& event)
{
	if (auto body = event.entity.component<BodyComponent>())
	{
		body->setLinearVelocity(event.velocity);
	}
}

void PhysicsSystem::receive(const SetAngularVelocity& event)
{
	if (auto body = event.entity.component<BodyComponent>())
	{
		body->setAngularVelocity(event.velocity);
	}
}

void PhysicsSystem::receive(const ApplyForce& event)
{
	if (auto body = event.entity.component<BodyComponent>())
	{
		body->applyForce(event.force);
	}
}

void PhysicsSystem::receive(const ApplyLinearImpulse& event)
{
	if (auto body = event.entity.component<BodyComponent>())
	{
		body->applyLinearImpulse(event.impulse);
	}
}

void PhysicsSystem::receive(const ApplyAngularImpulse& event)
{
	if (auto body = event.entity.component<BodyComponent>())
	{
		body->applyAngularImpulse(event.impulse);
	}
}