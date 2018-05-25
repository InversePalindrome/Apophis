/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ImpulseComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <tinyxml2/tinyxml2.h>


class ImpulseComponent
{
public:
	explicit ImpulseComponent(const tinyxml2::XMLElement* componentNode);

	float getLinearImpulse() const;
	void setLinearImpulse(float linearImpulse);

	float getAngularImpulse() const;
	void setAngularImpulse(float angularImpulse);

private:
	float linearImpulse;
	float angularImpulse;
};