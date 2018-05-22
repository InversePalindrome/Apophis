/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ChildComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <tinyxml2/tinyxml2.h>


class ChildComponent
{
public:
	explicit ChildComponent(const tinyxml2::XMLElement* componentNode);

	int getParentID() const;
	void setParentID(int parentID);

private:
	int parentID;
};