/*
Copyright (c) 2018 Inverse Palindrome
Apophis - BodyParser.cpp
InversePalindrome.com
*/


#include "BodyParser.hpp"

#include <vector>


void BodyParser::parseBody(b2Body* body, const pugi::xml_node& bodyNode)
{
	if (const auto bodyTypeAttribute = bodyNode.attribute("type"))
	{
		body->SetType(static_cast<b2BodyType>(bodyTypeAttribute.as_int()));
	}
	if (const auto xPositionAttribute = bodyNode.attribute("x"),
		yPositionAttribute = bodyNode.attribute("y");
	    xPositionAttribute && yPositionAttribute)
	{
		body->SetTransform({ xPositionAttribute.as_float(), yPositionAttribute.as_float() }, body->GetAngle()); 
	}
	if (const auto angleAttribute = bodyNode.attribute("angle"))
	{
		body->SetTransform(body->GetPosition(), angleAttribute.as_float());
	}
	if (const auto linearDampingAttribute = bodyNode.attribute("linearDamping"))
	{
		body->SetLinearDamping(linearDampingAttribute.as_float());
	}
	if (const auto angularDampingAttribute = bodyNode.attribute("angularDamping"))
	{
		body->SetAngularVelocity(angularDampingAttribute.as_float());
	}
	if (const auto fixedRotationAttribute = bodyNode.attribute("fixedRotation"))
	{
		body->SetFixedRotation(fixedRotationAttribute.as_bool());
	}
	if (const auto bulletAttribute = bodyNode.attribute("bullet"))
	{
		body->SetBullet(bulletAttribute.as_bool());
	}
}

void BodyParser::parseFixtureDef(b2FixtureDef& fixtureDef, const pugi::xml_node& fixtureNode)
{
	if (const auto densityAttribute = fixtureNode.attribute("density"))
	{
		fixtureDef.density = densityAttribute.as_float();
	}
	if (const auto frictionAttribute = fixtureNode.attribute("friction"))
	{
		fixtureDef.friction = frictionAttribute.as_float();
	}
	if (const auto restitutionAttribute = fixtureNode.attribute("restitution"))
	{
		fixtureDef.restitution = restitutionAttribute.as_float();
	}
	if (const auto sensorAttribute = fixtureNode.attribute("sensor"))
	{
		fixtureDef.isSensor = sensorAttribute.as_bool();
	}
}

void BodyParser::parseCircleShape(b2CircleShape& circle, const pugi::xml_node& circleNode)
{
	if (const auto xAttribute = circleNode.attribute("x"))
	{
		circle.m_p.x = xAttribute.as_float();
	}
	if (const auto yAttribute = circleNode.attribute("y"))
	{
		circle.m_p.y = yAttribute.as_float();
	}
	if (const auto radiusAttribute = circleNode.attribute("radius"))
	{
		circle.m_radius = radiusAttribute.as_float();
	}
}

void BodyParser::parseEdgeShape(b2EdgeShape& edge, const pugi::xml_node& edgeNode)
{
	if (const auto hasVertex0Attribute = edgeNode.attribute("hasVertex0"))
	{
		if (hasVertex0Attribute.as_bool())
		{
			edge.m_hasVertex0 = true;

			if (const auto vertex0XAttribute = edgeNode.attribute("vertex0X"))
			{
				edge.m_vertex0.x = vertex0XAttribute.as_float();
			}
			if (const auto vertex0YAttribute = edgeNode.attribute("vertex0Y"))
			{
				edge.m_vertex0.y = vertex0YAttribute.as_float();
			}
		}
		else
		{
			edge.m_hasVertex0 = false;
		}
	}

	if (const auto vertex1XAttribute = edgeNode.attribute("vertex1X"))
	{
		edge.m_vertex1.x = vertex1XAttribute.as_float();
	}
	if (const auto vertex1YAttribute = edgeNode.attribute("vertex1Y"))
	{
		edge.m_vertex1.y = vertex1YAttribute.as_float();
	}
	if (const auto vertex2XAttribute = edgeNode.attribute("vertex2X"))
	{
		edge.m_vertex2.x = vertex2XAttribute.as_float();
	}
	if (const auto vertex2YAttribute = edgeNode.attribute("vertex2Y"))
	{
		edge.m_vertex2.y = vertex2YAttribute.as_float();
	}

	if (const auto hasVertex3Attribute = edgeNode.attribute("hasVertex3"))
	{
		if (hasVertex3Attribute.as_bool())
		{
			edge.m_hasVertex3 = true;

			if (const auto vertex3XAttribute = edgeNode.attribute("vertex3X"))
			{
				edge.m_vertex3.x = vertex3XAttribute.as_float();
			}
			if (const auto vertex3YAttribute = edgeNode.attribute("vertex3Y"))
			{
				edge.m_vertex3.y = vertex3YAttribute.as_float();
			}
		}
		else
		{
			edge.m_hasVertex3 = false;
		}
	}
}

void BodyParser::parsePolygonShape(b2PolygonShape& polygon, const pugi::xml_node& polygonNode)
{
	std::vector<b2Vec2> points;

	for (const auto pointNode : polygonNode.children("Point"))
	{
		b2Vec2 point(0.f, 0.f);

		if (const auto xAttribute = pointNode.attribute("x"))
		{
			point.x = xAttribute.as_float();
		}
		if (const auto yAttribute = pointNode.attribute("y"))
		{
			point.y = yAttribute.as_float();
		}

		points.push_back(point);
	}
	
	polygon.Set(points.data(), points.size());
}

void BodyParser::parseChainShape(b2ChainShape& chain, const pugi::xml_node& chainNode)
{
	std::vector<b2Vec2> points;

	for (const auto pointNode : chainNode.children("Point"))
	{
		b2Vec2 point(0.f, 0.f);

		if (const auto xAttribute = pointNode.attribute("x"))
		{
			point.x = xAttribute.as_float();
		}
		if (const auto yAttribute = pointNode.attribute("y"))
		{
			point.y = yAttribute.as_float();
		}

		points.push_back(point);
	}

	chain.CreateChain(points.data(), points.size());
}