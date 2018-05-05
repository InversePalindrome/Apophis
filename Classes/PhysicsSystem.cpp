/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - PhysicsSystem.cpp
InversePalindrome.com
*/


#include "PhysicsSystem.hpp"


PhysicsSystem::PhysicsSystem(cocos2d::Node* mainNode, entityx::EventManager& eventManager) :
	world({ 0.f, 0.f }),
	collisionManager(mainNode, eventManager)
{
	world.SetContactListener(&collisionManager);
}

void PhysicsSystem::configure(entityx::EventManager& eventManager)
{
	eventManager.subscribe<entityx::EntityDestroyedEvent>(*this);
	eventManager.subscribe<CreateBody>(*this);
	eventManager.subscribe<SetPosition>(*this);
	eventManager.subscribe<SetRotation>(*this);
	eventManager.subscribe<SetVelocity>(*this);
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
		world.DestroyBody(body->getBody());
	}
}

void PhysicsSystem::receive(const CreateBody& event)
{
	event.entity.assign<BodyComponent>(event.bodyData, world, event.entity);
}

void PhysicsSystem::receive(const SetPosition& event)
{
	if (auto body = event.entity.component<BodyComponent>())
	{
		body->setPosition(event.position);
	}
}

void PhysicsSystem::receive(const SetRotation& event)
{
	if (auto body = event.entity.component<BodyComponent>())
	{
		body->setAngle(event.angle);
	}
}

void PhysicsSystem::receive(const SetVelocity& event)
{
	if (auto body = event.entity.component<BodyComponent>())
	{
		body->setLinearVelocity(event.velocity);
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