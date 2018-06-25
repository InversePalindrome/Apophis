/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PhysicsSystem.cpp
InversePalindrome.com
*/


#include "BodyParser.hpp"
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
	eventManager.subscribe<entityx::ComponentRemovedEvent<BodyComponent>>(*this);
	eventManager.subscribe<CreateBody>(*this);
	eventManager.subscribe<CreateDistanceJoint>(*this);
}

void PhysicsSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
	updateBodyCallbacks();

	entityx::ComponentHandle<BodyComponent> body;

	for (auto entity : entityManager.entities_with_components(body))
	{
		if (auto geometry = entity.component<GeometryComponent>())
		{
			updateGeometry(body, geometry);
		}
		if (auto impulse = entity.component<ImpulseComponent>())
		{
			applyImpulses(body, impulse);
		}
		if (auto speed = entity.component<SpeedComponent>())
		{
			limitLinearSpeed(body, speed);
			limitAngularSpeed(body, speed);
		}
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

void PhysicsSystem::receive(const entityx::ComponentRemovedEvent<BodyComponent>& event)
{
	auto* body = event.component->getBody();

	bodyCallbacks.push_back([this, body](){ world.DestroyBody(body); });
}

void PhysicsSystem::receive(const CreateBody& event)
{
	auto bodyDef = BodyParser::createBodyDef(event.bodyNode);

	std::vector<std::pair<b2FixtureDef, std::variant<b2CircleShape, b2PolygonShape>>> fixtures;

	for (const auto fixtureNode : event.bodyNode.children())
	{
		fixtures.push_back({ BodyParser::createFixtureDef(fixtureNode), BodyParser::createShape(fixtureNode) });
	}

	bodyCallbacks.push_back([this, event, bodyDef, fixtures]() 
	{
		if (event.entity)
		{
			auto body = event.entity.assign<BodyComponent>(world.CreateBody(&bodyDef));
			body->setUserData(event.entity);

			for (auto fixture : fixtures)
			{
				std::visit([&fixture](auto& shape) { fixture.first.shape = &shape; }, fixture.second);

				body->createFixture(fixture.first);
			}

			if (auto geometry = event.entity.component<GeometryComponent>())
			{
				body->setPosition(geometry->getPosition());
				body->setAngle(Conversions::degreesToRadians(geometry->getAngle()));
			}
		}
	});
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

void PhysicsSystem::updateBodyCallbacks()
{
	for (const auto& bodyCallback : bodyCallbacks)
	{
		bodyCallback();
	}

	bodyCallbacks.clear();
}

void PhysicsSystem::updateGeometry(entityx::ComponentHandle<BodyComponent> body, entityx::ComponentHandle<GeometryComponent> geometry)
{
	geometry->setPosition(body->getPosition());
	geometry->setSize(body->getAABB().upperBound - body->getAABB().lowerBound);
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