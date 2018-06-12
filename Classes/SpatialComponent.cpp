/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SpatialComponent.cpp
InversePalindrome.com
*/


#include "SpatialComponent.hpp"


SpatialComponent::SpatialComponent(const pugi::xml_node& componentNode) :
	position({0.f, 0.f}),
	size({ 0.f, 0.f }),
	angle(0.f)
{
	if (const auto xPositionAttribute = componentNode.attribute("x"))
	{
		position[0] = xPositionAttribute.as_float();
	}
	if (const auto yPositionAttribute = componentNode.attribute("y"))
	{
		position[1] = yPositionAttribute.as_float();
	}
	if (const auto widthAttribute = componentNode.attribute("width"))
	{
		size[0] = widthAttribute.as_float();
	}
	if (const auto heightAttribute = componentNode.attribute("height"))
	{
		size[1] = heightAttribute.as_float();
	}
	if (const auto angleAttribute = componentNode.attribute("angle"))
	{
		angle = angleAttribute.as_float();
	}
}

Vector2f SpatialComponent::getPosition() const
{
	return position;
}

void SpatialComponent::setPosition(const Vector2f& position)
{
	this->position = position;
}

Vector2f SpatialComponent::getSize() const
{
	return size;
}

void SpatialComponent::setSize(const Vector2f& size)
{
	this->size = size;
}

float SpatialComponent::getAngle() const
{
	return angle;
}

void SpatialComponent::setAngle(float angle)
{
	this->angle = angle;
}