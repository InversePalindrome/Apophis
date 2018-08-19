/*
Copyright (c) 2018 Inverse Palindrome
Apophis - LabelComponent.cpp
InversePalindrome.com
*/


#include "LabelComponent.hpp"

#include <imgui.h>


LabelComponent::LabelComponent() :
	NodeComponent(cocos2d::Label::create()),
	label(static_cast<cocos2d::Label*>(getNode()))
{
} 

void LabelComponent::load(const pugi::xml_node& componentNode)
{
	setText(componentNode.text().as_string());

	if (const auto fontAttribute = componentNode.attribute("font"))
	{
		setFontName(fontAttribute.as_string());
	}
	if (const auto sizeAttribute = componentNode.attribute("size"))
	{
		setFontSize(sizeAttribute.as_float());
	}
	if (const auto HAlignmentAttribute = componentNode.attribute("HAlignment"))
	{
		setHorizontalAlignment(static_cast<cocos2d::TextHAlignment>(HAlignmentAttribute.as_int()));
	}
	if (const auto VAlignmentAttribute = componentNode.attribute("VAlignment"))
	{
		setVerticalAlignment(static_cast<cocos2d::TextVAlignment>(VAlignmentAttribute.as_int()));
	}
	if (const auto textRAttribute = componentNode.attribute("textR"),
		textGAttribute = componentNode.attribute("textG"),
		textBAttribute = componentNode.attribute("textB"),
		textAAttribute = componentNode.attribute("textA");
	    textRAttribute && textGAttribute && textBAttribute && textAAttribute)
	{
		setTextColor(cocos2d::Color4B(textRAttribute.as_uint(), textGAttribute.as_uint(), textBAttribute.as_uint(), textAAttribute.as_uint()));
	}
}
void LabelComponent::save(pugi::xml_node& componentNode) const
{
	NodeComponent::save(componentNode);

	componentNode.set_name("Label");

	componentNode.text().set(getText().c_str());
	componentNode.append_attribute("font") = getFontName().c_str();
	componentNode.append_attribute("size") = getFontSize();
	componentNode.append_attribute("HAlignment") = static_cast<int>(getHorizontalAlignment());
	componentNode.append_attribute("VAlignment") = static_cast<int>(getVerticalAlignment());
	componentNode.append_attribute("textR") = getTextColor().r;
	componentNode.append_attribute("textG") = getTextColor().g;
	componentNode.append_attribute("textB") = getTextColor().b;
	componentNode.append_attribute("textA") = getTextColor().a;
}

void LabelComponent::display()
{
	if (ImGui::TreeNode("Label"))
	{
		NodeComponent::display();

		auto text = getText();
		text.resize(64);

		if (ImGui::InputText("Text", text.data(), text.length()))
		{
			setText(text);
		}

		auto fontName = getFontName();
		fontName.resize(64);

		if (ImGui::InputText("Font Name", fontName.data(), fontName.length()))
		{
			setFontName(fontName);
		}
		if (auto fontSize = getFontSize(); ImGui::InputFloat("Font Size", &fontSize))
		{
			setFontSize(fontSize);
		}
		
		const char* horizontalAlignments[] = { "Left", "Center", "Right" };

		if (auto HAlignment = static_cast<int>(getHorizontalAlignment()); ImGui::Combo("Horizontal Alignment", &HAlignment, horizontalAlignments, 3))
		{
			setHorizontalAlignment(static_cast<cocos2d::TextHAlignment>(HAlignment));
		}

		const char* verticalAlignments[] = { "Top", "Center", "Bottom" };

		if (auto VAlignment = static_cast<int>(getVerticalAlignment()); ImGui::Combo("Vertical Alignment", &VAlignment, verticalAlignments, 3))
		{
			setVerticalAlignment(static_cast<cocos2d::TextVAlignment>(VAlignment));
		}

		if (auto textColor = cocos2d::Color4F(getTextColor()); ImGui::ColorEdit3("Text Color", &textColor.r))
		{
			setTextColor(cocos2d::Color4B(textColor));
		}

		ImGui::TreePop();
	}
}

std::string LabelComponent::getText() const
{
	return label->getString();
}

void LabelComponent::setText(const std::string& text)
{
	label->setString(text);
}

std::string LabelComponent::getFontName() const
{
	return label->getSystemFontName();
}

void LabelComponent::setFontName(const std::string& fontName)
{
	label->setSystemFontName(fontName);
}

float LabelComponent::getFontSize() const
{
	return label->getSystemFontSize();
}

void LabelComponent::setFontSize(float fontSize)
{
	label->setSystemFontSize(fontSize);
}

cocos2d::TextHAlignment LabelComponent::getHorizontalAlignment() const
{
	return label->getHorizontalAlignment();
}

void LabelComponent::setHorizontalAlignment(cocos2d::TextHAlignment horizontalAlignment)
{
	label->setHorizontalAlignment(horizontalAlignment);
}

cocos2d::TextVAlignment LabelComponent::getVerticalAlignment() const
{
	return label->getVerticalAlignment();
}

void LabelComponent::setVerticalAlignment(cocos2d::TextVAlignment verticalAlignment)
{
	label->setVerticalAlignment(verticalAlignment);
}

cocos2d::Color4B LabelComponent::getTextColor() const
{
	return label->getTextColor();
}

void LabelComponent::setTextColor(const cocos2d::Color4B& textColor)
{
	label->setTextColor(textColor);
}