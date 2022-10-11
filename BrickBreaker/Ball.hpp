// Written by Jaidon van Herwaarden October 2022

#pragma once

#include "GameCommon.hpp"

enum class CollisionType
{
	None
	, Left
	, Right
	, Top
	, Bottom
};

class Ball
{
public:
	void Initialize();
	void Update();
	void Render();

	const sf::CircleShape GetCircleShape() const { return mCircleShape; }
	const sf::Vector2f GetVelocity() const { return mVelocity; }
	const sf::Vector2f GetPosition() const { return mCircleShape.getPosition(); }

	void SetBallColour(sf::Color colour);
	void SetVelocity(sf::Vector2f velocity);

	void NegateXVelocity();
	void NegateYVelocity();

	CollisionType CheckRectCollision(const sf::FloatRect& globalBoundsRect);
	bool CheckDeathCollision();

private:

	sf::CircleShape mCircleShape{ GameConstants::BallSize };

	float mSpeed = 15.0f; // per frame (60 FPS)
	sf::Vector2f mVelocity{};

	bool mIsStuckToPaddle{ true };
};