/*
Copyright (c) 2018 Inverse Palindrome
Apophis - GeometryComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <pugixml.hpp>

#include <wykobi.hpp>

#include <vector>
#include <variant>


class GeometryComponent
{
	using Shape = std::variant<wykobi::circle<float>, wykobi::rectangle<float>, wykobi::polygon<float, 2>>;

public:
	explicit GeometryComponent(const pugi::xml_node& componentNode);
	
	wykobi::vector2d<float> getPosition() const;
	void setPosition(const wykobi::vector2d<float>& position);

	wykobi::vector2d<float> getSize() const;

	float getAngle() const;
	void setAngle(float angle);
	
	const std::vector<Shape>& getShapes() const;

	void addShape(const Shape& shape);

private:
	wykobi::vector2d<float> position;
	wykobi::vector2d<float> size;
	float angle;

	wykobi::rectangle<float> AABB;

	std::vector<Shape> shapes;
};