/*
Copyright (c) 2018 Inverse Palindrome
Apophis - GeometryComponent.cpp
InversePalindrome.com
*/


#include "GeometryComponent.hpp"


GeometryComponent::GeometryComponent(const pugi::xml_node& componentNode) :
	position(0.f, 0.f),
	size(0.f, 0.f),
	angle(0.f),
	AABB(wykobi::make_rectangle(0.f, 0.f, 0.f, 0.f))
{
	if (const auto xPositionAttribute = componentNode.attribute("x"))
	{
		position.x = xPositionAttribute.as_float();
	}
	if (const auto yPositionAttribute = componentNode.attribute("y"))
	{
		position.y = yPositionAttribute.as_float();
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
			
			addShape(circle);
		}
		else if (std::strcmp(shapeNode.name(), "Rectangle") == 0)
		{
			auto rectangle = wykobi::make_rectangle(0.f, 0.f, 0.f, 0.f);

			if (const auto width = shapeNode.attribute("width"))
			{
				rectangle[1][0] = width.as_float();
			}
			if (const auto height = shapeNode.attribute("height"))
			{
				rectangle[1][1] = height.as_float();
			}
			
			addShape(rectangle);
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

			addShape(polygon);
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

wykobi::vector2d<float> GeometryComponent::getSize() const
{
	return size;
}

float GeometryComponent::getAngle() const
{
	return angle;
}

void GeometryComponent::setAngle(float angle)
{
	this->angle = angle;
}

const std::vector<GeometryComponent::Shape>& GeometryComponent::getShapes() const
{
	return shapes;
}

void GeometryComponent::addShape(const Shape& shape)
{
	shapes.push_back(shape);

	std::visit([this](const auto& shape) 
	{
		const auto& shapeAABB = wykobi::aabb(shape);

		AABB[0][0] = wykobi::min(AABB[0].x, shapeAABB[0].x);
		AABB[0][1] = wykobi::min(AABB[0].y, shapeAABB[0].y);
		AABB[1][0] = wykobi::max(AABB[1].x, shapeAABB[1].x);
		AABB[1][1] = wykobi::max(AABB[1].y, shapeAABB[1].y);
	}, shape);

	size = AABB[1] - AABB[0];
}