/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ComponentParser.hpp
InversePalindrome.com
*/


#pragma once

#include "Components.hpp"

#include <entityx/Entity.h>

#include <functional>
#include <unordered_map>


extern const std::unordered_map<std::string, std::function<ComponentsVariant(entityx::Entity&)>> componentParser;