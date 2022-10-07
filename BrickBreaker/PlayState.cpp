// Written by Jaidon van Herwaarden October 2022

#include "PlayState.hpp"

#include "Game.hpp"

void PlayState::Initialize()
{
	LOG("Initializing PlayState.");

	ASSERT(levelSong.openFromFile("resources\\level1song.wav"));
	levelSong.setVolume(30.f);
	levelSong.setLoop(true);
	levelSong.play();

	mPaddle.Initialize();
	mBall.Initialize();

	// Initialize brick layout
	// TODO1: Convert this to read in a CSV or JSON as a level? Makes Playstate more versatile
	int levelHeight = 5;
	int levelWidth = 10;
	mBricks.resize(levelHeight * levelWidth);
	mBricks.shrink_to_fit();
	float brickHeight = GameConstants::BrickHeight;
	float brickWidth = GameConstants::BrickWidth;
	float edgeOffset = 40.f;
	float offset = 22.2f;
	for (int y = 0; y < levelHeight; ++y)
	{
		for (int x = 0; x < levelWidth; ++x)
		{
			int i = x + y * levelWidth;
			mBricks[i].SetColour(sf::Color::Red);
			mBricks[i].SetPosition(edgeOffset + ((brickWidth + offset) * x), edgeOffset + ((brickHeight + offset)*y) );
		}
	}

	// When a ball hits the paddle on the right, left, or bottom, we turn on no clip for this many seconds.
	secondsToTime = sf::seconds(2.0f);
}

void PlayState::Terminate()
{
	LOG("Terminating PlayState.");
	levelSong.stop();
}

void PlayState::Update(float deltaTime)
{
	// Paddle side collision behaviour
	if (isNoClip)
	{
		currentElapsed += noClipTimer.getElapsedTime();
		if (currentElapsed >= secondsToTime)
		{
			isNoClip = false;
		}
	}

	auto game = Game::Get();

	CheckCollisions();

	mPaddle.Update();
	mBall.Update();
}

void PlayState::Render()
{
	auto renderWindow = Game::Get()->GetRenderWindow();

	for (auto& brick : mBricks)
	{
		if (brick.IsActive())
		{
			renderWindow->draw(brick.GetDrawable());
		}
	}

	renderWindow->draw(mPaddle.GetDrawable());
	renderWindow->draw(mBall.GetDrawable());
}

void PlayState::CheckCollisions()
{
	CollisionType collisionType = mBall.CheckRectCollision(mPaddle.GetDrawable().getGlobalBounds());

	if (collisionType == CollisionType::Top && isNoClip == false)
	{
		JMath::Vector2 paddleToBall = mBall.GetPosition() - mPaddle.GetPosition();
		mBall.SetVelocity(paddleToBall);
	}
	else if(collisionType != CollisionType::None)
	{
		isNoClip = true;
		noClipTimer.restart();
		currentElapsed = sf::seconds(0.f);
	}

	for (auto& brick : mBricks)
	{
		if (brick.IsActive())
		{
			collisionType = mBall.CheckRectCollision(brick.GetDrawable().getGlobalBounds());

			if (collisionType == CollisionType::Left || collisionType == CollisionType::Right)
			{
				auto vel = mBall.GetVelocity();
				vel.x *= -1.f;
				mBall.SetVelocity(vel);
				brick.SetActive(false);
			}
			else if (collisionType == CollisionType::Top || collisionType == CollisionType::Bottom)
			{
				auto vel = mBall.GetVelocity();
				vel.y *= -1.f;
				mBall.SetVelocity(vel);
				brick.SetActive(false);
			}
		}
	}
}