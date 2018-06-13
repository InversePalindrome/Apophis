/*
Copyright (c) 2018 Inverse Palindrome
Apophis - GeometryComponent.cpp
InversePalindrome.com
*/


#include "GeometryComponent.hpp"


GeometryComponent::GeometryComponent(const pugi::xml_node& componentNode) :
	position({ 0.f, 0.f }),
	AABB(wykobi::make_rectangle(0.f, 0.f, 0.f, 0.f)),
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
	if (const auto angleAttribute = componentNode.attribute("angle"))
	{
		angle = angleAttribute.as_float();
	}
	
	for (const auto shapeNode : componentNode.children())
	{
		if (std::strcmp(shapeNode.name(), "Circle") == 0)
		{
			auto circle = wykobi::make_circle(0.f, 0.f, 0.f);
			
			if (const auto xAttribute = shapeNode.attribute("x"))
			{
				circle.x = xAttribute.as_float();
			}
			if (const auto yAttribute = shapeNode.attribute("y"))
			{
				circle.y = yAttribute.as_float();
			}
		    if (const auto radiusAttribute = shapeNode.attribute("radius"))
			{
				circle.radius = radiusAttribute.as_float();
			}
			
			addAABB(wykobi::aabb(circle));

			shapes.push_back(circle);
		}
		else if (std::strcmp(shapeNode.name(), "Polygon") == 0)
		{
			wykobi::polygon<float, 2> polygon;

			for (const auto pointNode : shapeNode.children("Point"))
			{
				const auto xAttribute = pointNode.attribute("x");
				const auto yAttribute = pointNode.attribute("y");

				if (xAttribute && yAttribute)
				{
					polygon.push_back(wykobi::make_point(xAttribute.as_float(), yAttribute.as_float()));
				}
			}

			addAABB(wykobi::aabb(polygon));

			shapes.push_back(polygon);
		}
	}
}

wykobi::vector2d<float> GeometryComponent::getPosition() const
{
	return position;
}

void GeometryComponent::setPosition(const wykobi::vector2d<float>& position)
{
	this->position = position;
}

wykobi::rectangle<float> GeometryComponent::getAABB() const
{
	return AABB;
}

float GeometryComponent::getAngle() const
{
	return angle;
}

void GeometryComponent::setAngle(float angle)
{
	this->angle = angle;
}

void GeometryComponent::addAABB(const wykobi::rectangle<float>& shapeAABB)
{
	AABB[0][0] = wykobi::min(AABB[0].x, shapeAABB[0].x);
	AABB[0][1] = wykobi::min(AABB[0].y, shapeAABB[0].y);
	AABB[1][0] = wykobi::max(AABB[1].x, shapeAABB[1].x);
	AABB[1][1] = wykobi::max(AABB[1].y, shapeAABB[1].y);
}