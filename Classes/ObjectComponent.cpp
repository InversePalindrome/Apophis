/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ObjectComponent.cpp
InversePalindrome.com
*/


#include "ObjectComponent.hpp"


ObjectComponent::ObjectComponent(const tinyxml2::XMLElement* componentNode) :
	objectType(ObjectType::Undefined)
{
	if (const auto* objectType = componentNode->GetText())
	{
		this->objectType = ObjectType::_from_string(objectType);
	}
}

ObjectType ObjectComponent::getObjectType() const
{
	return objectType;
}

void ObjectComponent::setObjectType(ObjectType objectType)
{
	this->objectType = objectType;
}