/*
Copyright (c) 2018 Inverse Palindrome
Apophis - ObjectComponent.cpp
InversePalindrome.com
*/


#include "ObjectComponent.hpp"

#include <imgui.h>


ObjectComponent::ObjectComponent(const pugi::xml_node& componentNode) :
	objectType(ObjectType::_from_string(componentNode.text().as_string()))
{
}

void ObjectComponent::save(pugi::xml_node& componentNode) const
{
	componentNode.set_name("Object");

	componentNode.text().set(objectType._to_string());
}

void ObjectComponent::display()
{
	if (ImGui::TreeNode("Object"))
	{
		if (ImGui::BeginCombo("Type", objectType._to_string()))
		{
			for (const auto objectTypeValue : ObjectType::_values())
			{
				if (ImGui::Selectable(objectTypeValue._to_string()))
				{
					objectType = objectTypeValue;
				}
			}

			ImGui::EndCombo();
		}

		ImGui::TreePop();
	}
}

ObjectType ObjectComponent::getObjectType() const
{
	return objectType;
}

void ObjectComponent::setObjectType(ObjectType objectType)
{
	this->objectType = objectType;
}