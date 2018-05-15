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
	ObjectType objectType{ ObjectType::Undefined };
	entityx::Entity entity;
};