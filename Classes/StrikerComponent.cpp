/*
Copyright (c) 2018 Inverse Palindrome
Apophis - StrikerComponent.cpp
InversePalindrome.com
*/


#include "StrikerComponent.hpp"


void StrikerComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.set_name("Striker");
}