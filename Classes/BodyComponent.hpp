/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - BodyComponent.hpp
InversePalindrome.com
*/


#pragma once

#include "BodyData.hpp"

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/b2Fixture.h>

#include <entityx/Entity.h>

#include <tinyxml2/tinyxml2.h>

#include <list>
#include <vector>


class BodyComponent
{
public:
	BodyComponent(const tinyxml2::XMLElement* componentNode, b2World& world, entityx::Entity entity);

	b2Body* getBody();
	b2Body* getBody() const;

	b2World* getWorld();
	b2World* getWorld() const;

	BodyData& getBodyData();

	b2Vec2 getPosition() const;
	void setPosition(const b2Vec2& position);

	b2AABB getAABB() const;

	b2Vec2 getLinearVelocity() const;
	void setLinearVelocity(const b2Vec2& velocity);

	float getAngularVelocity() const;
	void setAngularVelocity(float velocity);

	float getAngle() const;
	void setAngle(float angle);

	float getMass() const;
	float getInertia() const;

	void applyForce(const b2Vec2& force);
	void applyLinearImpulse(const b2Vec2& impulse);
	void applyAngularImpulse(float impulse);

	bool contains(const b2Vec2& point) const;
	bool raycast(b2RayCastOutput& output, const b2RayCastInput& input) const;

private:
	b2Body* body;
    BodyData bodyData;
	b2AABB aabb;

	void createBody(const tinyxml2::XMLElement* bodyNode, b2World& world, entityx::Entity entity);
	void createFixture(const tinyxml2::XMLElement* fixtureNode);
	void createAABB();
};