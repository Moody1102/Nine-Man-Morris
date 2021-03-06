#pragma once
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "StateMachine.h"
#include "Assets.h"
#include "Input.h"
#include "Anchor.h"

struct GameData
{
	StateMachine machine;
	sf::RenderWindow window;
	Assets assets;
	Input input;
};

typedef std::shared_ptr<GameData> GameDataRef;

class Game
{
public:
	Game(int width, int height, std::string title);

private:
	const float dt = 1.0f / 60.0f;
	sf::Clock clock;
	GameDataRef data = std::make_shared<GameData>();

	void Run();
};