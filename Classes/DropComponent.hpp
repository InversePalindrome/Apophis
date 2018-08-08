/*
Copyright (c) 2018 Inverse Palindrome
Apophis - DropComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <pugixml.hpp>

#include <string>
#include <vector>


class DropComponent
{
public:
	explicit DropComponent(const pugi::xml_node& componentNode);

	void save(pugi::xml_node& componentNode) const;

	void display();

	const std::vector<std::string>& getItems() const;
	const std::vector<int>& getWeights() const;

	void addItem(const std::string& item, int weight);
	void removeItem(const std::string& item);

private:
	std::vector<std::string> items;
	std::vector<int> weights;
};