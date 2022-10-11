// Written by Jaidon van Herwaarden October 2022

#pragma once

#include "GameState.hpp"

#include "GameCommon.hpp"
#include "GameSprite.hpp"
#include "GameButton.hpp"

class VictoryState : public GameState
{
public:
	VictoryState() = default;

	void Initialize() override;
	void Terminate() override;
	// deltaTime is measures in seconds.
	void Update(float deltaTime) override;
	void Render() override;

private:
	sf::SoundBuffer mVictorySoundBuffer{};
	sf::Sound mVictoryNoise{};
	GameSprite mVictorySprite{};
	GameButton mHeroButton{};
};