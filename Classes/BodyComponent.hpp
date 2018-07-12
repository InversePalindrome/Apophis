/*
Copyright (c) 2018 Inverse Palindrome
Apophis - BodyComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>

#include <any>
#include <vector>


class BodyComponent
{
public:
	explicit BodyComponent(b2Body* body);

	void createFixture(const b2FixtureDef& fixtureDef);
	void destroyFixture(b2Fixture* fixture);

	b2Body* getBody();
	b2Body* getBody() const;

	std::any getUserData() const;
	void setUserData(std::any userData);

	b2Vec2 getPosition() const;
	void setPosition(const b2Vec2& position);

	b2Vec2 getLinearVelocity() const;
	void setLinearVelocity(const b2Vec2& linearVelocity);

	float getAngularVelocity() const;
	void setAngularVelocity(float angularVelocity);

	float getAngle() const;
	void setAngle(float angle);

	float getMass() const;
	float getInertia() const;

	b2AABB getAABB() const;
	void computeAABB();

	void applyLinearImpulse(const b2Vec2& linearImpulse);
	void applyAngularImpulse(float angularImpulse);

	void applyLinearForce(const b2Vec2& linearForce);
	void applyAngularForce(float angularForce);

	bool contains(const b2Vec2& point) const;
	bool raycast(b2RayCastOutput& output, const b2RayCastInput& input) const;

private:
	b2Body* body;
	std::vector<b2Fixture*> fixtures;

	b2AABB AABB;

	std::any userData;
};