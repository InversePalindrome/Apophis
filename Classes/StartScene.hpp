/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - StartScene.hpp
InversePalindrome.com
*/


#include "KeyboardManager.hpp"

#include <cocos/2d/CCLayer.h>
#include <cocos/2d/CCScene.h>


class StartScene : public cocos2d::Layer
{
public:
	~StartScene();

	virtual bool init() override;
	virtual void update(float dt) override;

	CREATE_FUNC(StartScene);

	static cocos2d::Scene* scene();

private:
	KeyboardManager* keyboardManager;
};