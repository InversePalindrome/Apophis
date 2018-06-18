/*
Copyright (c) 2018 Inverse Palindrome
Apophis - Renderables.hpp
InversePalindrome.com
*/


#pragma once

#include "SpriteComponent.hpp"
#include "ParticleComponent.hpp"

#include <brigand/sequences/list.hpp>


using Renderables = brigand::list<SpriteComponent, ParticleComponent>;