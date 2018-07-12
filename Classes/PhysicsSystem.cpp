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

#include <variant>


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
	eventManager.subscribe<entityx::ComponentRemovedEvent<DistanceJointComponent>>(*this);
	eventManager.subscribe<EntityCreated>(*this);
	eventManager.subscribe<CreateBody>(*this);
	eventManager.subscribe<CreateDistanceJoint>(*this);
}

void PhysicsSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{
	updateWorldCallbacks();

	entityx::ComponentHandle<BodyComponent> body;
	entityx::ComponentHandle<TransformComponent> transform;
	
	for (auto entity : entityManager.entities_with_components(body, transform))
	{
		transform->setPosition(body->getPosition());
		transform->setAngle(Conversions::radiansToDegrees(body->getAngle()));
	}

	world.Step(Constants::TIMESTEP, Constants::VELOCITY_ITERATIONS, Constants::POSITION_ITERATIONS);
}

void PhysicsSystem::receive(const entityx::EntityDestroyedEvent& event)
{
	auto entity = event.entity;

	if (auto body = entity.component<BodyComponent>())
	{
		auto* bodyToDestroy = body->getBody();

		auto destroyBody = [this, bodyToDestroy]() {world.DestroyBody(bodyToDestroy); };

		if (world.IsLocked())
		{
			worldCallbacks.push_back(destroyBody);
		}
		else
		{
			destroyBody();
		}
	}
}

void PhysicsSystem::receive(const entityx::ComponentRemovedEvent<BodyComponent>& event)
{
	auto* bodyToDestroy = event.component->getBody();

	auto destroyBody = [this, bodyToDestroy]() {world.DestroyBody(bodyToDestroy); };

	if (world.IsLocked())
	{
		worldCallbacks.push_back(destroyBody);
	}
	else
	{
		destroyBody();
	}
}

void PhysicsSystem::receive(const entityx::ComponentRemovedEvent<DistanceJointComponent>& event)
{
	auto* jointToDestroy = event.component->getDistanceJoint();

	auto destroyJoint = [this, jointToDestroy] {world.DestroyJoint(jointToDestroy); };
	
	if (world.IsLocked())
	{
		worldCallbacks.push_back(destroyJoint);
	}
	else
	{
		destroyJoint();
	}
}

void PhysicsSystem::receive(const EntityCreated& event)
{
	auto setupTransform = [event]()
	{
		if (auto[body, transform] = event.entity.components<BodyComponent, TransformComponent>(); body && transform)
		{
			body->setPosition(transform->getPosition());
			body->setAngle(Conversions::degreesToRadians(transform->getAngle()));
		}
	};

	if (world.IsLocked())
	{
		worldCallbacks.push_back(setupTransform);
	}
	else
	{
		setupTransform();
	}
}

void PhysicsSystem::receive(const CreateBody& event)
{
	b2BodyDef bodyDef;
	BodyParser::parseBodyDef(bodyDef, event.bodyNode);

	std::vector<std::pair<b2FixtureDef, std::variant<b2CircleShape, b2PolygonShape>>> fixtures;

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

		fixtures.push_back({ fixtureDef, shape });
	}

    auto createBody = [this, event, bodyDef, fixtures]()
	{
		auto body = event.entity.assign<BodyComponent>(world.CreateBody(&bodyDef));
		body->setUserData(event.entity);

		for (auto fixture : fixtures)
		{
			std::visit([&fixture](auto& shape) { fixture.first.shape = &shape; }, fixture.second);

			body->createFixture(fixture.first);
		}

		body->computeAABB();
	};

	if (world.IsLocked())
	{
		worldCallbacks.push_back(createBody);
	}
	else
	{
		createBody();
	}
}

void PhysicsSystem::receive(const CreateDistanceJoint& event)
{
	b2DistanceJointDef distanceJointDef;
	
	std::size_t idA = 0u, idB = 0u;
	
	if (const auto idAAttribute = event.jointNode.attribute("IDA"))
	{
		idA = idAAttribute.as_uint();
	}
	if (const auto idBAttribute = event.jointNode.attribute("IDB"))
	{
		idB = idBAttribute.as_uint();
	}

	if (auto entityA = entityManager.get(entityManager.create_id(idA)),
        entityB = entityManager.get(entityManager.create_id(idB)); 
	    entityA && entityB)
	{
		if (auto bodyA = entityA.component<BodyComponent>(),
		    bodyB = entityB.component<BodyComponent>(); 
		    bodyA && bodyB)
		{
			JointParser::parseDistanceJointDef(distanceJointDef, bodyA->getBody(), bodyB->getBody(), event.jointNode);

			auto createJoint = [this, event, distanceJointDef]()
			{
			    event.entity.assign<DistanceJointComponent>(static_cast<b2DistanceJoint*>(world.CreateJoint(&distanceJointDef)));
			};

			if (world.IsLocked())
			{
				worldCallbacks.push_back(createJoint);
			}
			else
			{
				createJoint();
			}
		}
	}
}

void PhysicsSystem::updateWorldCallbacks()
{
	for (const auto& worldCallback : worldCallbacks)
	{
		worldCallback();
	}

	worldCallbacks.clear();
}