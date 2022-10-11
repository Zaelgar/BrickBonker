// Written by Jaidon van Herwaarden October 2022

#include "GameButton.hpp"
#include "Game.hpp"

GameButton::GameButton(std::string filePath, sf::Vector2<float> position)
{
	LoadTexture(filePath);
	mSprite.setPosition(position);
}

// Update will return true if the button has been clicked.
bool GameButton::Update(sf::Vector2<int> mousePosition)
{
	// TODO2: don't pass in mouse position. Grab directly from Game
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

void GameButton::SetPosition(float yOrBoth, bool isXCentered)
{
	if (isXCentered)
	{
		const auto size = mTexture.getSize();
		auto& gameConfig = Game::Get()->GetGameConfig();

		// Assuming an origin of top left.
		mSprite.setPosition({ (gameConfig.mWindowWidth / 2.f) - (size.x / 2.f), yOrBoth });
		return;
	}
	mSprite.setPosition(yOrBoth, yOrBoth);
}