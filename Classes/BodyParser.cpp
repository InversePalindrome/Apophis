/*
Copyright (c) 2018 Inverse Palindrome
Apophis - BodyParser.cpp
InversePalindrome.com
*/


#include "BodyParser.hpp"

#include <vector>


b2BodyDef BodyParser::createBodyDef(const pugi::xml_node& bodyNode)
{
	b2BodyDef bodyDef;
	
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

	return bodyDef;
}

b2FixtureDef BodyParser::createFixtureDef(const pugi::xml_node& fixtureNode)
{
	b2FixtureDef fixtureDef;

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

	return fixtureDef;
}

b2CircleShape BodyParser::createCircle(const pugi::xml_node& circleNode)
{
	b2CircleShape circle;
	
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

	return circle;
}

b2PolygonShape BodyParser::createRectangle(const pugi::xml_node& rectangleNode)
{
	b2PolygonShape rectangle;

	b2Vec2 center(0.f, 0.f);
	float width = 0.f, height = 0.f, angle = 0.f;

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

	rectangle.SetAsBox(width, height, center, angle);

	return rectangle;
}

b2PolygonShape BodyParser::createPolygon(const pugi::xml_node& polygonNode)
{
	b2PolygonShape polygon;

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

	return polygon;
}


std::variant<b2CircleShape, b2PolygonShape> BodyParser::createShape(const pugi::xml_node& shapeNode)
{
	if (std::strcmp(shapeNode.name(), "Circle") == 0)
	{
		return BodyParser::createCircle(shapeNode);
	}
	else if (std::strcmp(shapeNode.name(), "Rectangle") == 0)
	{
		return BodyParser::createRectangle(shapeNode);
	}
	else if (std::strcmp(shapeNode.name(), "Polygon") == 0)
	{
		return BodyParser::createPolygon(shapeNode);
	}
}