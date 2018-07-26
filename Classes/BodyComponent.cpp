/*
Copyright (c) 2018 Inverse Palindrome
Apophis - BodyComponent.cpp
InversePalindrome.com
*/


#include "BodyComponent.hpp"

#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>

#include <algorithm>


BodyComponent::BodyComponent(b2Body* body) :
	body(body),
    AABB({ {FLT_MAX, FLT_MAX}, {-FLT_MAX, -FLT_MAX} })
{
	body->SetUserData(&userData);
}

void BodyComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.set_name("Body");
	
	componentNode.append_attribute("type") = getBodyType();
	componentNode.append_attribute("x") = getPosition().x;
	componentNode.append_attribute("y") = getPosition().y;
	componentNode.append_attribute("linearDamping") = getLinearDamping();
	componentNode.append_attribute("angularDamping") = getAngularDamping();
	componentNode.append_attribute("fixedRotation") = isRotationFixed();
	componentNode.append_attribute("bullet") = isBullet();

	for (const auto& fixture : fixtures)
	{
		auto fixtureNode = componentNode.append_child();

		fixtureNode.append_attribute("density") = fixture->GetDensity();
		fixtureNode.append_attribute("friction") = fixture->GetFriction();
		fixtureNode.append_attribute("restitution") = fixture->GetRestitution();
		fixtureNode.append_attribute("sensor") = fixture->IsSensor();

		switch (fixture->GetType())
		{
		case b2Shape::e_circle:
		{
			const auto* circleShape = static_cast<b2CircleShape*>(fixture->GetShape());

			fixtureNode.set_name("Circle");
			fixtureNode.append_attribute("x") = circleShape->m_p.x;
			fixtureNode.append_attribute("y") = circleShape->m_p.y;
			fixtureNode.append_attribute("radius") = circleShape->m_radius;
		}
		break;

		case b2Shape::e_polygon:
		{
			const auto* polygonShape = static_cast<b2PolygonShape*>(fixture->GetShape());

			fixtureNode.set_name("Polygon");

			for (std::size_t i = 0; i < polygonShape->GetVertexCount(); ++i)
			{
				auto pointNode = fixtureNode.append_child("Point");
				pointNode.append_attribute("x") = polygonShape->m_vertices[i].x;
				pointNode.append_attribute("y") = polygonShape->m_vertices[i].y;
			}
		}
		break;
		}
	}
}

void BodyComponent::createFixture(const b2FixtureDef& fixtureDef)
{
	fixtures.push_back(body->CreateFixture(&fixtureDef));
}

void BodyComponent::destroyFixture(b2Fixture* fixture)
{
	fixtures.erase(std::remove(std::begin(fixtures), std::end(fixtures), fixture), std::end(fixtures));

	body->DestroyFixture(fixture);
}

b2Body* BodyComponent::getBody()
{
	return body;
}

b2Body* BodyComponent::getBody() const
{
	return body;
}

std::any BodyComponent::getUserData() const
{
	return userData;
}

void BodyComponent::setUserData(const std::any& userData)
{
	this->userData = userData;
}

b2BodyType BodyComponent::getBodyType() const
{
	return body->GetType();
}

void BodyComponent::setBodyType(b2BodyType bodyType)
{
	body->SetType(bodyType);
}

b2Vec2 BodyComponent::getPosition() const
{
	return body->GetPosition();
}

void BodyComponent::setPosition(const b2Vec2& position)
{
    body->SetTransform(position, body->GetAngle());
}

b2Vec2 BodyComponent::getLinearVelocity() const
{
	return body->GetLinearVelocity();
}

void BodyComponent::setLinearVelocity(const b2Vec2& linearVelocity)
{
    body->SetLinearVelocity(linearVelocity);
}

float BodyComponent::getAngularVelocity() const
{
	return body->GetAngularVelocity();
}

void BodyComponent::setAngularVelocity(float angularVelocity)
{
    body->SetAngularVelocity(angularVelocity);
}

float BodyComponent::getAngle() const
{
	return body->GetAngle();
}

void BodyComponent::setAngle(float angle)
{
    body->SetTransform(body->GetPosition(), angle);
}

float BodyComponent::getMass() const
{
	return body->GetMass();
}

float BodyComponent::getInertia() const
{
	return body->GetInertia();
}

float BodyComponent::getLinearDamping() const
{
	return body->GetLinearDamping();
}

void BodyComponent::setLinearDamping(float linearDamping)
{
	body->SetLinearDamping(linearDamping);
}

float BodyComponent::getAngularDamping() const
{
	return body->GetAngularDamping();
}

void BodyComponent::setAngularDamping(float angularDamping)
{
	body->SetAngularDamping(angularDamping);
}

b2AABB BodyComponent::getAABB() const
{
	return AABB;
}

void BodyComponent::computeAABB()
{
	for (const auto& fixture : fixtures)
	{
		for (int child = 0; child < fixture->GetShape()->GetChildCount(); ++child)
		{
			b2Transform transform;
			transform.SetIdentity();

			b2AABB shapeAABB{ { FLT_MAX, FLT_MAX },{ -FLT_MAX, -FLT_MAX } };
			fixture->GetShape()->ComputeAABB(&shapeAABB, transform, child);

			AABB.Combine(shapeAABB);
		}
	}
}

void BodyComponent::applyLinearImpulse(const b2Vec2& linearImpulse)
{
    body->ApplyLinearImpulse(linearImpulse, body->GetWorldCenter(), true);
}

void BodyComponent::applyAngularImpulse(float angularImpulse)
{
	body->ApplyAngularImpulse(angularImpulse, true);
}

void BodyComponent::applyLinearForce(const b2Vec2& linearForce)
{
    body->ApplyForceToCenter(linearForce, true);
}

void BodyComponent::applyAngularForce(float angularForce)
{
    body->ApplyTorque(angularForce, true); 
}

bool BodyComponent::isRotationFixed() const
{
	return body->IsFixedRotation();
}

void BodyComponent::setRotationFixed(bool rotationFixed)
{
	body->SetFixedRotation(rotationFixed);
}

bool BodyComponent::isBullet() const
{
	return body->IsBullet();
}

void BodyComponent::setBullet(bool bullet)
{
	body->SetBullet(bullet);
}

bool BodyComponent::contains(const b2Vec2& point) const
{
	for (const auto& fixture : fixtures)
	{
		if (fixture->TestPoint(point))
		{
			return true;
		}
	}
	
	return false;
}

bool BodyComponent::raycast(b2RayCastOutput& output, const b2RayCastInput& input) const
{
	for (const auto& fixture : fixtures)
	{
		if (fixture->RayCast(&output, input, 0))
		{
			return true;
		}
	}

	return false;
}