/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PhysicsSystem.cpp
InversePalindrome.com
*/


#include "Joints.hpp"
#include "Constants.hpp"
#include "Conversions.hpp"
#include "PhysicsSystem.hpp"
#include "TransformComponent.hpp"

#include <brigand/algorithms/for_each.hpp>

#include <variant>


PhysicsSystem::PhysicsSystem(entityx::EntityManager& entityManager, entityx::EventManager& eventManager) :
	world({ 0.f, 0.f }),
	collisionManager(eventManager),
	destructionListener(entityManager),
	entityManager(entityManager)
{
	world.SetContactListener(&collisionManager);
	world.SetContactFilter(&collisionFilter);
	world.SetDestructionListener(&destructionListener);
}

void PhysicsSystem::configure(entityx::EventManager& eventManager)
{
	eventManager.subscribe<entityx::EntityDestroyedEvent>(*this);
	eventManager.subscribe<entityx::ComponentAddedEvent<BodyComponent>>(*this);
	eventManager.subscribe<entityx::ComponentRemovedEvent<BodyComponent>>(*this);
	eventManager.subscribe<EntityParsed>(*this);
	eventManager.subscribe<DestroyJoint<DistanceJointComponent>>(*this);
}

void PhysicsSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
	updateWorldCallbacks();

	entityManager.each<TransformComponent, BodyComponent>([](auto entity, auto& transform, const auto& body)
	{
		transform.setPosition(body.getPosition());
		transform.setAngle(Conversions::radiansToDegrees(body.getAngle()));
	});

	world.Step(Constants::TIMESTEP, Constants::VELOCITY_ITERATIONS, Constants::POSITION_ITERATIONS);
}

void PhysicsSystem::receive(const entityx::EntityDestroyedEvent& event)
{
	auto entity = event.entity;
	
	brigand::for_each<Joints>([this, entity](auto jointElement) mutable
	{
		if (auto joint = entity.component<decltype(jointElement)::type>())
		{
			destroyJoint(joint->getJoint());
		}
	});

	if (auto body = entity.component<BodyComponent>())
	{
		destroyBody(body->getBody());
	}
}

void PhysicsSystem::receive(const entityx::ComponentAddedEvent<BodyComponent>& event)
{
	auto body = event.component;

	modifyWorld([this, body, &event]() mutable
	{ 
		body->setBody(world.CreateBody(&b2BodyDef())); 
		body->setUserData(event.entity);
	});
}

void PhysicsSystem::receive(const entityx::ComponentRemovedEvent<BodyComponent>& event)
{
	destroyBody(event.component->getBody());
}

void PhysicsSystem::receive(const EntityParsed& event)
{
	modifyWorld([event]()
	{
		if (auto[body, transform] = event.entity.components<BodyComponent, TransformComponent>(); body && transform)
		{
			body->setPosition(transform->getPosition());
			body->setAngle(Conversions::degreesToRadians(transform->getAngle()));
		}
	});
}

void PhysicsSystem::receive(const DestroyJoint<DistanceJointComponent>& event)
{
	auto joint = event.joint;

	destroyJoint(joint->getJoint());

	joint.remove();
}

void PhysicsSystem::updateWorldCallbacks()
{
	for (const auto& worldCallback : worldCallbacks)
	{
		worldCallback();
	}

	worldCallbacks.clear();
}

void PhysicsSystem::destroyBody(b2Body* body)
{
    modifyWorld([this, body]() { world.DestroyBody(body); });
}

void PhysicsSystem::destroyJoint(b2Joint* joint)
{
	modifyWorld([this, joint] { world.DestroyJoint(joint); });
}

void PhysicsSystem::modifyWorld(const std::function<void()>& function)
{
	if (world.IsLocked())
	{
		worldCallbacks.push_back(function);
	}
	else
	{
		function();
	}
}