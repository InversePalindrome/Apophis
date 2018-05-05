/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - StartScene.cpp
InversePalindrome.com
*/


#include "MenuScene.hpp"
#include "StartScene.hpp"

#include <cocos/2d/CCLabel.h>
#include <cocos/2d/CCSprite.h>
#include <cocos/base/CCDirector.h>
#include <cocos/2d/CCActionInterval.h>
#include <cocos/2d/CCParticleSystemQuad.h>


StartScene::~StartScene()
{
	keyboardManager->release();
}

bool StartScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	scheduleUpdate();

	keyboardManager = KeyboardManager::create();
	keyboardManager->retain();

	auto* director = cocos2d::Director::getInstance();
	const auto& windowSize = cocos2d::Director::getInstance()->getVisibleSize();

	auto* background = cocos2d::Sprite::create("SpaceBackground.png");
	background->setPosition(windowSize.width / 2.f, windowSize.height / 2.f);

	auto* backgroundEffect = cocos2d::ParticleSystemQuad::create("StartEffect.plist");
	backgroundEffect->setPosition(windowSize.width / 2.f, windowSize.height / 2.f);

	auto* titleLabel = cocos2d::Label::createWithTTF("jatrgg", "Zian.ttf", 200.f);
	titleLabel->enableOutline(cocos2d::Color4B(30.f, 144.f, 255.f, 255.f), 6);
    titleLabel->setTextColor(cocos2d::Color4B(135.f, 206.f, 250.f, 255.f));
	titleLabel->setPosition(windowSize.width / 2.f, windowSize.height / 2.f);
	titleLabel->runAction(cocos2d::RepeatForever::create(cocos2d::Sequence::createWithTwoActions(cocos2d::TintTo::create(2.f, 135.f, 206.f, 250.f), cocos2d::TintTo::create(2.f, 240.f, 248.f, 255.f))));

	auto* startLabel = cocos2d::Label::createWithTTF("press a key to continue", "Zian.ttf", 80.f);
	startLabel->setCascadeOpacityEnabled(true);
	startLabel->setTextColor(cocos2d::Color4B(135.f, 206.f, 250.f, 255.f));
	startLabel->setPosition(windowSize.width / 2.f, windowSize.height / 8.f);
	startLabel->runAction(cocos2d::RepeatForever::create(cocos2d::Sequence::createWithTwoActions(cocos2d::FadeOut::create(1.f), cocos2d::FadeIn::create(1.f))));

	addChild(keyboardManager);
	addChild(background);
	addChild(backgroundEffect);
	addChild(titleLabel);
	addChild(startLabel);

	return true;
}

void StartScene::update(float dt)
{
	if (keyboardManager->isKeyPressed())
	{
		cocos2d::Director::getInstance()->replaceScene(MenuScene::scene());
	}
}

cocos2d::Scene* StartScene::scene()
{
	auto* scene = cocos2d::Scene::create();
	scene->addChild(StartScene::create());

	return scene;
}