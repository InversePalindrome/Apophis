/*
Copyright (c) 2018 Inverse Palindrome
Apophis - LevelEditorNode.hpp
InversePalindrome.com
*/


#pragma once

#include <cocos/2d/CCNode.h>
#include <cocos/2d/CCScene.h>


class LevelEditorNode : public cocos2d::Node
{
public:
	virtual bool init() override;

	CREATE_FUNC(LevelEditorNode);

	static cocos2d::Scene* scene();
};