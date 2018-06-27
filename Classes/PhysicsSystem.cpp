/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PhysicsSystem.cpp
InversePalindrome.com
*/


#include "Constants.hpp"
#include "BodyParser.hpp"
#include "Conversions.hpp"
#include "PhysicsSystem.hpp"
#include "GeometryComponent.hpp"
#include "AnchorPointComponent.hpp"
#include "DistanceJointComponent.hpp"


PhysicsSystem::PhysicsSystem(entityx::EntityManager& entityManager, entityx::EventManager& eventManager) :
	world({ 0.f, 0.f }),
	collisionManager(eventManager),
	entityManager(entityManager)
{
	world.SetContactListener(&collisionManager);
	world.SetContactFilter(&collisionFilter);
}

void PhysicsSystem::configure(entityx::EventManager& eventManager)
{
	eventManager.subscribe<entityx::EntityDestroyedEvent>(*this);
	eventManager.subscribe<entityx::ComponentRemovedEvent<BodyComponent>>(*this);
	eventManager.subscribe<EntityCreated>(*this);
	eventManager.subscribe<CreateBody>(*this);
	eventManager.subscribe<CreateDistanceJoint>(*this);
}

void PhysicsSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
	entityx::ComponentHandle<BodyComponent> body;
	entityx::ComponentHandle<GeometryComponent> geometry;

	for (auto entity : entityManager.entities_with_components(body, geometry))
	{
		geometry->setPosition(body->getPosition());
		geometry->setAngle(Conversions::radiansToDegrees(body->getAngle()));
	}
	
	collisionManager.update();
	world.Step(Constants::TIMESTEP, Constants::VELOCITY_ITERATIONS, Constants::POSITION_ITERATIONS);
}

void PhysicsSystem::receive(const entityx::EntityDestroyedEvent& event)
{
	auto entity = event.entity;

	if (auto body = entity.component<BodyComponent>())
	{
	    world.DestroyBody(body->getBody());
	}
}

void PhysicsSystem::receive(const entityx::ComponentRemovedEvent<BodyComponent>& event)
{
	world.DestroyBody(event.component->getBody());
}

void PhysicsSystem::receive(const EntityCreated& event)
{
	auto body = event.entity.component<BodyComponent>();
	auto geometry = event.entity.component<GeometryComponent>();

	if (body && geometry)
	{
		body->setPosition(geometry->getPosition());
		body->setAngle(Conversions::degreesToRadians(geometry->getAngle()));
	}
}

void PhysicsSystem::receive(const CreateBody& event)
{
	auto body = event.entity.assign<BodyComponent>(world.CreateBody(&BodyParser::createBodyDef(event.bodyNode)));
	body->setUserData(event.entity);

	for (const auto fixtureNode : event.bodyNode.children())
	{
		auto fixtureDef = BodyParser::createFixtureDef(fixtureNode);
		auto shape = BodyParser::createShape(fixtureNode);

		std::visit([&fixtureDef](auto& shape) { fixtureDef.shape = &shape; }, shape);

	    body->createFixture(fixtureDef);
	}

	body->computeAABB();
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