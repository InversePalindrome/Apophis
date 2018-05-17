/*
Copyright (c) 2018 Inverse Palindrome
Apophis - StartNode.hpp
InversePalindrome.com
*/


#include "KeyboardManager.hpp"

#include <cocos/2d/CCNode.h>
#include <cocos/2d/CCScene.h>


class StartNode : public cocos2d::Node
{
public:
	~StartNode();

	virtual bool init() override;
	virtual void update(float dt) override;

	CREATE_FUNC(StartNode);

	static cocos2d::Scene* scene();

private:
	KeyboardManager* keyboardManager;
};