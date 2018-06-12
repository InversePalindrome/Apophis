/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ExplosionComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <pugixml.hpp>

#include <string>
#include <chrono>


class ExplosionComponent
{
public:
	explicit ExplosionComponent(const pugi::xml_node& componentNode);

	std::string getExplosionName() const;
	void setExplosionName(const std::string& explosionName);

    std::chrono::milliseconds getExplosionTime() const;
	void setExplosionTime(const std::chrono::milliseconds& explosionTime);

private:
	std::string explosionName;
	std::chrono::milliseconds explosionTime;
};