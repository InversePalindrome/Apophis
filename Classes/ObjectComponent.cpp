/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ObjectComponent.cpp
InversePalindrome.com
*/


#include "ObjectComponent.hpp"


ObjectComponent::ObjectComponent(const pugi::xml_node& componentNode) :
	objectType(ObjectType::_from_string(componentNode.text().as_string()))
{
}

ObjectType ObjectComponent::getObjectType() const
{
	return objectType;
}

void ObjectComponent::setObjectType(ObjectType objectType)
{
	this->objectType = objectType;
}