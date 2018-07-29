/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PhysicsSystem.cpp
InversePalindrome.com
*/


#include "Joints.hpp"
#include "Constants.hpp"
#include "BodyParser.hpp"
#include "Conversions.hpp"
#include "JointParser.hpp"
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
	eventManager.subscribe<entityx::ComponentRemovedEvent<BodyComponent>>(*this);
	eventManager.subscribe<EntityParsed>(*this);
	eventManager.subscribe<CreateBody>(*this);
	eventManager.subscribe<CreateJoint<DistanceJointComponent>>(*this);
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

    modifyWorld([this, event, bodyDef, fixtures]()
	{
		auto body = event.entity.assign<BodyComponent>(world.CreateBody(&bodyDef));
		body->setUserData(event.entity);

		for (auto fixture : fixtures)
		{
			std::visit([&fixture](auto& shape) { fixture.first.shape = &shape; }, fixture.second);

			body->createFixture(fixture.first);
		}

		body->computeAABB();
	});
}

void PhysicsSystem::receive(const CreateJoint<DistanceJointComponent>& event)
{
	std::size_t entityIDA = 0u, entityIDB = 0u;
	
	if (const auto entityIDAAttribute = event.jointNode.attribute("idA"))
	{
		entityIDA = entityIDAAttribute.as_uint();
	}
	if (const auto entityIDBAttribute = event.jointNode.attribute("idB"))
	{
		entityIDB = entityIDBAttribute.as_uint();
	}

	if (auto entityA = entityManager.get(entityManager.create_id(entityIDA)),
		entityB = entityManager.get(entityManager.create_id(entityIDB));
     	entityA && entityB)
	{
		if (auto bodyA = entityA.component<BodyComponent>(),
			bodyB = entityB.component<BodyComponent>();
		    bodyA && bodyB)
		{
			b2DistanceJointDef distanceJointDef;

			JointParser::parseDistanceJointDef(distanceJointDef, bodyA->getBody(), bodyB->getBody(), event.jointNode);

			modifyWorld([this, event, distanceJointDef, entityIDA, entityIDB]() mutable
			{
				event.entity.assign<DistanceJointComponent>(world.CreateJoint(&distanceJointDef), entityIDA, entityIDB);
			});
		}
	}
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