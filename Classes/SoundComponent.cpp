/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - SoundComponent.cpp
InversePalindrome.com
*/


#include "SoundComponent.hpp"


SoundComponent::SoundComponent(const tinyxml2::XMLElement* componentNode)
{
	for (const auto* actionNode = componentNode->FirstChildElement("Action"); actionNode; actionNode = actionNode->NextSiblingElement("Action"))
	{
		const auto* name = actionNode->Attribute("name");
		const auto* filename = actionNode->Attribute("filename");
		
		if (name && filename)
		{
			sounds.insert({ name, filename });
		}
	}
}

std::string SoundComponent::getSound(const std::string& action) const
{
	return sounds.at(action);
}

bool SoundComponent::hasSound(const std::string& action) const
{
	return sounds.count(action);
}