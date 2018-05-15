/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - AIComponent.hpp
InversePalindrome.com
*/


#pragma once

#include "BehaviorType.hpp"

#include <tinyxml2/tinyxml2.h>


class AIComponent
{
public:
	explicit AIComponent(const tinyxml2::XMLElement* componentNode);

	BehaviorType getBehaviorType() const;
	void setBehaviorType(BehaviorType behaviorType);

private:
	BehaviorType behaviorType;
};