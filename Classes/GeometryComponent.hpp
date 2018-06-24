/*
Copyright (c) 2018 Inverse Palindrome
Apophis - GeometryComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <pugixml.hpp>

#include <wykobi.hpp>


class GeometryComponent
{
public:
	explicit GeometryComponent(const pugi::xml_node& componentNode);
	
	wykobi::vector2d<float> getPosition() const;
	void setPosition(const wykobi::vector2d<float>& position);

	wykobi::vector2d<float> getSize() const;

	float getAngle() const;
	void setAngle(float angle);


private:
	wykobi::vector2d<float> position;
	wykobi::vector2d<float> size;
	float angle;
};