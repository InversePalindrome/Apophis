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
public:
	explicit GeometryComponent(const pugi::xml_node& componentNode);
	
	wykobi::vector2d<float> getPosition() const;
	void setPosition(const wykobi::vector2d<float>& position);

	wykobi::rectangle<float> getAABB() const;

	float getAngle() const;
	void setAngle(float angle);
	
private:
	wykobi::vector2d<float> position;
	wykobi::rectangle<float> AABB;
	float angle;

	std::vector<std::variant<wykobi::circle<float>, wykobi::polygon<float, 2>>> shapes;

	void addAABB(const wykobi::rectangle<float>& shapeAABB);
};