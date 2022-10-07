// Written by Jaidon van Herwaarden October 2022

#include "Ball.hpp"
#include "Game.hpp"

void Ball::Initialize()
{
	mCircleShape.setPosition({ 300.0f, 300.0f });

	auto center = mCircleShape.getLocalBounds();
	mCircleShape.setOrigin(center.width / 2.f, center.height / 2.f);
}

void Ball::Update()
{
	// On click if stuck, should unstick.
	// Collision handled by PlayState because it knows of everyone.
	mCircleShape.move(mVelocity.x, mVelocity.y);
	CheckWallCollision();
}

const JMath::Vector2 Ball::GetPosition() const
{
	return { mCircleShape.getPosition().x, mCircleShape.getPosition().y };
}

void Ball::SetBallColour(sf::Color colour)
{
	mCircleShape.setFillColor(colour);
}

void Ball::SetVelocity(JMath::Vector2 velocity)
{
	mVelocity.x = velocity.x;
	mVelocity.y = velocity.y;
	mVelocity.Normalize();
	mVelocity *= mSpeed;
}

void Ball::CheckWallCollision()
{
	auto windowHeight = Game::Get()->GetGameConfig().mWindowHeight;
	auto windowWidth = Game::Get()->GetGameConfig().mWindowWidth;
	auto position = mCircleShape.getPosition();
	auto bounds = mCircleShape.getLocalBounds();

	// Check if our ball has touched or crossed either the left or right side of the screen
	if (position.x >= (windowWidth - (bounds.width / 2.f))) // Right side
	{
		mVelocity.x *= -1.f;
		// position properly from bounce
		mCircleShape.setPosition(windowWidth - (bounds.width / 2.f), position.y);
	}
	else if (position.x <= bounds.width / 2.f) // Left side
	{
		mVelocity.x *= -1.f;
		// position properly from bounce
		mCircleShape.setPosition(bounds.width / 2.f, position.y);
	}

	// Check if our ball has touched or crossed either the top or bottom side of the screen
	// TODO1: bottom kills you
	if (position.y >= (windowHeight - (bounds.height / 2.f))) // Bottom side
	{
		mVelocity.y *= -1.f;
		// position properly from bounce
		mCircleShape.setPosition(position.x, (windowHeight - (bounds.height / 2.f)));
	}
	else if (position.y <= bounds.height / 2.f) // Top side
	{
		mVelocity.y *= -1.f;
		// position properly from bounce
		mCircleShape.setPosition(position.x, (bounds.height / 2.f));
	}
}

CollisionType Ball::CheckRectCollision(const sf::FloatRect& globalBoundsRect)
{
	// Get point from center of ball to point on edge closest to rect.
	// if point intersects with rect, we collide. Good enough approximation?
	// TODO1 Better found here: https://www.jeffreythompson.org/collision-detection/circle-rect.php
	// This does not work if the ball is moving fast enough to go through the rect.

	const auto circlePosition = mCircleShape.getPosition();

	CollisionType result = CollisionType::None;

	float testX = circlePosition.x;
	float testY = circlePosition.y;

	if (circlePosition.x < globalBoundsRect.left)
	{
		testX = globalBoundsRect.left;
		result = CollisionType::Left;
	}
	else if (circlePosition.x > globalBoundsRect.left + globalBoundsRect.width)
	{
		testX = globalBoundsRect.left + globalBoundsRect.width;
		result = CollisionType::Right;
	}
	if (circlePosition.y < globalBoundsRect.top)
	{
		testY = globalBoundsRect.top;
		result = CollisionType::Top;
	}
	else if (circlePosition.y > globalBoundsRect.top + globalBoundsRect.height)
	{
		testY = globalBoundsRect.top + globalBoundsRect.height;
		result = CollisionType::Bottom;
	}

	float distanceX = circlePosition.x - testX;
	float distanceY = circlePosition.y - testY;
	float distance = sqrt((distanceX * distanceX) + (distanceY * distanceY));

	if (distance <= mCircleShape.getRadius())
	{
		//mCircleShape.move(-mVelocity.x, -mVelocity.y);
		return result;
	}
	return CollisionType::None;
}