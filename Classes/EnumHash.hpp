/*
Copyright (c) 2018 Inverse Palindrome
Apophis - EnumHash.hpp
InversePalindrome.com
*/


#pragma once

#include <cstddef>


template<typename T>
struct EnumHash
{
    std::size_t operator()(T _enum) const
    {
        return static_cast<std::size_t>(_enum);
    }
};