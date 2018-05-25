/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SteeringSystem.cpp
InversePalindrome.com
*/


#include "Constants.hpp"
#include "AreaQuery.hpp"
#include "RayCastQuery.hpp"
#include "BodyComponent.hpp"
#include "FlockComponent.hpp"
#include "SteeringSystem.hpp"
#include "AvoidComponent.hpp"
#include "QueueComponent.hpp"
#include "ForceComponent.hpp"
#include "PursueComponent.hpp"
#include "ArriveComponent.hpp"
#include "WanderComponent.hpp"
#include "PatrolComponent.hpp"
#include "FollowComponent.hpp"
#include "ObjectComponent.hpp"

#include <cocos/base/ccRandom.h>

#include <boost/math/constants/constants.hpp>


void SteeringSystem::configure(entityx::EventManager& eventManager)
{
	this->eventManager = &eventManager;

	eventManager.subscribe<Seek>(*this);
	eventManager.subscribe<Pursue>(*this);
	eventManager.subscribe<Arrive>(*this);
	eventManager.subscribe<Follow>(*this);
	eventManager.subscribe<Wander>(*this);
	eventManager.subscribe<Avoid>(*this);
	eventManager.subscribe<Orbit>(*this);
	eventManager.subscribe<Align>(*this);
	eventManager.subscribe<Cohesion>(*this);
	eventManager.subscribe<Separate>(*this);
	eventManager.subscribe<Queue>(*this);
	eventManager.subscribe<Face>(*this);
}

void SteeringSystem::update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime)
{ 
	
}

void SteeringSystem::receive(const Seek& event)
{
	auto body = event.entity.component<BodyComponent>();
	auto force = event.entity.component<ForceComponent>();

	if (body && force)
	{
		body->applyLinearForce(seekForce(body->getPosition(), event.targetPosition, body->getLinearVelocity(), force->getLinearForce()));
	}
}

void SteeringSystem::receive(const Pursue& event)
{
	auto body = event.entity.component<BodyComponent>();
	auto force = event.entity.component<ForceComponent>();
	auto pursue = event.entity.component<PursueComponent>();

	if (body && force && pursue)
	{
		body->applyLinearForce(pursueForce(body->getPosition(), event.targetPosition, body->getLinearVelocity(), event.targetVelocity, pursue->getPredictionTime(), force->getLinearForce()));
	}
}

void SteeringSystem::receive(const Arrive& event)
{
	auto body = event.entity.component<BodyComponent>();
	auto force = event.entity.component<ForceComponent>();
	auto arrive = event.entity.component<ArriveComponent>();

	if (body && force && arrive)
	{
		body->applyLinearForce(arriveForce(body->getPosition(), event.targetPosition, body->getLinearVelocity(), arrive->getSlowRadius(), force->getLinearForce()));
	}
}

void SteeringSystem::receive(const Follow& event)
{
	auto body = event.entity.component<BodyComponent>();
	auto force = event.entity.component<ForceComponent>();
	auto follow = event.entity.component<FollowComponent>();
	auto pursue = event.entity.component<PursueComponent>();

	if (body && force && follow && pursue)
	{
		body->applyLinearForce(followForce(body->getPosition(), event.targetPosition, body->getLinearVelocity(), event.targetVelocity, event.targetVision, follow->getDistanceFromLeader(), pursue->getPredictionTime(), force->getLinearForce()));
	}
}

void SteeringSystem::receive(const Wander& event)
{
	auto body = event.entity.component<BodyComponent>();
	auto force = event.entity.component<ForceComponent>();
	auto wander = event.entity.component<WanderComponent>();

	if (body && force && wander)
	{
		body->applyLinearForce(wanderForce(body->getPosition(), body->getLinearVelocity(), wander->getWanderDistance(), wander->getWanderRadius(), wander->getWanderRate(), wander->getWanderAngle(), force->getLinearForce()));
	}
}

void SteeringSystem::receive(const Avoid& event)
{
	auto body = event.entity.component<BodyComponent>();
	auto avoid = event.entity.component<AvoidComponent>();

	if (body && avoid)
	{
		body->applyLinearForce(avoidForce(body->getPosition(), body->getLinearVelocity(), avoid->getAvoidanceDistance(), avoid->getAvoidanceForce()));
	}
}

void SteeringSystem::receive(const Orbit& event)
{
	auto body = event.entity.component<BodyComponent>();
	auto force = event.entity.component<ForceComponent>();

	if (body && force)
	{
		body->applyLinearForce(orbitForce(body->getPosition(), event.primaryPosition, force->getLinearForce()));
	}
}

void SteeringSystem::receive(const Align& event)
{
	
}

void SteeringSystem::receive(const Cohesion& event)
{
	
}

void SteeringSystem::receive(const Separate& event)
{

}

void SteeringSystem::receive(const Queue& event)
{
	
}

void SteeringSystem::receive(const Face& event)
{
	if (auto body = event.entity.component<BodyComponent>())
	{
		body->applyAngularImpulse(faceForce(body->getPosition(), event.targetPosition, body->getAngle(), body->getAngularVelocity(), body->getInertia()));
	}
}

b2Vec2 SteeringSystem::seekForce(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, const b2Vec2& bodyVelocity, float force)
{
	return desiredVelocity(bodyPosition, targetPosition, force) - bodyVelocity;
}

b2Vec2 SteeringSystem::pursueForce(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, const b2Vec2& bodyVelocity, const b2Vec2& targetVelocity, float predictionTime, float force)
{
	auto distance = (targetPosition - bodyPosition).Length();

	if (bodyVelocity.Length() > distance / predictionTime)
	{
		predictionTime = distance / bodyVelocity.Length();
	}

	const auto& futurePosition = targetPosition + predictionTime * targetVelocity;

	return seekForce(bodyPosition, futurePosition, bodyVelocity, force);
}

b2Vec2 SteeringSystem::arriveForce(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, const b2Vec2& bodyVelocity, float force, float slowRadius)
{
	auto radius = (targetPosition - bodyPosition).Length();

	if (radius < slowRadius)
	{
		return seekForce(bodyPosition, targetPosition, bodyVelocity, force * radius / slowRadius);
	}

	return seekForce(bodyPosition, targetPosition, bodyVelocity, force);
}

b2Vec2 SteeringSystem::followForce(const b2Vec2& bodyPosition, const b2Vec2& leaderPosition, const b2Vec2& bodyVelocity, const b2Vec2& leaderVelocity, float leaderSight, float distanceFromLeader, float predictionTime, float force)
{
	b2Vec2 steeringForce(0.f, 0.f);

	auto leaderDirection = leaderVelocity;
	leaderDirection.Normalize();
	leaderDirection *= distanceFromLeader;

	auto leaderAhead = leaderPosition + leaderDirection;

	if ((bodyPosition - leaderAhead).Length() <= leaderSight || (bodyPosition - leaderPosition).Length() <= leaderSight)
	{
		steeringForce += pursueForce(bodyPosition, leaderPosition, bodyVelocity, leaderVelocity, predictionTime, -force);
	}

	steeringForce += arriveForce(bodyPosition, leaderPosition - leaderDirection, bodyVelocity, distanceFromLeader, force);

	return steeringForce;
}

b2Vec2 SteeringSystem::wanderForce(const b2Vec2& bodyPosition, const b2Vec2& bodyVelocity, float wanderDistance, float wanderRadius, float wanderRate, float& wanderAngle, float force)
{
	auto wanderCenter = bodyVelocity;
	wanderCenter.Normalize();
	wanderCenter *= wanderDistance;
	wanderCenter += { wanderRadius * std::cos(wanderAngle), wanderRadius * std::sin(wanderAngle) };

	wanderAngle += cocos2d::random() * wanderRate;

	return seekForce(bodyPosition, bodyPosition + wanderCenter, bodyVelocity, force);
}

b2Vec2 SteeringSystem::avoidForce(const b2Vec2& bodyPosition, const b2Vec2& bodyVelocity, float avoidanceDistance, float avoidanceForce)
{
	b2Vec2 steeringForce(0.f, 0.f);

	auto ahead = bodyVelocity;
	ahead.Normalize();
	ahead *= avoidanceDistance;
	ahead += bodyPosition;

	if ((bodyPosition - ahead).LengthSquared() > 0.0f)
	{
		RayCastQuery rayQuery;

		eventManager->emit(RayCast{ rayQuery, bodyPosition, ahead });

		for (const auto& rayData : rayQuery.queryData)
		{
			if (auto object = static_cast<entityx::Entity*>(rayData.body->GetUserData())->component<ObjectComponent>())
			{
				if (object->getObjectType() & ObjectType::Obstacle)
				{
					steeringForce += desiredVelocity(rayData.body->GetPosition(), ahead, avoidanceForce);
					break;
				}
			}
		}
	}

	return steeringForce;
}

b2Vec2 SteeringSystem::orbitForce(const b2Vec2& satellitePosition, const b2Vec2& primaryPosition, float force)
{
	auto radius = primaryPosition - satellitePosition;

	auto steeringForce = radius.Skew();
	steeringForce.Normalize();
	steeringForce *= force;

	return steeringForce;
}

b2Vec2 SteeringSystem::alignForce(float groupRadius, float force)
{
	b2Vec2 steeringForce(0.f, 0.f);

	return steeringForce;
}

b2Vec2 SteeringSystem::cohesionForce(float groupRadius, float force)
{
	b2Vec2 steeringForce(0.f, 0.f);

	return steeringForce;
}

b2Vec2 SteeringSystem::separateForce(float groupRadius, float force)
{
	b2Vec2 steeringForce(0.f, 0.f);

	return steeringForce;
}

b2Vec2 SteeringSystem::queueForce(float groupRadius, float queueDistance, float shrinkFactor, float steeringBrakeFactor, float force)
{
	b2Vec2 steeringForce(0.f, 0.f);

	return steeringForce;
}

float SteeringSystem::faceForce(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, float bodyAngle, float bodyAngularVelocity, float bodyInertia)
{
	auto desiredAngle = std::atan2f(targetPosition.x - bodyPosition.x, targetPosition.y - bodyPosition.y);
	auto nextAngle = bodyAngle + bodyAngularVelocity / Constants::FPS;

	auto totalRotation = std::remainderf(desiredAngle - nextAngle, 2 * boost::math::constants::pi<float>());
	
	auto desiredAngularVelocity = totalRotation * Constants::FPS;

	return bodyInertia * desiredAngularVelocity;
}

b2Vec2 SteeringSystem::desiredVelocity(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, float force)
{
	auto desiredVelocity = targetPosition - bodyPosition;
	desiredVelocity.Normalize();
	desiredVelocity *= force;

	return desiredVelocity;
}