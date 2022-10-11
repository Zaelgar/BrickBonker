// Written by Jaidon van Herwaarden October 2022

#include "Common.h"
#include "PlayState.hpp"
#include "Game.hpp"

void PlayState::Initialize()
{
	// Initialize music
	LOG("Initializing PlayState.");

	ASSERT(levelSong.openFromFile("resources\\level1song.wav"));
	levelSong.setVolume(30.f);
	levelSong.setLoop(true);
	levelSong.play();

	const GameConfig& gameConfig = Game::Get()->GetGameConfig();

	// Initialize Game Objects
	mPaddle.Initialize();
	mBall.Initialize();

	// Initialize walls
	mLeftWall.setFillColor(sf::Color::Blue);
	mLeftWall.setSize({ static_cast<float>(GameConstants::WallThickness), static_cast<float>(gameConfig.mWindowHeight) });
	mLeftWall.setPosition({ -(GameConstants::WallThickness / 2.f), 0.f });

	mTopWall.setFillColor(sf::Color::Blue);
	mTopWall.setSize({ static_cast<float>(gameConfig.mWindowWidth), static_cast<float>(GameConstants::WallThickness) });
	mTopWall.setPosition({ 0.f, -(GameConstants::WallThickness / 2.f) });

	mRightWall.setFillColor(sf::Color::Blue);
	mRightWall.setSize({ static_cast<float>(GameConstants::WallThickness), static_cast<float>(gameConfig.mWindowHeight) });
	mRightWall.setPosition({ gameConfig.mWindowWidth - (GameConstants::WallThickness / 2.f) }, 0.f);


	// Initialize brick layout
	// TODO2: Convert this to read in a CSV or JSON as a level? Makes Playstate more versatile
	int levelHeight = 5;
	int levelWidth = 10;
	mBricks.resize(levelHeight * levelWidth);
	mBricks.shrink_to_fit();
	float brickHeight = GameConstants::BrickHeight;
	float brickWidth = GameConstants::BrickWidth;
	float edgeOffset = 80.f;
	float offset = 13.3f;
	for (int y = 0; y < levelHeight; ++y)
	{
		for (int x = 0; x < levelWidth; ++x)
		{
			int i = x + y * levelWidth;
			mBricks[i].SetColour(sf::Color::Red);
			mBricks[i].SetPosition(edgeOffset + ((brickWidth + offset) * x), edgeOffset + ((brickHeight + offset) * y));
			mBricks[i].SetActive(true);
		}
	}

	// Initialize Pause Screen
	mPauseMenu.Initialize();
	mIsPaused = false;
}

void PlayState::Terminate()
{
	LOG("Terminating PlayState.");
	levelSong.stop();
}

void PlayState::Update(float deltaTime)
{
	auto game = Game::Get();

	if (mBall.CheckDeathCollision())
	{
		game->ChangeState("DefeatState");
	}

	if (Game::Get()->IsEscapeHitThisFrame(true))
	{
		mIsPaused = mIsPaused ? false : true;
	}

	if (!mIsPaused)
	{
		CheckCollisions();

		mPaddle.Update();
		mBall.Update();
	}
	else if (mPauseMenu.Update()) // Will return true if resume is pressed
	{
		mIsPaused = false;
	}
}

void PlayState::Render()
{
	auto renderWindow = Game::Get()->GetRenderWindow();

	// Draw Walls
	renderWindow->draw(mLeftWall);
	renderWindow->draw(mTopWall);
	renderWindow->draw(mRightWall);

	// Draw Bricks
	for (auto& brick : mBricks)
	{
		if (brick.IsActive())
		{
			brick.Render();
		}
	}

	// Draw other game objects
	mPaddle.Render();
	mBall.Render();

	// Only if paused, draw pause screen
	if (mIsPaused)
	{
		mPauseMenu.Render();
	}
}

void PlayState::CheckCollisions()
{
	CollisionType collisionType = mBall.CheckRectCollision(mPaddle.GetGlobalBounds());

	if (collisionType != CollisionType::None)
	{
		auto paddleToBall = mBall.GetPosition() - mPaddle.GetPosition();
		mBall.SetVelocity(paddleToBall);
	}

	for (auto& brick : mBricks)
	{
		if (brick.IsActive())
		{
			collisionType = mBall.CheckRectCollision(brick.GetGlobalBounds());

			if (collisionType == CollisionType::Left || collisionType == CollisionType::Right)
			{
				mBall.NegateXVelocity();
				brick.SetActive(false);
			}
			else if (collisionType == CollisionType::Top || collisionType == CollisionType::Bottom)
			{
				mBall.NegateYVelocity();
				brick.SetActive(false);
			}
		}
	}

	collisionType = mBall.CheckRectCollision(mLeftWall.getGlobalBounds());
	if (collisionType != CollisionType::None)
	{
		mBall.NegateXVelocity();
	}

	collisionType = mBall.CheckRectCollision(mRightWall.getGlobalBounds());
	if (collisionType != CollisionType::None)
	{
		mBall.NegateXVelocity();
	}

	collisionType = mBall.CheckRectCollision(mTopWall.getGlobalBounds());
	if (collisionType != CollisionType::None)
	{
		mBall.NegateYVelocity();
	}
}