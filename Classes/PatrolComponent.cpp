/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - PatrolComponent.cpp
InversePalindrome.com
*/


#include "PatrolComponent.hpp"

#include <string>


PatrolComponent::PatrolComponent(const tinyxml2::XMLElement* componentNode) :
	currentIndex(0u)
{
	for (const auto* pointNode = componentNode->FirstChildElement("Point"); pointNode; pointNode = pointNode->NextSiblingElement("Point"))
	{
		const auto* x = pointNode->Attribute("x");
		const auto* y = pointNode->Attribute("y");

		if (x && y)
		{
			path.push_back({ std::stof(x), std::stof(y) });
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