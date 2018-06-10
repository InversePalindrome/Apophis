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
		const auto xAttribute = pointNode.attribute("x");
		const auto yAttribute = pointNode.attribute("y");

		if (xAttribute && yAttribute)
		{
			path.push_back({ xAttribute.as_float(), yAttribute.as_float() });
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