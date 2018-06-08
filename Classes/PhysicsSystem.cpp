/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PhysicsSystem.cpp
InversePalindrome.com
*/


#include "BodyParser.hpp"
#include "PhysicsSystem.hpp"
#include "AnchorPointComponent.hpp"
#include "DistanceJointComponent.hpp"


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
}

void PhysicsSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
	entityx::ComponentHandle<BodyComponent> body;
	entityx::ComponentHandle<SpeedComponent> speed;

	for (auto entity : entityManager.entities_with_components(body, speed))
	{        
		limitLinearSpeed(body, speed);
		limitAngularSpeed(body, speed);
	}

	createBodies();
	removeBodies();
	updateWorld();
}

void PhysicsSystem::receive(const entityx::EntityDestroyedEvent& event)
{
	auto entity = event.entity;

	if (auto body = entity.component<BodyComponent>())
	{
		deletionBodies.push_back(body->getBody());
	}
}

void PhysicsSystem::receive(const entityx::ComponentRemovedEvent<BodyComponent>& event)
{
	deletionBodies.push_back(event.component->getBody());
}

void PhysicsSystem::receive(const CreateBody& event)
{
	auto bodyDef = BodyParser::createBodyDef(event.bodyNode);
	bodyDef.userData = new entityx::Entity(event.entity);

	std::vector<std::pair<b2FixtureDef, std::variant<b2CircleShape, b2PolygonShape>>> fixtureDefs;

	for (const auto* fixtureNode = event.bodyNode->FirstChildElement(); fixtureNode; fixtureNode = fixtureNode->NextSiblingElement())
	{
		std::variant<b2CircleShape, b2PolygonShape> shape;

		if (std::strcmp(fixtureNode->Value(), "Circle") == 0)
		{
			shape = BodyParser::createCircle(fixtureNode);
		}
		else if (std::strcmp(fixtureNode->Value(), "Polygon") == 0)
		{
			shape = BodyParser::createPolygon(fixtureNode);
		}
		
		fixtureDefs.push_back({BodyParser::createFixtureDef(fixtureNode), shape });
	}

	bodiesDefinitions.push_back({ bodyDef, fixtureDefs });
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

void PhysicsSystem::createBodies()
{
	for (auto& bodyDefinition : bodiesDefinitions)
	{
		auto* body = world.CreateBody(&bodyDefinition.bodyDef);

		for (auto& [fixtureDef, shape] : bodyDefinition.fixtureDefs)
		{
			std::visit([&body, &fixtureDef](auto& shapeValue) 
			{
				fixtureDef.shape = &shapeValue;
				body->CreateFixture(&fixtureDef);
			}, shape);
		}

		static_cast<entityx::Entity*>(bodyDefinition.bodyDef.userData)->assign<BodyComponent>(body);
	}

	bodiesDefinitions.clear();
}

void PhysicsSystem::removeBodies()
{
	for (const auto& body : deletionBodies)
	{
		delete static_cast<entityx::Entity*>(body->GetUserData());

		world.DestroyBody(body);
	}

	deletionBodies.clear();
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