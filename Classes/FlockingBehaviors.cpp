/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - FlockingBehaviors.cpp
InversePalindrome.com
*/


#include "BodyData.hpp"
#include "BodyComponent.hpp"
#include "FlockingBehaviors.hpp"


void FlockingBehaviors::align(b2Body* agentBody, const std::vector<b2Body*>& neighborBodies, float maxSpeed)
{
	b2Vec2 alignForce(0.f, 0.f);
	std::size_t groupCount = 0u;
	
	const auto* agentData = static_cast<BodyData*>(agentBody->GetUserData());

	if (!agentData)
	{
		return;
	}

	for (const auto* neighborBody : neighborBodies)
	{
		if (agentBody != neighborBody)
		{
			if (const auto* neighborBodyData = static_cast<BodyData*>(neighborBody->GetUserData()))
			{
				if (neighborBodyData->objectType & agentData->objectType)
				{
					alignForce += neighborBody->GetLinearVelocity();
					++groupCount;
				}
			}
		}
	}
	
	if (groupCount > 0u)
	{
		alignForce *= 1 / groupCount;
		alignForce.Normalize();
		alignForce *= maxSpeed;
		
		agentBody->ApplyLinearImpulse(alignForce, agentBody->GetWorldCenter(), true);
	}
}

void FlockingBehaviors::cohesion(b2Body* agentBody, const std::vector<b2Body*>& neighborBodies, float maxSpeed)
{
	b2Vec2 cohesionForce(0.f, 0.f);
	std::size_t groupCount = 0u;

	const auto* agentData = static_cast<BodyData*>(agentBody->GetUserData());

	if (!agentData)
	{
		return;
	}

	for (const auto* neighborBody : neighborBodies)
	{
		if (agentBody != neighborBody)
		{
			if (const auto* neighborBodyData = static_cast<BodyData*>(neighborBody->GetUserData()))
			{
				if (neighborBodyData->objectType & agentData->objectType)
				{
					cohesionForce += neighborBody->GetPosition();
					++groupCount;
				}
			}
		}
	}

	if (groupCount > 0u)
	{
		cohesionForce *= 1 / groupCount;
		cohesionForce -= agentBody->GetPosition();
		cohesionForce.Normalize();
		cohesionForce *= maxSpeed;

		agentBody->ApplyLinearImpulse(cohesionForce, agentBody->GetWorldCenter(), true);
	}
}

void FlockingBehaviors::separate(b2Body* agentBody, const std::vector<b2Body*>& neighborBodies, float maxSpeed)
{
	b2Vec2 separationForce(0.f, 0.f);
	std::size_t groupCount = 0u;
	
	const auto* agentData = static_cast<BodyData*>(agentBody->GetUserData());

	if (!agentData)
	{
		return;
	}

	for (const auto* neighborBody : neighborBodies)
	{
		if (agentBody != neighborBody)
		{
			if (const auto* neighborBodyData = static_cast<BodyData*>(neighborBody->GetUserData()))
			{
				if (neighborBodyData->objectType & agentData->objectType)
				{
					separationForce += agentBody->GetPosition() - neighborBody->GetPosition();
					++groupCount;
				}
			}
		}
	}
	
	if (groupCount > 0u)
	{
		separationForce *= -1 / groupCount;
		separationForce.Normalize();
		separationForce *= maxSpeed;

		agentBody->ApplyLinearImpulse(separationForce, agentBody->GetWorldCenter(), true);
	}
}