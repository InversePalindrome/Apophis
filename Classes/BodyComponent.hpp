/*
Copyright (c) 2018 Inverse Palindrome
Apophis - BodyComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2World.h>

#include <pugixml.hpp>


class BodyComponent
{
public:
	BodyComponent(b2World& world, const pugi::xml_node& componentNode, void* bodyData);

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
	void setLinearVelocity(const b2Vec2& linearVelocity);

	float getAngularVelocity() const;
	void setAngularVelocity(float angularVelocity);

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

	void createBody(b2World& world, const pugi::xml_node& bodyNode, void* bodyData);
	void createFixture(const pugi::xml_node& fixtureNode);
};