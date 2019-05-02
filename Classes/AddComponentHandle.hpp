/*
Copyright (c) 2018 Inverse Palindrome
Apophis - AddComponentHandle.hpp
InversePalindrome.com
*/


#pragma once

#include <entityx/Entity.h>


template<typename Component>
struct AddComponetHandle
{
    using type = entityx::ComponentHandle<Component>;
};