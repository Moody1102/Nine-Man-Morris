#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

class MainMenu : public State
{
public:
	MainMenu(GameDataRef data);

	void Init();

	void HandleInput();
	void Update(float dt);
	void Draw(float dt);

private:
	GameDataRef _data;

	sf::Sprite background;
	sf::Sprite player_button;
	sf::Sprite AI_button;
	sf::Sprite title;
};
