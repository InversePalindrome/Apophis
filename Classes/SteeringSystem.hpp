/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SteeringSystem.hpp
InversePalindrome.com
*/


#pragma once

#include "Events.hpp"

#include <entityx/System.h>


class SteeringSystem : public entityx::System<SteeringSystem>, public entityx::Receiver<SteeringSystem>
{
public:
	virtual void configure(entityx::EventManager& eventManager) override;
	virtual void update(entityx::EntityManager& entityManager, entityx::EventManager& eventManager, entityx::TimeDelta deltaTime) override;
	virtual void receive(const Seek& event);
	virtual void receive(const Flee& event);
	virtual void receive(const Pursue& event);
	virtual void receive(const Evade& event);
	virtual void receive(const Arrive& event);
	virtual void receive(const Follow& event);
	virtual void receive(const Wander& event);
	virtual void receive(const Avoid& event);
	virtual void receive(const Orbit& event);
	virtual void receive(const Align& event);
	virtual void receive(const Cohesion& event);
	virtual void receive(const Separate& event);
	virtual void receive(const Queue& event);
	virtual void receive(const Face& event);

private:
	entityx::EventManager* eventManager;

	b2Vec2 seekForce(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, const b2Vec2& bodyVelocity, float force);
	b2Vec2 pursueForce(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, const b2Vec2& bodyVelocity, const b2Vec2& targetVelocity, float predictionTime, float force);
	b2Vec2 arriveForce(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, const b2Vec2& bodyVelocity, float slowRadius, float force);
	b2Vec2 followForce(const b2Vec2& bodyPosition, const b2Vec2& leaderPosition, const b2Vec2& bodyVelocity, const b2Vec2& leaderVelocity, float leaderSight, float distanceFromLeader, float predictionTime, float force);
	b2Vec2 wanderForce(const b2Vec2& bodyPosition, const b2Vec2& bodyVelocity, float wanderDistance, float wanderRadius, float wanderRate, float& wanderAngle, float force);
	b2Vec2 avoidForce(const b2Vec2& bodyPosition, const b2Vec2& bodyVelocity, float avoidanceDistance, float avoidanceForce);
	b2Vec2 orbitForce(const b2Vec2& satellitePosition, const b2Vec2& primaryPosition, float force);

	b2Vec2 alignForce(float groupRadius, float force);
	b2Vec2 cohesionForce(float groupRadius, float force);
	b2Vec2 separateForce(float groupRadius, float force);
	b2Vec2 queueForce(float groupRadius, float queueDistance, float shrinkFactor, float steeringBrakeFactor, float force);

	float faceForce(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, float bodyAngle, float bodyAngularVelocity, float bodyInertia);

	b2Vec2 desiredVelocity(const b2Vec2& bodyPosition, const b2Vec2& targetPosition, float force);
};