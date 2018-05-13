/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - BehaviorTreeComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <entityx/Entity.h>

#include <beehive/beehive.hpp>


class BehaviorTreeComponent
{
public:
	beehive::Status update(entityx::Entity entity);

	void setTree(const beehive::Tree<entityx::Entity>& tree);

private:
	beehive::Tree<entityx::Entity> tree;
};