/*
Copyright (c) 2018 Inverse Palindrome
Apophis - BodyComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>

#include <pugixml.hpp>

#include <any>
#include <vector>
#include <variant>


class BodyComponent
{
public:
	explicit BodyComponent(const pugi::xml_node& componentNode);

	void createBody(b2World& world);

	b2Body* getBody();
	b2Body* getBody() const;

	b2World* getWorld();
	b2World* getWorld() const;

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

	void applyLinearImpulse(const b2Vec2& linearImpulse);
	void applyAngularImpulse(float angularImpulse);

	void applyLinearForce(const b2Vec2& linearForce);
	void applyAngularForce(float angularForce);

	bool contains(const b2Vec2& point) const;
	bool raycast(b2RayCastOutput& output, const b2RayCastInput& input) const;

private:
	b2Body* body;
	b2BodyDef bodyDef;
	std::any userData;
	std::vector<b2FixtureDef> fixtureDefs;
	std::vector<std::variant<b2CircleShape, b2PolygonShape>> shapes;

	void initBodyDef(const pugi::xml_node& bodyNode);
	void initFixtureDef(const pugi::xml_node& fixtureNode);
};