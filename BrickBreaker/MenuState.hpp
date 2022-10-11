// Written by Jaidon van Herwaarden October 2022

#include "GameCommon.hpp"

#include "GameState.hpp"

#include "GameSprite.hpp"
#include "GameButton.hpp"

class MenuState : public GameState
{
public:
	MenuState() = default;

	void Initialize() override;
	void Terminate() override;
	// deltaTime is measures in seconds.
	void Update(float deltaTime) override;
	void Render() override;

private:

	// Music
	sf::Music titleSong{};

	// Title Banner
	GameSprite mLogo{};

	// Menu Buttone
	GameButton mPlayButton{};
	GameButton mQuitButton{};
};