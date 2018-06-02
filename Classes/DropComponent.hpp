/*
Copyright (c) 2018 Inverse Palindrome
Apophis - DropComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <tinyxml2/tinyxml2.h>

#include <string>
#include <vector>
#include <random>


class DropComponent
{
public:
	explicit DropComponent(const tinyxml2::XMLElement* componentNode);

	std::string getItem();

	void addItem(const std::string& item, int weight);
	void removeItem(const std::string& item);

private:
	std::vector<std::string> items;
	std::vector<int> weights;

	std::mt19937 randomEngine;
};