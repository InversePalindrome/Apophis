/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SoundComponent.cpp
InversePalindrome.com
*/


#include "SoundComponent.hpp"


SoundComponent::SoundComponent(const pugi::xml_node& componentNode)
{
	for (const auto actionNode : componentNode.children("Action"))
	{
		const auto nameAttribute = actionNode.attribute("name");
		const auto filenameAttribute = actionNode.attribute("filename");

		if (nameAttribute && filenameAttribute)
		{
			sounds.emplace(nameAttribute.as_string(), filenameAttribute.as_string());
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