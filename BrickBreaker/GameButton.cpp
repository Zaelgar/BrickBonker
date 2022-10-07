// Written by Jaidon van Herwaarden October 2022

#include "GameButton.hpp"

GameButton::GameButton(std::string filePath, sf::Vector2<float> position)
{
	LoadTexture(filePath);
	mSprite.setPosition(position);
}

bool GameButton::Update(sf::Vector2<int> mousePosition)
{
	if (IsMouseOverButton(mousePosition))
	{
		mSprite.setColor(mHoverColourMultiplier);
		if (IsButtonPressed())
		{
			return true;
		}
		return false;
	}

	mSprite.setColor(sf::Color::White);

	return false;
}

void GameButton::SetPosition(sf::Vector2<float> position)
{
	mSprite.setPosition(position);
}

bool GameButton::IsMouseOverButton(sf::Vector2<int> mousePosition)
{
	auto bounds = mSprite.getGlobalBounds();

	if (bounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
	{
		return true;
	}
	return false;
}

bool GameButton::IsButtonPressed()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		return true;
	}

	return false;
}

void GameButton::LoadTexture(std::string filePath)
{
	if (mTexture.loadFromFile(filePath))
	{
		mSprite.setTexture(mTexture);
	}
}