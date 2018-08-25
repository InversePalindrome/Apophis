/*
Copyright (c) 2018 Inverse Palindrome
Apophis - TagsComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <pugixml.hpp>

#include <string>
#include <vector>


class TagsComponent
{
public:
	void load(const pugi::xml_node& componentNode);
	void save(pugi::xml_node& componentNode) const;

	void display();

	void addTag(const std::string& tag = "");

	void removeTag(const std::string& tag);
	void clearTags();

	bool hasTag(const std::string& tag) const;

private:
	std::vector<std::string> tags;
};