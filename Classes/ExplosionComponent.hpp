/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ExplosionComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <pugixml.hpp>

#include <chrono>


class ExplosionComponent
{
public:
    ExplosionComponent();

    void load(const pugi::xml_node& componentNode);
    void save(pugi::xml_node& componentNode) const;

    void display();

    std::string getExplosionFilename() const;
    void setExplosionFilename(const std::string& explosionFilename);

    std::chrono::milliseconds getExplosionTime() const;
    void setExplosionTime(const std::chrono::milliseconds& explosionTime);

private:
    std::string explosionFilename;

    std::chrono::milliseconds explosionTime;
};