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
	createBodies();
	removeBodies();

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

	if (auto body = entity.component<BodyComponent>())
	{
		bodiesToRemove.push_back(body->getBody());
	}
}

void PhysicsSystem::receive(const entityx::ComponentAddedEvent<BodyComponent>& event)
{
	bodiesToCreate.emplace_back(event.entity, event.component);
}

void PhysicsSystem::receive(const entityx::ComponentRemovedEvent<BodyComponent>& event)
{
	bodiesToRemove.push_back(event.component->getBody());
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
	for (auto& [entity, body] : bodiesToCreate)
	{
		body->createBody(world);

		if (const auto geometry = entity.component<GeometryComponent>())
		{
			std::vector<std::variant<b2CircleShape, b2PolygonShape>> shapes;

			for (const auto& shape : geometry->getShapes())
			{
				std::visit([&shapes](const auto& shape) 
				{
					using T = std::decay_t<decltype(shape)>;

					if constexpr(std::is_same_v<T, wykobi::circle<float>>)
					{
						b2CircleShape circle;

						circle.m_p = { shape.x, shape.y };
						circle.m_radius = shape.radius;

						shapes.push_back(circle);
					}
					else if constexpr (std::is_same_v<T, wykobi::rectangle<float>>)
					{
						b2PolygonShape rectangle;

						rectangle.SetAsBox(shape[1].x, shape[1].y);

						shapes.push_back(rectangle);
					}
					else if constexpr (std::is_same_v<T, wykobi::polygon<float, 2>>)
					{
						b2PolygonShape polygon;
						
						std::vector<b2Vec2> points;

						for (const auto& point : shape)
						{
							points.push_back({ point.x, point.y });
						}

						polygon.Set(points.data(), points.size());

						shapes.push_back(polygon);
					}
				}, shape);
			}

			body->createFixtures(shapes);
			body->setPosition({ geometry->getPosition().x, geometry->getPosition().y });
			body->setAngle(Conversions::degreesToRadians(geometry->getAngle()));
		}

		body->setUserData(new entityx::Entity(entity));
	}

	bodiesToCreate.clear();
}

void PhysicsSystem::removeBodies()
{
	for (const auto& body : bodiesToRemove)
	{
		delete static_cast<entityx::Entity*>(body->GetUserData());

		world.DestroyBody(body);
	}

	bodiesToRemove.clear();
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