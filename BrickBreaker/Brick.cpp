// Written by Jaidon van Herwaarden October 2022

#include "Brick.hpp"

void Brick::Initialize()
{
}

void Brick::Update()
{
}

void Brick::Shutdown()
{
}

const sf::RectangleShape Brick::GetDrawable() const
{
	return mRectangleShape;
}

void Brick::SetColour(sf::Color colour)
{
	mRectangleShape.setFillColor(colour);
}

void Brick::SetPosition(float x, float y)
{
	mRectangleShape.setPosition(x, y);
}