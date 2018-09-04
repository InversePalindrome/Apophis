/*
Copyright (c) 2018 Inverse Palindrome
Apophis - LevelSelectionNode.cpp
InversePalindrome.com
*/


#include "MenuNode.hpp"
#include "GameNode.hpp"
#include "LevelManager.hpp"
#include "LevelSelectionNode.hpp"

#include <cocos/ui/UIVBox.h>
#include <cocos/ui/UIHBox.h>
#include <cocos/2d/CCLabel.h>
#include <cocos/ui/UIButton.h>
#include <cocos/base/CCDirector.h>
#include <cocos/platform/CCFileUtils.h>

#include <pugixml.hpp>


LevelSelectionNode::~LevelSelectionNode()
{
	levelSelectionView->release();
}

bool LevelSelectionNode::init()
{
	if (!Node::init())
	{
		return false;
	}

	auto* director = cocos2d::Director::getInstance();
	const auto windowSize = director->getVisibleSize();
	
	auto* backButton = cocos2d::ui::Button::create("RegularRectangleButton", "SelectedRectangleButton", "", cocos2d::ui::Widget::TextureResType::PLIST);
	backButton->setPosition({ backButton->getContentSize().width / 2.f, windowSize.height - backButton->getContentSize().height / 2.f });
	backButton->addClickEventListener([director](auto* sender) { director->replaceScene(MenuNode::scene()); });

	auto* backLabel = cocos2d::Label::createWithTTF("back", "Zian.ttf", 60.f);
	backLabel->setTextColor(cocos2d::Color4B(135, 206, 250, 255));
	backLabel->setPosition(backButton->getContentSize().width / 2.f, backButton->getContentSize().height / 2.f);
	backButton->addChild(backLabel);
	
	levelSelectionView = cocos2d::ui::PageView::create();
	levelSelectionView->retain();
	levelSelectionView->setContentSize({ windowSize.width / 1.25f, windowSize.height / 1.25f });
	levelSelectionView->setPosition({ windowSize.width / 2.f - levelSelectionView->getContentSize().width / 2.f, 0.f });
	levelSelectionView->setClippingEnabled(false);
	levelSelectionView->setTouchEnabled(true);
	
	load("LevelSelection.xml");

	addChild(backButton);
	addChild(levelSelectionView);

	return true;
}

cocos2d::Scene* LevelSelectionNode::scene()
{
	auto* scene = cocos2d::Scene::create();
	scene->addChild(LevelSelectionNode::create());

	return scene;
}

void LevelSelectionNode::load(const std::string& filename)
{
	if (pugi::xml_document doc; doc.load_file(cocos2d::FileUtils::getInstance()->fullPathForFilename(filename).c_str()))
	{
		if (const auto selectionLayoutNode = doc.child("LevelSelection"))
		{
			for (const auto pageNode : selectionLayoutNode.children("Page"))
			{
				const auto windowSize = cocos2d::Director::getInstance()->getVisibleSize();

				auto* vBox = cocos2d::ui::VBox::create({ windowSize.width / 1.25f, windowSize.height / 1.25f });
				std::size_t levelIndex = 0u;
				
				const auto rowChildren = pageNode.children("Row");
				
				for (const auto rowNode : rowChildren)
				{
					auto* hBox = cocos2d::ui::HBox::create({ windowSize.width / 1.25f, windowSize.height / std::distance(rowChildren.begin(), rowChildren.end()) });
					
					if (const auto itemsAttribute = rowNode.attribute("items"))
					{
						for (int i = 0; i < itemsAttribute.as_int(); ++i)
						{
							auto* levelButton = cocos2d::ui::Button::create("RegularSquareButton", "SelectedSquareButton", "", cocos2d::ui::Widget::TextureResType::PLIST);
							levelButton->addClickEventListener([levelIndex](auto* sender) { cocos2d::Director::getInstance()->replaceScene(GameNode::scene(LevelManager::getInstance()[levelIndex])); });

							auto* indexLabel = cocos2d::Label::createWithTTF(std::to_string(levelIndex++), "BEBAS.ttf", 40.f);
							indexLabel->setTextColor(cocos2d::Color4B(135, 206, 250, 255));
							indexLabel->setPosition(levelButton->getContentSize().width / 2.f, levelButton->getContentSize().height / 2.f);
							levelButton->addChild(indexLabel);

							hBox->addChild(levelButton);
						}
					}

					vBox->addChild(hBox);
				}

				levelSelectionView->addPage(vBox);
			}
		}
	}
}