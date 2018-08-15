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

	const std::vector<std::string>& getItemFilenames() const;
	const std::vector<int>& getWeights() const;

	void addItem(const std::string& itemFilename, int weight);
	void removeItem(const std::string& itemFilename);

private:
	std::vector<std::string> itemFilenames;
	std::vector<int> weights;
};