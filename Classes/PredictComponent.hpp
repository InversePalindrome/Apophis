/*
Copyright (c) 2018 Inverse Palindrome
JATR66 - PredictComponent.hpp
InversePalindrome.com
*/


#pragma once

#include <tinyxml2/tinyxml2.h>

#include <string>


template<typename T>
class PredictComponent
{
public:
	explicit PredictComponent(const tinyxml2::XMLElement* componentNode);

	float getPredictionTime() const;
	void setPredictionTime(float predictionTime);

private:
	float predictionTime;
};

template<typename T>
PredictComponent<T>::PredictComponent(const tinyxml2::XMLElement* componentNode) :
	predictionTime(5.f)
{
	if (const auto* predictionTime = componentNode->GetText())
	{
		this->predictionTime = std::stof(predictionTime);
	}
}

template<typename T>
float PredictComponent<T>::getPredictionTime() const
{
	return predictionTime;
}

template<typename T>
void PredictComponent<T>::setPredictionTime(float predictionTime)
{
	this->predictionTime = predictionTime;
}

using PursueComponent = PredictComponent<struct Pursue>;
using EvadeComponent = PredictComponent<struct Evade>;