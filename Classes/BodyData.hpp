/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - BodyData.hpp
InversePalindrome.com
*/


#pragma once

#include "ObjectType.hpp"

#include <entityx/Entity.h>


struct BodyData
{
	BodyData();

	ObjectType objectType;
	entityx::Entity entity;
};