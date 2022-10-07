// Written by Jaidon van Herwaarden October 2022

#pragma once

#include <SFML/Graphics.hpp>

#include "GameConstants.hpp"
#include <JMath.h>

class Ball
{
public:
	void Initialize();
	void Update();

	const sf::CircleShape GetDrawable() const { return mCircleShape; }
	const JMath::Vector2 GetVelocity() const { return mVelocity; }

	void SetBallColour(sf::Color colour);
	void SetVelocity(sf::Vector2f velocity);

private:
	void CheckWallCollision();
	bool CheckRectCollision(const sf::FloatRect& globalBoundsRect, const sf::Vector2f& rectPosition) const;

	sf::CircleShape mCircleShape{ GameConstants::BallSize };

	float mSpeed = 10.0f; // per frame
	JMath::Vector2 mVelocity{ JMath::Vector2::RandomOnUnitCircle() * mSpeed };

	bool mIsStuckToPaddle{ true };
};