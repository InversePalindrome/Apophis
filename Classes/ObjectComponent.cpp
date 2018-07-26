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

void ObjectComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.set_name("Object");

	componentNode.text().set(objectType._to_string());
}

ObjectType ObjectComponent::getObjectType() const
{
	return objectType;
}

void ObjectComponent::setObjectType(ObjectType objectType)
{
	this->objectType = objectType;
}