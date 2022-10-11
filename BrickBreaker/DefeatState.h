// Written by Jaidon van Herwaarden October 2022

#pragma once

#include "GameState.hpp"

#include "GameCommon.hpp"
#include "GameSprite.hpp"
#include "GameButton.hpp"

class DefeatState : public GameState
{
public:
	DefeatState() = default;

	void Initialize() override;
	void Terminate() override;
	// deltaTime is measures in seconds.
	void Update(float deltaTime) override;
	void Render() override;

private:
	sf::SoundBuffer mDefeatSoundBuffer{};
	sf::Sound mDefeatNoise{};
	GameSprite mDefeatSprite{};
	GameButton mFailureButton{};
};