/*
Copyright (c) 2018 Inverse Palindrome
Apophis - GeometryComponent.cpp
InversePalindrome.com
*/


#include "GeometryComponent.hpp"


GeometryComponent::GeometryComponent(const pugi::xml_node& componentNode) :
	position(0.f, 0.f),
	size(0.f, 0.f),
	angle(0.f)
{
	if (const auto xPositionAttribute = componentNode.attribute("x"))
	{
		position.x = xPositionAttribute.as_float();
	}
	if (const auto yPositionAttribute = componentNode.attribute("y"))
	{
		position.y = yPositionAttribute.as_float();
	}
	if (const auto widthAttribute = componentNode.attribute("width"))
	{
		size.x = widthAttribute.as_float();
	}
	if (const auto heightAttribute = componentNode.attribute("height"))
	{
		size.y = heightAttribute.as_float();
	}
	if (const auto angleAttribute = componentNode.attribute("angle"))
	{
		angle = angleAttribute.as_float();
	}
}

b2Vec2 GeometryComponent::getPosition() const
{
	return position;
}

void GeometryComponent::setPosition(const b2Vec2& position)
{
	this->position = position;
}

b2Vec2 GeometryComponent::getSize() const
{
	return size;
}

void GeometryComponent::setSize(const b2Vec2& size)
{
	this->size = size;
}

float GeometryComponent::getAngle() const
{
	return angle;
}

void GeometryComponent::setAngle(float angle)
{
	this->angle = angle;
}