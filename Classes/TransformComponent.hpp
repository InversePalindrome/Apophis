/*
Copyright (c) 2018 Inverse Palindrome
Apophis - TransformComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <Box2D/Common/b2Math.h>

#include <pugixml.hpp>


class TransformComponent
{
public:
    TransformComponent();

    void load(const pugi::xml_node& componentNode);
    void save(pugi::xml_node& componentNode) const;

    void display();

    b2Vec2 getPosition() const;
    void setPosition(const b2Vec2& position);

    float getAngle() const;
    void setAngle(float angle);

private:
    b2Vec2 position;
    float angle;
};