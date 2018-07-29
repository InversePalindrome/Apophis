/*
Copyright (c) 2018 Inverse Palindrome
Apophis - LevelEditorNode.cpp
InversePalindrome.com
*/


#include "LevelEditorNode.hpp"


bool LevelEditorNode::init()
{
	if (!Node::init())
	{
		return false;
	}

	return true;
}

cocos2d::Scene* LevelEditorNode::scene()
{
	auto* scene = cocos2d::Scene::create();
	scene->addChild(LevelEditorNode::create());

	return scene;
}