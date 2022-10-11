// Written by Jaidon van Herwaarden October 2022

#include "Ball.hpp"
#include "Game.hpp"

void Ball::Initialize()
{
	// TODO1: Have a real start position on the paddle. Click to release maybe?
	mCircleShape.setPosition({ 300.0f, 300.0f });

	auto center = mCircleShape.getLocalBounds();
	mCircleShape.setOrigin(center.width / 2.f, center.height / 2.f);

	// TODO2: Better math solution for this game...
	auto vel = JMath::Vector2::RandomOnUnitCircle() * mSpeed;

	mVelocity = { vel.x, vel.y };
}

void Ball::Update()
{
	// On click if stuck, should unstick.
	// Collision initiated by PlayState because it knows of all game objects.
	mCircleShape.move(mVelocity.x, mVelocity.y);
}

void Ball::Render()
{
	Game::Get()->GetRenderWindow()->draw(mCircleShape);
}

void Ball::SetBallColour(sf::Color colour)
{
	mCircleShape.setFillColor(colour);
}

void Ball::SetVelocity(sf::Vector2f velocity)
{
	// TODO2: Better math solution for this game...
	// Normalize and multiply by max Speed.
	float magnitude = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
	velocity.x /= magnitude;
	velocity.y /= magnitude;
	velocity.x *= mSpeed;
	velocity.y *= mSpeed;

	mVelocity = velocity;
}

bool Ball::CheckDeathCollision()
{
	auto windowHeight = Game::Get()->GetGameConfig().mWindowHeight;
	auto windowWidth = Game::Get()->GetGameConfig().mWindowWidth;
	auto position = mCircleShape.getPosition();
	auto bounds = mCircleShape.getLocalBounds();

	// Check if our ball has fully crossed the bottom side of the screen
	if (position.y >= (windowHeight + GameConstants::BallSize * 2.f)) // Bottom side
	{
		return true;
	}
	return false;
}

CollisionType Ball::CheckRectCollision(const sf::FloatRect& globalBoundsRect)
{
	// TODO1: Speed is a bit too high and sometimes collisions (velocity changes) look wonked.
	// Maybe start from previous position and nudge until collision happens?

	// TODO2: Ball collision should only crunch one brick per frame.
	// Otherwise it can continue it's motion while flipping velocity
	// multiple times a frame and it looks weird
	// This coupled with the solution above could make it look a lot better.
	const auto circlePosition = mCircleShape.getPosition();

	CollisionType result = CollisionType::None;

	float testX = circlePosition.x;
	float testY = circlePosition.y;

	if (circlePosition.x < globalBoundsRect.left)
	{
		testX = globalBoundsRect.left;
	}
	else if (circlePosition.x > globalBoundsRect.left + globalBoundsRect.width)
	{
		testX = globalBoundsRect.left + globalBoundsRect.width;
	}
	if (circlePosition.y < globalBoundsRect.top)
	{
		testY = globalBoundsRect.top;
	}
	else if (circlePosition.y > globalBoundsRect.top + globalBoundsRect.height)
	{
		testY = globalBoundsRect.top + globalBoundsRect.height;
	}

	if (testX < globalBoundsRect.left + globalBoundsRect.width
		&& testX > globalBoundsRect.left)
	{
		if (testY > globalBoundsRect.top + globalBoundsRect.height / 2.f)
			result = CollisionType::Bottom;
		else
			result = CollisionType::Top;
	}
	if (testY < globalBoundsRect.top + globalBoundsRect.height
		&& testY > globalBoundsRect.top)
	{
		if (testX > globalBoundsRect.left + globalBoundsRect.width / 2.f)
			result = CollisionType::Right;
		else
			result = CollisionType::Left;
	}

	float distanceX = circlePosition.x - testX;
	float distanceY = circlePosition.y - testY;
	float distance = sqrt((distanceX * distanceX) + (distanceY * distanceY));

	if (distance <= mCircleShape.getRadius())
	{
		return result;
	}
	return CollisionType::None;
}

void Ball::NegateXVelocity()
{
	mVelocity.x *= -1.f;
}

void Ball::NegateYVelocity()
{
	mVelocity.y *= -1.f;
}