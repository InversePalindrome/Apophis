/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - BehaviorTreeComponent.cpp
InversePalindrome.com
*/


#include "BehaviorTreeComponent.hpp"


beehive::Status BehaviorTreeComponent::update(entityx::Entity entity)
{
	return tree.process(entity);
}

void BehaviorTreeComponent::setTree(const beehive::Tree<entityx::Entity>& tree)
{
	this->tree = tree;
}