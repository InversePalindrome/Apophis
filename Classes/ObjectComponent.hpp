/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ObjectComponent.hpp
InversePalindrome.com
*/


#pragma once

#include "ObjectType.hpp"

#include <tinyxml2/tinyxml2.h>


class ObjectComponent
{
public:
	explicit ObjectComponent(const tinyxml2::XMLElement* componentNode);

	ObjectType getObjectType() const;
	void setObjectType(ObjectType objectType);

private:
	ObjectType objectType;
};