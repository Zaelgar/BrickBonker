// Written by Jaidon van Herwaarden October 2022

#pragma once

#include <SFML/Graphics.hpp>
#include <JMath.h>

#include "GameConstants.hpp"

class Paddle
{
public:
	void Initialize();
	void Update();

	void SetColour(sf::Color colour);

	const sf::RectangleShape GetDrawable();
	const JMath::Vector2 GetPosition() const;

private:
	float yPosition = 650.f;
	sf::RectangleShape mRectangleShape{
		{GameConstants::PaddleWidth, GameConstants::PaddleHeight}
	};
};