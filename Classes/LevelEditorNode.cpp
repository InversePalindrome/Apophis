/*
Copyright (c) 2018 Inverse Palindrome
Apophis - LevelEditorNode.cpp
InversePalindrome.com
*/


#include "ActionSystem.hpp"
#include "GraphicsSystem.hpp"
#include "LevelSerializer.hpp"
#include "LevelEditorNode.hpp"

#include "CCIMGUI.h"
#include "CCImGuiLayer.h"


LevelEditorNode::LevelEditorNode() :
	entityManager(eventManager),
	systemManager(entityManager, eventManager)
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

	auto* font = ImGui::GetIO().Fonts->AddFontFromFileTTF("Fonts/OpenSans-Regular.ttf", 40.f);

	CCIMGUI::getInstance()->addImGUI([font]()
	{
		ImGui::PushFont(font);

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open"))
				{

				}
				if (ImGui::MenuItem("Save"))
				{
					
				}

				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}

		ImGui::Begin("Entities");

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
	systemManager.add<ActionSystem>();

	eventManager.subscribe<entityx::EntityCreatedEvent>(*this);
	eventManager.subscribe<entityx::EntityDestroyedEvent>(*this);

	systemManager.configure();
}