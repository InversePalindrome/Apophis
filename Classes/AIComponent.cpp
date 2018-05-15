/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - AIComponent.cpp
InversePalindrome.com
*/


#include "AIComponent.hpp"


AIComponent::AIComponent(const tinyxml2::XMLElement* componentNode) :
	behaviorType(BehaviorType::Undefined)
{
	if (const auto* behaviorType = componentNode->GetText())
	{
		this->behaviorType = BehaviorType::_from_string(behaviorType);
	}
}

BehaviorType AIComponent::getBehaviorType() const
{
	return behaviorType;
}

void AIComponent::setBehaviorType(BehaviorType behaviorType)
{
	this->behaviorType = behaviorType;
}