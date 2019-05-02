/*
Copyright (c) 2018 Inverse Palindrome
Apophis - Conversions.hpp
InversePalindrome.com
*/


#pragma once

#include <boost/math/constants/constants.hpp>


namespace Conversions
{
    template<typename T>
    T degreesToRadians(T degrees)
    {
        return degrees * boost::math::constants::pi<T>() / (T)180;
    }

    template<typename T>
    T radiansToDegrees(T radians)
    {
        return radians * (T)180 / boost::math::constants::pi<T>();
    }
}