// Written by Jaidon van Herwaarden October 2022

#include "Brick.hpp"
#include "Game.hpp"

void Brick::Initialize()
{
}

void Brick::Update()
{
}

void Brick::Render()
{
	Game::Get()->GetRenderWindow()->draw(mRectangleShape);
}

void Brick::Shutdown()
{
}

void Brick::SetColour(sf::Color colour)
{
	mRectangleShape.setFillColor(colour);
}

void Brick::SetPosition(float x, float y)
{
	mRectangleShape.setPosition(x, y);
}