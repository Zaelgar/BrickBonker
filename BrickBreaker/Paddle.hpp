// Written by Jaidon van Herwaarden October 2022

#pragma once

#include <SFML/Graphics.hpp>

#include "GameConstants.hpp"

class Paddle
{
public:
	void Initialize();
	void Update();

	void SetColour(sf::Color colour);

	const sf::RectangleShape GetDrawable();

private:
	float yPosition = 650.f;
	sf::RectangleShape mRectangleShape{
		{GameConstants::PaddleWidth, GameConstants::PaddleHeight}
	};
};