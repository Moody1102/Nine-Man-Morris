#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

class GameOverW : public State
{

public:
	GameOverW(GameDataRef data);

	void Init();

	void HandleInput();
	void Update(float dt);
	void Draw(float dt);

private:
	GameDataRef _data;

	sf::Sprite background1;
	sf::Sprite background2;
	sf::Clock clock;
};
