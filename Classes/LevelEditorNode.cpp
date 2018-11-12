/*
Copyright (c) 2018 Inverse Palindrome
Apophis - LevelEditorNode.cpp
InversePalindrome.com
*/


#include "Constants.hpp"
#include "MenuScene.hpp"
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
	if (!PanZoomLayer::init())
	{
		return false;
	}

	schedule([this](auto dt)
	{ 
		systemManager.update_all(dt);
		SetPanBoundsRect({ mapDimensions.x * Constants::PTM_RATIO * -0.5f, mapDimensions.y * Constants::PTM_RATIO * -0.5f, mapDimensions.x * Constants::PTM_RATIO, mapDimensions.y * Constants::PTM_RATIO });
	}, 0.f, "update");

	initSystems();

	std::string currentAddComponent;
	
	CCIMGUI::getInstance()->addImGUI([this, currentAddComponent]() mutable
	{
		ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::MenuItem("Exit"))
			{
				cocos2d::Director::getInstance()->replaceScene(getMenuScene());
			}
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open"))
				{
					nfdchar_t* filename = nullptr;
					
					if (NFD_OpenDialog("xml", nullptr, &filename) == NFD_OKAY)
					{
						LevelParser::parseLevel(entities, mapDimensions, entityManager, eventManager, filename);
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

		if (ImGui::TreeNode("Entities"))
		{
			ImGui::SameLine();
			if (CCIMGUI::getInstance()->imageButton("#AddButton", 50, 50))
			{
				auto entity = entityManager.create();

				entities.emplace(std::to_string(entity.id().index()), entity);
			}
			ImGui::SameLine();
			if (ImGui::Button("Clear"))
			{
				entityManager.reset();
				entities.clear();
			}
			
			int i = 0;
			for (auto entityItr = std::begin(entities); entityItr != std::end(entities);)
			{
				ImGui::PushID(i++);
				
				bool isEntityOpen = ImGui::TreeNode(std::to_string(i).c_str(), entityItr->first.c_str());
				bool isEntityMarkedForRemoval = false;
				bool isEntityRenamed = false;

				ImGui::SameLine();
				if (ImGui::Button("Rename"))
				{
					entityName = entityItr->first;

					ImGui::OpenPopup("Name");
				}
				if (auto isOpen = true; ImGui::BeginPopupModal("Name", &isOpen, ImGuiWindowFlags_AlwaysAutoResize))
				{
					entityName.resize(64);
					
					ImGui::InputText("Name", entityName.data(), entityName.length());

					entityName.erase(std::find(std::begin(entityName), std::end(entityName), '\0'), std::end(entityName));
					
					if (ImGui::Button("Rename"))
					{
						isEntityRenamed = true;

						ImGui::CloseCurrentPopup();
					}

					ImGui::EndPopup();
				}

				ImGui::SameLine();
				if (ImGui::Button("Open"))
				{
					nfdchar_t* filename = nullptr;

					if (NFD_OpenDialog("xml", nullptr, &filename) == NFD_OKAY)
					{
						EntityParser::parseEntity(entityItr->second, eventManager, filename);
					}
				}
				ImGui::SameLine();
				if (ImGui::Button("Save"))
				{
					nfdchar_t* filename = nullptr;

					if (NFD_SaveDialog("xml", nullptr, &filename) == NFD_OKAY)
					{
						EntitySerializer::saveEntity(entityItr->second, filename);
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
							componentParser.at(currentAddComponent)(entityItr->second);
						}

						ImGui::CloseCurrentPopup();
					}

					ImGui::EndPopup();
				}

				if (isEntityOpen)
				{
					brigand::for_each<Components>([entityItr](auto componentElement) mutable
					{
						if (auto component = entityItr->second.component<decltype(componentElement)::type>())
						{
							component->display();
						}
					});

					ImGui::TreePop();
				}

				ImGui::PopID();

				if (isEntityMarkedForRemoval)
				{
					entityItr->second.destroy();
					entityItr = entities.erase(entityItr);
				}
				else if (isEntityRenamed && !entities.count(entityName))
				{
					auto renamedEntity = entities.extract(entityItr->first);
					renamedEntity.key() = entityName;
					entityItr = entities.insert(std::move(renamedEntity)).position;

					entityName.clear();
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

cocos2d::Scene* LevelEditorNode::scene()
{
	auto* scene = cocos2d::Scene::create();
	scene->addChild(LevelEditorNode::create());
	scene->addChild(ImGuiLayer::create());

	return scene;
}

void LevelEditorNode::initSystems()
{
	systemManager.add<GraphicsSystem>(this);
	systemManager.add<PhysicsSystem>(entityManager, eventManager);

	systemManager.configure();
}