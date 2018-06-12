/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ImpulseComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <Box2D/Common/b2Math.h>

#include <entityx/Entity.h>


class ImpulseComponent
{
public:
	b2Vec2 getLinearImpulse() const;
	void setLinearImpulse(const b2Vec2& linearImpulse);

	float getAngularImpulse() const;
	void setAngularImpulse(float angularImpulse);

private:
	b2Vec2 linearImpulse{ 0.f, 0.f };
	float angularImpulse = 0.f;
};

void operator+=(entityx::ComponentHandle<ImpulseComponent> impulseComponent, const b2Vec2& linearImpulse);
void operator-=(entityx::ComponentHandle<ImpulseComponent> impulseComponent, const b2Vec2& linearImpulse);
void operator+=(entityx::ComponentHandle<ImpulseComponent> impulseComponent, float angularImpulse);
void operator-=(entityx::ComponentHandle<ImpulseComponent> impulseComponent, float angularImpulse);