/*
Copyright (c) 2018 Inverse Palindrome
Apophis - Renderables.hpp
InversePalindrome.com
*/


#pragma once

#include "LabelComponent.hpp"
#include "SpriteComponent.hpp"
#include "ParticleComponent.hpp"

#include <brigand/sequences/list.hpp>


using Renderables = brigand::list<SpriteComponent, LabelComponent, ParticleComponent>;