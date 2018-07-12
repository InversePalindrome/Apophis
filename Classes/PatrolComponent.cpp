/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PatrolComponent.cpp
InversePalindrome.com
*/


#include "PatrolComponent.hpp"


PatrolComponent::PatrolComponent(const pugi::xml_node& componentNode) :
	currentIndex(0u)
{
	for (const auto pointNode : componentNode.children("Point"))
	{
		if (const auto xPositionAttribute = pointNode.attribute("x"),
			yPositionAttribute = pointNode.attribute("y");
		    xPositionAttribute && yPositionAttribute)
		{
			path.push_back({ xPositionAttribute.as_float(), yPositionAttribute.as_float() });
		}
	}
}

void PatrolComponent::nextPoint()
{
	if (++currentIndex == path.size())
	{
		currentIndex = 0u;
	}
}

b2Vec2 PatrolComponent::getCurrentPoint() const
{
	return path.at(currentIndex);
}

bool PatrolComponent::hasPoints() const
{
	return !path.empty();
}