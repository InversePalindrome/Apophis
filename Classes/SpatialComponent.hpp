/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SpatialComponent.hpp
InversePalindrome.com
*/


#pragma once

#include "Vector2.hpp"

#include <pugixml.hpp>


class SpatialComponent
{
public:
	explicit SpatialComponent(const pugi::xml_node& componentNode);
	
	Vector2f getPosition() const;
	void setPosition(const Vector2f& position);
	
	Vector2f getSize() const;
	void setSize(const Vector2f& size);

	float getAngle() const;
	void setAngle(float angle);
	
private:
	Vector2f position;
    Vector2f size;
	float angle;
};