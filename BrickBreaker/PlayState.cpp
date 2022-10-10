// Written by Jaidon van Herwaarden October 2022

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

	// Initialize Game Objects
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

	// Initialize Pause Screen
	mPlayButton.LoadTexture("resources\\play.png");
	mPlayButton.SetPosition({ 550.0f, 250.0f });
	mPlayButton.SetColour(sf::Color::Green);

	mQuitButton.LoadTexture("resources\\quit.png");
	mQuitButton.SetPosition({ 565.0f, 450.0f });
	mQuitButton.SetColour(sf::Color::Red);

	mPauseUnderlay.setSize({ static_cast<float>(Game::Get()->GetGameConfig().mWindowWidth)
		, static_cast<float>(Game::Get()->GetGameConfig().mWindowHeight) });
	mPauseUnderlay.setFillColor(mPauseColour);
}

void PlayState::Terminate()
{
	LOG("Terminating PlayState.");
	levelSong.stop();
}

void PlayState::Update(float deltaTime)
{
	auto game = Game::Get();

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
	else
	{
		auto mousePosition = sf::Mouse::getPosition(*game->GetRenderWindow());
		if (mPlayButton.Update(mousePosition))
		{
			mIsPaused = false;
		}
		else if (mQuitButton.Update(mousePosition))
		{
			mIsPaused = false;
			game->ChangeState("MenuState");
		}
	}
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

	if (mIsPaused)
	{
		renderWindow->draw(mPauseUnderlay);
		renderWindow->draw(mPlayButton.GetDrawable());
		renderWindow->draw(mQuitButton.GetDrawable());
	}
}

void PlayState::CheckCollisions()
{
	CollisionType collisionType = mBall.CheckRectCollision(mPaddle.GetDrawable().getGlobalBounds());

	if (collisionType != CollisionType::None)
	{
		JMath::Vector2 paddleToBall = mBall.GetPosition() - mPaddle.GetPosition();
		mBall.SetVelocity(paddleToBall);
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