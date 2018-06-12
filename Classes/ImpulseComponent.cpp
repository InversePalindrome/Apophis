/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ImpulseComponent.cpp
InversePalindrome.com
*/


#include "ImpulseComponent.hpp"


b2Vec2 ImpulseComponent::getLinearImpulse() const
{
	return linearImpulse;
}

void ImpulseComponent::setLinearImpulse(const b2Vec2& linearImpulse)
{
	this->linearImpulse = linearImpulse;
}

float ImpulseComponent::getAngularImpulse() const
{
	return angularImpulse;
}

void ImpulseComponent::setAngularImpulse(float angularImpulse)
{
	this->angularImpulse = angularImpulse;
}

void operator+=(entityx::ComponentHandle<ImpulseComponent> impulseComponent, const b2Vec2& linearImpulse)
{
	impulseComponent->setLinearImpulse(impulseComponent->getLinearImpulse() + linearImpulse);
}

void operator-=(entityx::ComponentHandle<ImpulseComponent> impulseComponent, const b2Vec2& linearImpulse)
{
	impulseComponent->setLinearImpulse(impulseComponent->getLinearImpulse() - linearImpulse);
}

void operator+=(entityx::ComponentHandle<ImpulseComponent> impulseComponent, float angularImpulse)
{
	impulseComponent->setAngularImpulse(impulseComponent->getAngularImpulse() + angularImpulse);
}

void operator-=(entityx::ComponentHandle<ImpulseComponent> impulseComponent, float angularImpulse)
{
	impulseComponent->setAngularImpulse(impulseComponent->getAngularImpulse() - angularImpulse);
}