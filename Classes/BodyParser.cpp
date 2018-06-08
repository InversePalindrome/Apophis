/*
Copyright (c) 2018 Inverse Palindrome
Apophis  - BodyParser.cpp
InversePalindrome.com
*/


#include "BodyParser.hpp"

#include <string>
#include <vector>
#include <sstream>


b2BodyDef BodyParser::createBodyDef(const tinyxml2::XMLElement* bodyNode)
{
	b2BodyDef bodyDef;

	if (const auto* bodyType = bodyNode->Attribute("type"))
	{
		bodyDef.type = static_cast<b2BodyType>(std::stoi(bodyType));
	}
	if (const auto* linearDamping = bodyNode->Attribute("linearDamping"))
	{
		bodyDef.linearDamping = std::stof(linearDamping);
	}
	if (const auto* angularDamping = bodyNode->Attribute("angularDamping"))
	{
		bodyDef.angularDamping = std::stof(angularDamping);
	}
	if (const auto* fixedRotation = bodyNode->Attribute("fixedRotation"))
	{
		std::istringstream iStream(fixedRotation);

		iStream >> std::boolalpha >> bodyDef.fixedRotation;
	}
	if (const auto* bullet = bodyNode->Attribute("bullet"))
	{
		std::istringstream iStream(bullet);

		iStream >> std::boolalpha >> bodyDef.bullet;
	}
	if (const auto* x = bodyNode->Attribute("x"))
	{
		bodyDef.position.x = std::stof(x);
	}
	if (const auto* y = bodyNode->Attribute("y"))
	{
		bodyDef.position.y = std::stof(y);
	}
	if (const auto* angle = bodyNode->Attribute("angle"))
	{
		bodyDef.angle = std::stof(angle);
	}

	return bodyDef;
}

b2FixtureDef BodyParser::createFixtureDef(const tinyxml2::XMLElement* fixtureNode)
{
	b2FixtureDef fixtureDef;

	if (const auto* density = fixtureNode->Attribute("density"))
	{
		fixtureDef.density = std::stof(density);
	}
	if (const auto* friction = fixtureNode->Attribute("friction"))
	{
		fixtureDef.friction = std::stof(friction);
	}
	if (const auto* restitution = fixtureNode->Attribute("restitution"))
	{
		fixtureDef.restitution = std::stof(restitution);
	}
	if (const auto* sensor = fixtureNode->Attribute("sensor"))
	{
		std::istringstream iStream(sensor);

		iStream >> std::boolalpha >> fixtureDef.isSensor;
	}

	return fixtureDef;
}

b2CircleShape BodyParser::createCircle(const tinyxml2::XMLElement* shapeNode)
{
	b2CircleShape circle;

	if (const auto* x = shapeNode->Attribute("x"))
	{
		circle.m_p.x = std::stof(x);
	}
	if (const auto* y = shapeNode->Attribute("y"))
	{
		circle.m_p.y = std::stof(y);
	}
	if (const auto* radius = shapeNode->Attribute("radius"))
	{
		circle.m_radius = std::stof(radius);
	}

	return circle;
}

b2PolygonShape BodyParser::createPolygon(const tinyxml2::XMLElement* shapeNode)
{
	b2PolygonShape polygon;

	std::vector<b2Vec2> vertices;

	for (const auto* vertextNode = shapeNode->FirstChildElement("Vertex"); vertextNode; vertextNode = vertextNode->NextSiblingElement("Vertex"))
	{
		const auto* x = vertextNode->Attribute("x");
		const auto* y = vertextNode->Attribute("y");

		if (x && y)
		{
			vertices.push_back({ std::stof(x), std::stof(y) });
		}
	}
	
	polygon.Set(vertices.data(), vertices.size());

	return polygon;
}