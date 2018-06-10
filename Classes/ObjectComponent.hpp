/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ObjectComponent.hpp
InversePalindrome.com
*/


#pragma once

#include "ObjectType.hpp"

#include <pugixml.hpp>


class ObjectComponent
{
public:
	explicit ObjectComponent(const pugi::xml_node& componentNode);

	ObjectType getObjectType() const;
	void setObjectType(ObjectType objectType);

private:
	ObjectType objectType;
};