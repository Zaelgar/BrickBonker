#pragma once

#include "GameSprite.hpp"

class GameButton
{
public:
	GameButton() = default;
	GameButton(std::string filePath, sf::Vector2<float> position);

	bool Update(sf::Vector2<int> mousePosition);

	void LoadTexture(std::string filePath);
	void SetColour(sf::Color colour) { mHoverColourMultiplier = colour; }

	void SetPosition(sf::Vector2<float> position);

	const sf::Sprite& GetDrawable() { return mSprite; }

private:

	bool IsMouseOverButton(sf::Vector2<int> mousePosition);
	bool IsButtonPressed();

	sf::Texture mTexture;
	sf::Sprite mSprite;
	sf::Color mHoverColourMultiplier{ sf::Color::White };
};