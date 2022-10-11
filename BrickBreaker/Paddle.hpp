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
	void Render();

	void SetColour(sf::Color colour);

	const sf::RectangleShape GetRectangle() { return mRectangleShape; }
	const sf::Vector2f GetPosition() const { return mRectangleShape.getPosition(); }
	const sf::FloatRect GetGlobalBounds() const { return mRectangleShape.getGlobalBounds(); }

private:
	float yPosition = 650.f;
	sf::RectangleShape mRectangleShape{
		{GameConstants::PaddleWidth, GameConstants::PaddleHeight}
	};
};