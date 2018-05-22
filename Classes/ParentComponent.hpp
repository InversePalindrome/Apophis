/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ParentComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <tinyxml2/tinyxml2.h>


class ParentComponent
{
public:
	explicit ParentComponent(const tinyxml2::XMLElement* componentNode);

	int getChildID() const;
	void setChildID(int childID);

private:
	int childID;
};