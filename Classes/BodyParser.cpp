/*
Copyright (c) 2018 Inverse Palindrome
Apophis - BodyParser.cpp
InversePalindrome.com
*/


#include "BodyParser.hpp"

#include <vector>


void BodyParser::parseBodyDef(b2BodyDef& bodyDef, const pugi::xml_node& bodyNode)
{
	if (const auto bodyTypeAttribute = bodyNode.attribute("type"))
	{
		bodyDef.type = static_cast<b2BodyType>(bodyTypeAttribute.as_int());
	}
	if (const auto linearDampingAttribute = bodyNode.attribute("linearDamping"))
	{
		bodyDef.linearDamping = linearDampingAttribute.as_float();
	}
	if (const auto angularDampingAttribute = bodyNode.attribute("angularDamping"))
	{
		bodyDef.angularDamping = angularDampingAttribute.as_float();
	}
	if (const auto fixedRotationAttribute = bodyNode.attribute("fixedRotation"))
	{
		bodyDef.fixedRotation = fixedRotationAttribute.as_bool();
	}
	if (const auto bulletAttribute = bodyNode.attribute("bullet"))
	{
		bodyDef.bullet = bulletAttribute.as_bool();
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

void BodyParser::parseCircleShape(b2CircleShape& circleShape, const pugi::xml_node& circleNode)
{
	if (const auto xAttribute = circleNode.attribute("x"))
	{
		circleShape.m_p.x = xAttribute.as_float();
	}
	if (const auto yAttribute = circleNode.attribute("y"))
	{
		circleShape.m_p.y = yAttribute.as_float();
	}
	if (const auto radiusAttribute = circleNode.attribute("radius"))
	{
		circleShape.m_radius = radiusAttribute.as_float();
	}
}

void BodyParser::parseRectangleShape(b2PolygonShape& rectangleShape, const pugi::xml_node& rectangleNode)
{
	b2Vec2 center(0.f, 0.f);
	float width = 1.f, height = 1.f, angle = 0.f;

	if (const auto xAttribute = rectangleNode.attribute("x"))
	{
		center.x = xAttribute.as_float();
	}
	if (const auto yAttribute = rectangleNode.attribute("y"))
	{
		center.y = yAttribute.as_float();
	}
	if (const auto widthAttribute = rectangleNode.attribute("width"))
	{
		width = widthAttribute.as_float();
	}
	if (const auto heightAttribute = rectangleNode.attribute("height"))
	{
		height = heightAttribute.as_float();
	}
	if (const auto angleAttribute = rectangleNode.attribute("angle"))
	{
		angle = angleAttribute.as_float();
	}
	
	rectangleShape.SetAsBox(width, height, center, angle);
}

void BodyParser::parsePolygonShape(b2PolygonShape& polygonShape, const pugi::xml_node& polygonNode)
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

	polygonShape.Set(points.data(), points.size());
}