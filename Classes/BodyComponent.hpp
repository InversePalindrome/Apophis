/*
Copyright (c) 2018 Inverse Palindrome
Apophis - BodyComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2World.h>

#include <tinyxml2/tinyxml2.h>


class BodyComponent
{
public:
	BodyComponent(const tinyxml2::XMLElement* componentNode, b2World& world);

	b2Body* getBody();
	b2Body* getBody() const;

	b2World* getWorld();
	b2World* getWorld() const;

	void* getUserData() const;
	void setUserData(void* userData);

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

	void applyLinearImpulse(const b2Vec2& linearImpulse);
	void applyAngularImpulse(float angularImpulse);

	void applyLinearForce(const b2Vec2& linearForce);
	void applyAngularForce(float angularForce);

	bool contains(const b2Vec2& point) const;
	bool raycast(b2RayCastOutput& output, const b2RayCastInput& input) const;

private:
	b2Body* body;

	void createBody(const tinyxml2::XMLElement* bodyNode, b2World& world);
	void createFixture(const tinyxml2::XMLElement* fixtureNode);
};