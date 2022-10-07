// Written by Jaidon van Herwaarden October 2022

#include "Paddle.hpp"
#include "Game.hpp"

void Paddle::Initialize()
{
	SetColour(sf::Color::Yellow);

 	auto center = mRectangleShape.getGlobalBounds();
	mRectangleShape.setOrigin(center.width / 2.f, center.height / 2.f);
	center = mRectangleShape.getGlobalBounds();
 }

void Paddle::Update()
{
	auto window = Game::Get()->GetRenderWindow();

	sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window));
	auto bounds = mRectangleShape.getLocalBounds();

	// Check to see if the mouse position for X is between our min and max (screen size dependant)
	float windowWidth = static_cast<float>(Game::Get()->GetGameConfig().mWindowWidth);
	if (mousePosition.x < bounds.width/2.f)
	{
		mousePosition.x = bounds.width/2.f;
	}
	else if (mousePosition.x > (windowWidth - bounds.width/2.f))
	{
		mousePosition.x = windowWidth - bounds.width/2.f;
	}

	mRectangleShape.setPosition(mousePosition.x, yPosition);
}

void Paddle::SetColour(sf::Color colour)
{
	mRectangleShape.setFillColor(colour);
}

const sf::RectangleShape Paddle::GetDrawable()
{
	return mRectangleShape;
}

const JMath::Vector2 Paddle::GetPosition() const
{
	return { mRectangleShape.getPosition().x, mRectangleShape.getPosition().y };
}