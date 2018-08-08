/*
Copyright (c) 2018 Inverse Palindrome
Apophis - QueueComponent.cpp
InversePalindrome.com
*/


#include "QueueComponent.hpp"

#include <imgui.h>


QueueComponent::QueueComponent(const pugi::xml_node& componentNode) :
	queueAheadDistance(5.f),
	queueRadius(1.f),
	brakeFactor(0.8f),
	velocityShrinkFactor(0.3f)
{
	if (const auto queueAheadDistanceAttribute = componentNode.attribute("aheadDistance"))
	{
		setQueueAheadDistance(queueAheadDistanceAttribute.as_float());
	}
	if (const auto queueRadiusAttribute = componentNode.attribute("radius"))
	{
		setQueueRadius(queueRadiusAttribute.as_float());
	}
	if (const auto brakeFactorAttribute = componentNode.attribute("brakeFactor"))
	{
		setBrakeFactor(brakeFactorAttribute.as_float());
	}
	if (const auto velocityShrinkFactorAttribute = componentNode.attribute("velocityShrinkFactor"))
	{
       setVelocityShrinkFactor(velocityShrinkFactorAttribute.as_float());
	}
}

void QueueComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.set_name("Queue");

	componentNode.append_attribute("aheadDistance") = getQueueAheadDistance();
	componentNode.append_attribute("radius") = getQueueRadius();
	componentNode.append_attribute("brakeFactor") = getBrakeFactor();
	componentNode.append_attribute("velocityShrinkFactor") = getVelocityShrinkFactor();
}

void QueueComponent::display()
{
	if (ImGui::TreeNode("Queue"))
	{
		ImGui::InputFloat("Ahead Distance", &queueAheadDistance);
		ImGui::InputFloat("Radius", &queueRadius);
		ImGui::InputFloat("Brake Factor", &brakeFactor);
		ImGui::InputFloat("Velocity Shrink Factor", &velocityShrinkFactor);

		ImGui::TreePop();
	}
}

float QueueComponent::getQueueAheadDistance() const
{
	return queueAheadDistance;
}

void QueueComponent::setQueueAheadDistance(float queueAheadDistance)
{
	this->queueAheadDistance = queueAheadDistance;
}

float QueueComponent::getQueueRadius() const
{
	return queueRadius;
}

void QueueComponent::setQueueRadius(float queueRadius)
{
	this->queueRadius = queueRadius;
}

float QueueComponent::getBrakeFactor() const
{
	return brakeFactor;
}

void QueueComponent::setBrakeFactor(float brakeFactor)
{
	this->brakeFactor = brakeFactor;
}

float QueueComponent::getVelocityShrinkFactor() const
{
	return velocityShrinkFactor;
}

void QueueComponent::setVelocityShrinkFactor(float velocityShrinkFactor)
{
	this->velocityShrinkFactor = velocityShrinkFactor;
}