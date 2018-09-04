/*
Copyright (c) 2018 Inverse Palindrome
Apophis - LevelSelectionNode.hpp
InversePalindrome.com
*/


#pragma once

#include <cocos/2d/CCNode.h>
#include <cocos/2d/CCScene.h>
#include <cocos/ui/UIPageView.h>


class LevelSelectionNode : public cocos2d::Node
{
public:
	~LevelSelectionNode();

	virtual bool init() override;

	CREATE_FUNC(LevelSelectionNode);

	static cocos2d::Scene* scene();

private:
	cocos2d::ui::PageView* levelSelectionView;

	void load(const std::string& filename);
};