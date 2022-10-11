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

	const sf::CircleShape GetDrawable() const { return mCircleShape; }
	const JMath::Vector2 GetVelocity() const { return mVelocity; }
	const JMath::Vector2 GetPosition() const;

	void SetBallColour(sf::Color colour);
	void SetVelocity(JMath::Vector2 velocity);

	void NegateXVelocity();
	void NegateYVelocity();

	CollisionType CheckRectCollision(const sf::FloatRect& globalBoundsRect);
	bool CheckDeathCollision();

private:

	sf::CircleShape mCircleShape{ GameConstants::BallSize };

	float mSpeed = 15.0f; // per frame
	JMath::Vector2 mVelocity{ JMath::Vector2::RandomOnUnitCircle() * mSpeed };

	bool mIsStuckToPaddle{ true };
};