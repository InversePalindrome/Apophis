/*
Copyright (c) 2018 Inverse Palindrome
Apophis - TransformComponent.cpp
InversePalindrome.com
*/


#include "TransformComponent.hpp"

#include <imgui.h>


TransformComponent::TransformComponent() :
	position(0.f, 0.f),
	angle(0.f)
{
}

void TransformComponent::load(const pugi::xml_node& componentNode)
{
	if (const auto xPositionAttribute = componentNode.attribute("x"))
	{
		position.x = xPositionAttribute.as_float();
	}
	if (const auto yPositionAttribute = componentNode.attribute("y"))
	{
		position.y = yPositionAttribute.as_float();
	}
	if (const auto angleAttribute = componentNode.attribute("angle"))
	{
		setAngle(angleAttribute.as_float());
	}
}

void TransformComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.set_name("Transform");

	componentNode.append_attribute("x") = getPosition().x;
	componentNode.append_attribute("y") = getPosition().y;
	componentNode.append_attribute("angle") = getAngle();
}

void TransformComponent::display()
{
	if (ImGui::TreeNode("Transform"))
	{
		ImGui::InputFloat2("Position(X, Y)", &position.x);
		ImGui::InputFloat("Angle", &angle);

		ImGui::TreePop();
	}
}

b2Vec2 TransformComponent::getPosition() const
{
	return position;
}

void TransformComponent::setPosition(const b2Vec2& position)
{
	this->position = position;
}

float TransformComponent::getAngle() const
{
	return angle;
}

void TransformComponent::setAngle(float angle)
{
	this->angle = angle;
}