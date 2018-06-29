/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PhysicsSystem.cpp
InversePalindrome.com
*/


#include "Constants.hpp"
#include "BodyParser.hpp"
#include "Conversions.hpp"
#include "JointParser.hpp"
#include "PhysicsSystem.hpp"
#include "TransformComponent.hpp"
#include "DistanceJointComponent.hpp"

#include <variant>


PhysicsSystem::PhysicsSystem(entityx::EventManager& eventManager) :
	world({ 0.f, 0.f }),
	collisionManager(eventManager)
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
	entityx::ComponentHandle<TransformComponent> transform;

	for (auto entity : entityManager.entities_with_components(body, transform))
	{
		transform->setPosition(body->getPosition());
		transform->setAngle(Conversions::radiansToDegrees(body->getAngle()));
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
	auto transform = event.entity.component<TransformComponent>();

	if (body && transform)
	{
		body->setPosition(transform->getPosition());
		body->setAngle(Conversions::degreesToRadians(transform->getAngle()));
	}
}

void PhysicsSystem::receive(const CreateBody& event)
{
	b2BodyDef bodyDef;
	BodyParser::parseBodyDef(bodyDef, event.bodyNode);

	auto body = event.entity.assign<BodyComponent>(world.CreateBody(&bodyDef));
	body->setUserData(event.entity);

	for (const auto fixtureNode : event.bodyNode.children())
	{
		b2FixtureDef fixtureDef;
		BodyParser::parseFixtureDef(fixtureDef, fixtureNode);
		
		std::variant<b2CircleShape, b2PolygonShape> shape;

		if (std::strcmp(fixtureNode.name(), "Circle") == 0)
		{
			b2CircleShape circleShape;
			BodyParser::parseCircleShape(circleShape, fixtureNode);
			shape = circleShape;
		}
		else if (std::strcmp(fixtureNode.name(), "Rectangle") == 0)
		{
			b2PolygonShape rectangleShape;
			BodyParser::parseRectangleShape(rectangleShape, fixtureNode);
			shape = rectangleShape;
		}
		else if (std::strcmp(fixtureNode.name(), "Polygon") == 0)
		{
			b2PolygonShape polygonShape;
			BodyParser::parsePolygonShape(polygonShape, fixtureNode);
			shape = polygonShape;
		}

		std::visit([&fixtureDef](auto& shape) { fixtureDef.shape = &shape; }, shape);

	    body->createFixture(fixtureDef);
	}

	body->computeAABB();
}

void PhysicsSystem::receive(const CreateDistanceJoint& event)
{
	auto bodyA = event.entityA.component<BodyComponent>();
	auto bodyB = event.entityB.component<BodyComponent>();
	
	if (bodyA && bodyB)
	{
		//event.jointEntity.assign<DistanceJointComponent>(world.CreateJoint())
	}
}