/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PlayerComponent.cpp
InversePalindrome.com
*/


#include "PlayerComponent.hpp"


void PlayerComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.set_name("Player");
}