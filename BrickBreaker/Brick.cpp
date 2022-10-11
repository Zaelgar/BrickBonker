// Written by Jaidon van Herwaarden October 2022

#include "Brick.hpp"
#include "Game.hpp"

void Alien::Initialize()
{
	mSprite.LoadTexture("resources\\alien.png");
}

void Alien::Update()
{
}

void Alien::Render()
{
	mSprite.Render();
}

void Alien::Shutdown()
{
}

void Alien::SetPosition(float x, float y)
{
	mSprite.GetSprite().setPosition(x, y);
}