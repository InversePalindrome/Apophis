/*
Copyright (c) 2018 Inverse Palindrome
Apophis - PursueComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <pugixml.hpp>

#include <chrono>


class PursueComponent
{
public:
	explicit PursueComponent(const pugi::xml_node& componentNode);

	void save(pugi::xml_node& componentNode) const;

	void display();

	std::chrono::milliseconds getPredictionTime() const;
	void setPredictionTime(const std::chrono::milliseconds& predictionTime);

private:
	std::chrono::milliseconds predictionTime;
};