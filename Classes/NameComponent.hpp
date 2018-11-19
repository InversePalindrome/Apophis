/*
Copyright (c) 2018 Inverse Palindrome
Apophis - NameComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <pugixml.hpp>

#include <string>


class NameComponent
{
public:
	void load(const pugi::xml_node& componentNode);
	void save(pugi::xml_node& componentNode) const;

	void display();

	std::string getName() const;
	void setName(const std::string& name);

private:
	std::string name;
};