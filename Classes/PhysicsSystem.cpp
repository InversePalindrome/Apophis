/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PhysicsSystem.cpp
InversePalindrome.com
*/


#include "Conversions.hpp"
#include "PhysicsSystem.hpp"
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
	eventManager.subscribe<entityx::ComponentAddedEvent<BodyComponent>>(*this);
	eventManager.subscribe<entityx::ComponentRemovedEvent<BodyComponent>>(*this);
	eventManager.subscribe<CreateDistanceJoint>(*this);
}

void PhysicsSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
	updateCallbacks();

	entityx::ComponentHandle<BodyComponent> body;
	entityx::ComponentHandle<GeometryComponent> geometry;
	entityx::ComponentHandle<SpeedComponent> speed;
	entityx::ComponentHandle<ImpulseComponent> impulse;

	for (auto entity : entityManager.entities_with_components(body, geometry, speed, impulse))
	{
		updateSpatialProperties(body, geometry);
		applyImpulses(body, impulse);
		limitLinearSpeed(body, speed);
		limitAngularSpeed(body, speed);
	}
	
	updateWorld();
}

void PhysicsSystem::receive(const entityx::EntityDestroyedEvent& event)
{
	auto entity = event.entity;

	if (auto destroyedBody = entity.component<BodyComponent>())
	{
		auto* body = destroyedBody->getBody();

		bodyCallbacks.push_back([this, body]() { world.DestroyBody(body); });
	}
}

void PhysicsSystem::receive(const entityx::ComponentAddedEvent<BodyComponent>& event)
{
	auto entity = event.entity;
	auto body = event.component;
	
	bodyCallbacks.push_back([this, entity, body, event]() mutable
	{
		if (body)
		{
			body->createBody(world);
			body->setUserData(entity);

			if (const auto geometry = entity.component<GeometryComponent>())
			{
				body->setPosition({ geometry->getPosition().x, geometry->getPosition().y });
				body->setAngle(Conversions::degreesToRadians(geometry->getAngle()));
			}
		}
	});
}

void PhysicsSystem::receive(const entityx::ComponentRemovedEvent<BodyComponent>& event)
{
	auto* body = event.component->getBody();

	bodyCallbacks.push_back([this, body](){ world.DestroyBody(body); });
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

void PhysicsSystem::updateWorld()
{
	const float timeStep = 1.f / 60.f;
	const int velocityIterations = 6;
	const int positionIterations = 2;

	world.Step(timeStep, velocityIterations, positionIterations);
}

void PhysicsSystem::updateCallbacks()
{
	for (const auto& bodyCallback : bodyCallbacks)
	{
		bodyCallback();
	}

	bodyCallbacks.clear();
}

void PhysicsSystem::updateSpatialProperties(entityx::ComponentHandle<BodyComponent> body, entityx::ComponentHandle<GeometryComponent> geometry)
{
	geometry->setPosition({ body->getPosition().x, body->getPosition().y });
	geometry->setAngle(Conversions::radiansToDegrees(body->getAngle()));
}

void PhysicsSystem::applyImpulses(entityx::ComponentHandle<BodyComponent> body, entityx::ComponentHandle<ImpulseComponent> impulse)
{
	body->applyLinearImpulse(impulse->getLinearImpulse());
	body->applyAngularImpulse(impulse->getAngularImpulse());

	impulse->setLinearImpulse({ 0.f, 0.f });
	impulse->setAngularImpulse(0.f);
}

void PhysicsSystem::limitLinearSpeed(entityx::ComponentHandle<BodyComponent> body, entityx::ComponentHandle<SpeedComponent> speed)
{
	if (body->getLinearVelocity().Length() > speed->getMaxLinearSpeed())
	{
		body->setLinearVelocity(speed->getMaxLinearSpeed() / body->getLinearVelocity().Length() * body->getLinearVelocity());
	}
}

void PhysicsSystem::limitAngularSpeed(entityx::ComponentHandle<BodyComponent> body, entityx::ComponentHandle<SpeedComponent> speed)
{
	if (std::fabs(body->getAngularVelocity()) > speed->getMaxAngularSpeed())
	{
		body->setAngularVelocity(speed->getMaxAngularSpeed());
	}
}