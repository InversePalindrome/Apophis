/*
Copyright (c) 2018 Inverse Palindrome
Apophis - LevelEditorNode.cpp
InversePalindrome.com
*/


#include "MenuNode.hpp"
#include "Components.hpp"
#include "LevelParser.hpp"
#include "EntityParser.hpp"
#include "PhysicsSystem.hpp"
#include "GraphicsSystem.hpp"
#include "LevelSerializer.hpp"
#include "LevelEditorNode.hpp"
#include "ComponentParser.hpp"
#include "EntitySerializer.hpp"

#include "CCIMGUI.h"
#include "CCImGuiLayer.h"

#include <nfd.h>

#include <brigand/algorithms/for_each.hpp>


LevelEditorNode::LevelEditorNode() :
	entityManager(eventManager),
	systemManager(entityManager, eventManager),
	mapDimensions(0.f, 0.f)
{
}

bool LevelEditorNode::init()
{
	if (!Node::init())
	{
		return false;
	}

	scheduleUpdate();
	initSystems();
	
	std::string currentAddComponent;
	
	CCIMGUI::getInstance()->addImGUI([this, currentAddComponent]() mutable
	{
		ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::MenuItem("Exit"))
			{
				cocos2d::Director::getInstance()->replaceScene(MenuNode::scene());
			}
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open"))
				{
					nfdchar_t* filename = nullptr;
					
					if (NFD_OpenDialog("xml", nullptr, &filename) == NFD_OKAY)
					{
						LevelParser::parseLevel(entityManager, eventManager, mapDimensions, filename);
					}
				}
				if (ImGui::MenuItem("Save"))
				{
					nfdchar_t* filename = nullptr;
					
					if (NFD_SaveDialog("xml", nullptr, &filename) == NFD_OKAY)
					{
						LevelSerializer::saveLevel(entities, mapDimensions, filename);
					}
				}

				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}

		ImGui::Begin("Level Data");

		auto isEntitiesOpen = ImGui::TreeNode("Entities");

		ImGui::SameLine();
		if (CCIMGUI::getInstance()->imageButton("#AddButton", 50, 50))
		{
			entityManager.create();
		}
		ImGui::SameLine();
		if (ImGui::Button("Clear"))
		{
			entityManager.reset();
		}
		if (isEntitiesOpen)
		{
			int i = 0;
			for (auto entityItr = std::begin(entities); entityItr != std::end(entities);)
			{
				ImGui::PushID(i++);

				bool isEntityOpen = ImGui::TreeNode(("Entity " + std::to_string(entityItr->id().index())).c_str());
				bool isEntityMarkedForRemoval = false;

				ImGui::SameLine();
				if (ImGui::Button("Open"))
				{
					nfdchar_t* filename = nullptr;

					if (NFD_OpenDialog("xml", nullptr, &filename) == NFD_OKAY)
					{
						EntityParser::parseEntity(*entityItr, eventManager, filename);
					}
				}
				ImGui::SameLine();
				if (ImGui::Button("Save"))
				{
					nfdchar_t* filename = nullptr;

					if (NFD_SaveDialog("xml", nullptr, &filename) == NFD_OKAY)
					{
						EntitySerializer::saveEntity(*entityItr, filename);
					}
				}
				ImGui::SameLine();		
				if (CCIMGUI::getInstance()->imageButton("#AddButton", 50, 50))
				{
					ImGui::OpenPopup("Add Component");
				}
				ImGui::SameLine();
				if (CCIMGUI::getInstance()->imageButton("#RemoveButton", 50, 50))
				{
					isEntityMarkedForRemoval = true;
				}

				if (auto isAddComponentOpen = true; ImGui::BeginPopupModal("Add Component", &isAddComponentOpen, ImGuiWindowFlags_AlwaysAutoResize))
				{
					if (ImGui::BeginCombo("Component", currentAddComponent.c_str()))
					{
						for (const auto& component : componentParser)
						{
							if (ImGui::Selectable(component.first.c_str()))
							{
								currentAddComponent = component.first;
							}
						}

						ImGui::EndCombo();
					}

					if (ImGui::Button("Add"))
					{
						if (componentParser.count(currentAddComponent))
						{
							componentParser.at(currentAddComponent)(*entityItr);
						}

						ImGui::CloseCurrentPopup();
					}

					ImGui::EndPopup();
				}

				if (isEntityOpen)
				{
					brigand::for_each<Components>([entityItr](auto componentElement) mutable
					{
						if (auto component = entityItr->component<decltype(componentElement)::type>())
						{
							component->display();
						}
					});

					ImGui::TreePop();
				}

				ImGui::PopID();

				if (isEntityMarkedForRemoval)
				{
					entityItr = entities.erase(entityItr);
				}
				else
				{
					++entityItr;
				}
			}
			
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Map"))
		{
			ImGui::InputFloat2("Dimensions(Width, Height)", &mapDimensions.x);

			ImGui::TreePop();
		}
		ImGui::End();

		ImGui::PopFont();
	}, "LevelEditor");

	return true;
}

void LevelEditorNode::update(float dt)
{
	systemManager.update_all(dt);
}

void LevelEditorNode::receive(const entityx::EntityCreatedEvent& event)
{
	entities.push_back(event.entity);
}

void LevelEditorNode::receive(const entityx::EntityDestroyedEvent& event)
{
	entities.erase(std::remove(std::begin(entities), std::end(entities), event.entity), std::end(entities));
}

cocos2d::Scene* LevelEditorNode::scene()
{
	auto* scene = cocos2d::Scene::create();
	scene->addChild(LevelEditorNode::create());
	scene->addChild(ImGuiLayer::create());

	return scene;
}

void LevelEditorNode::initSystems()
{
	systemManager.add<GraphicsSystem>(this, mapDimensions);
	systemManager.add<PhysicsSystem>(entityManager, eventManager);

	eventManager.subscribe<entityx::EntityCreatedEvent>(*this);
	eventManager.subscribe<entityx::EntityDestroyedEvent>(*this);

	systemManager.configure();
}