/*
Copyright (c) 2018 Inverse Palindrome
Apophis - SettingsNode.cpp
InversePalindrome.com
*/


#include "AppSettings.hpp"
#include "SettingsNode.hpp"

#include <cocos/2d/CCLabel.h>
#include <cocos/2d/CCSprite.h>
#include <cocos/ui/UIButton.h>
#include <cocos/ui/UISlider.h>
#include <cocos/base/CCDirector.h>


SettingsNode::SettingsNode() :
	moveRight(KeyAction::MoveRight),
	moveLeft(KeyAction::MoveLeft),
	moveUp(KeyAction::MoveUp),
	moveDown(KeyAction::MoveDown)
{
}

SettingsNode::~SettingsNode()
{
	keyboardManager->release();
	controlButtons->release();
}

bool SettingsNode::init()
{
	if (!Node::init())
	{
		return false;
	}

	scheduleUpdate();

	keyboardManager = KeyboardManager::create();
	keyboardManager->retain();

	auto& appSettings = AppSettings::getInstance();

	auto* director = cocos2d::Director::getInstance();
	auto windowSize = director->getVisibleSize();

	auto* background = cocos2d::Sprite::create("SpaceBackground.png");
	background->setPosition(windowSize.width / 2.f, windowSize.height / 2.f);

	auto* backButton = cocos2d::ui::Button::create("RegularRectangleButton", "SelectedRectangleButton", "", cocos2d::ui::Widget::TextureResType::PLIST);
	backButton->setPosition({ backButton->getContentSize().width / 2.f, windowSize.height - backButton->getContentSize().height / 2.f });
	backButton->addClickEventListener([director](auto* sender) { director->popScene(); });

	auto* backLabel = cocos2d::Label::createWithTTF("back", "Zian.ttf", 60.f);
	backLabel->setTextColor(cocos2d::Color4B(135, 206, 250, 255));
	backLabel->setPosition(backButton->getContentSize().width / 2.f, backButton->getContentSize().height / 2.f);
	backButton->addChild(backLabel);

	auto* soundLabel = cocos2d::Label::createWithTTF("sound volume", "Zian.ttf", 60.f);
	soundLabel->setTextColor(cocos2d::Color4B(135, 206, 250, 255));
	soundLabel->setPosition({ windowSize.width / 3.2f, windowSize.height / 1.4f });

	auto* soundVolumeSlider = cocos2d::ui::Slider::create("Slider", "Scroller", cocos2d::ui::Widget::TextureResType::PLIST);
	soundVolumeSlider->setPosition({ windowSize.width / 1.5f, windowSize.height / 1.4f });
	soundVolumeSlider->setPercent(static_cast<int>(appSettings.getSoundVolume() * 100));
	soundVolumeSlider->addClickEventListener([soundVolumeSlider, &appSettings](auto* sender) { appSettings.setSoundVolume(soundVolumeSlider->getPercent() / 100.f); });

	auto* musicLabel = cocos2d::Label::createWithTTF("music volume", "Zian.ttf", 60.f);
	musicLabel->setTextColor(cocos2d::Color4B(135, 206, 250, 255));
	musicLabel->setPosition({ windowSize.width / 3.2f, windowSize.height / 1.8f });

	auto* musicVolumeSlider = cocos2d::ui::Slider::create("Slider", "Scroller", cocos2d::ui::Widget::TextureResType::PLIST);
	musicVolumeSlider->setPosition({ windowSize.width / 1.5f, windowSize.height / 1.8f });
	musicVolumeSlider->setPercent(static_cast<int>(appSettings.getMusicVolume() * 100));
	musicVolumeSlider->addClickEventListener([musicVolumeSlider, &appSettings](auto* sender) { appSettings.setMusicVolume(musicVolumeSlider->getPercent() / 100.f); });

	auto* moveRightLabel = cocos2d::Label::createWithTTF("move right", "Zian.ttf", 60.f);
	moveRightLabel->setTextColor(cocos2d::Color4B(135, 206, 250, 255));
	moveRightLabel->setPosition({ windowSize.width / 6.f, windowSize.height / 2.5f });

	auto* moveRightButton = cocos2d::ui::RadioButton::create();
	moveRightButton->setUserData(&moveRight);
	moveRightButton->setPosition({ windowSize.width / 6.f, windowSize.height / 3.f });
	moveRightButton->loadTextureBackGround("BlueRadioButtonOff", cocos2d::ui::Widget::TextureResType::PLIST);
	moveRightButton->loadTextureFrontCross("BlueRadioButtonOn", cocos2d::ui::Widget::TextureResType::PLIST);
	
	auto* moveLeftLabel = cocos2d::Label::createWithTTF("move left", "Zian.ttf", 60.f);
	moveLeftLabel->setTextColor(cocos2d::Color4B(135, 206, 250, 255));
	moveLeftLabel->setPosition({ windowSize.width / 2.5f, windowSize.height / 2.5f });

	auto* moveLeftButton = cocos2d::ui::RadioButton::create();
	moveLeftButton->setUserData(&moveLeft);
	moveLeftButton->setPosition({ windowSize.width / 2.5f, windowSize.height / 3.f });
	moveLeftButton->loadTextureBackGround("BlueRadioButtonOff", cocos2d::ui::Widget::TextureResType::PLIST);
	moveLeftButton->loadTextureFrontCross("BlueRadioButtonOn", cocos2d::ui::Widget::TextureResType::PLIST);

	auto* moveUpLabel = cocos2d::Label::createWithTTF("move up", "Zian.ttf", 60.f);
	moveUpLabel->setTextColor(cocos2d::Color4B(135, 206, 250, 255));
	moveUpLabel->setPosition({ windowSize.width / 1.65f, windowSize.height / 2.5f });

	auto* moveUpButton = cocos2d::ui::RadioButton::create();
	moveUpButton->setUserData(&moveUp);
	moveUpButton->setPosition({ windowSize.width / 1.65f, windowSize.height / 3.f });
	moveUpButton->loadTextureBackGround("BlueRadioButtonOff", cocos2d::ui::Widget::TextureResType::PLIST);
	moveUpButton->loadTextureFrontCross("BlueRadioButtonOn", cocos2d::ui::Widget::TextureResType::PLIST);

	auto* moveDownLabel = cocos2d::Label::createWithTTF("move down", "Zian.ttf", 60.f);
	moveDownLabel->setTextColor(cocos2d::Color4B(135, 206, 250, 255));
	moveDownLabel->setPosition({ windowSize.width / 1.25f, windowSize.height / 2.5f });

	auto* moveDownButton = cocos2d::ui::RadioButton::create();
	moveDownButton->setUserData(&moveDown);
	moveDownButton->setPosition({ windowSize.width / 1.25f, windowSize.height / 3.f });
	moveDownButton->loadTextureBackGround("BlueRadioButtonOff", cocos2d::ui::Widget::TextureResType::PLIST);
	moveDownButton->loadTextureFrontCross("BlueRadioButtonOn", cocos2d::ui::Widget::TextureResType::PLIST);
	
	controlButtons = cocos2d::ui::RadioButtonGroup::create();
	controlButtons->setAllowedNoSelection(true);
	controlButtons->retain();
	
	controlButtons->addRadioButton(moveRightButton);
	controlButtons->addRadioButton(moveLeftButton);
	controlButtons->addRadioButton(moveUpButton);
	controlButtons->addRadioButton(moveDownButton);

	addChild(keyboardManager);
	addChild(background);
	addChild(backButton);
	addChild(soundLabel);
	addChild(soundVolumeSlider);
	addChild(musicLabel);
	addChild(musicVolumeSlider);
	addChild(moveRightLabel);
	addChild(moveRightButton);
	addChild(moveLeftLabel);
	addChild(moveLeftButton);
	addChild(moveUpLabel);
	addChild(moveUpButton);
	addChild(moveDownLabel);
	addChild(moveDownButton);
	addChild(controlButtons);

	return true;
}

void SettingsNode::update(float dt)
{
	if (keyboardManager->isKeyPressed())
	{
		auto* selectedButton = controlButtons->getRadioButtonByIndex(controlButtons->getSelectedButtonIndex());

		auto keyAction = static_cast<KeyAction*>(selectedButton->getUserData());
		auto keyCode = keyboardManager->getActiveKeys().begin();

		AppSettings::getInstance().setKeyBinding(*keyAction, *keyCode);

		selectedButton->setSelected(false);
	}
}

cocos2d::Scene* SettingsNode::scene()
{
	auto* scene = cocos2d::Scene::create();
	scene->addChild(SettingsNode::create());

	return scene;
}