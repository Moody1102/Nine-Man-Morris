#include "Game.h"
#include "MainMenu.h"

Game::Game(int width, int height, std::string title) {

	data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
	data->machine.AddState(StateRef(new MainMenu(this->data)));

	this->Run();
}

void Game::Run() {

	float newTime, frameTime, interpolation;

	float currentTime = this->clock.getElapsedTime().asSeconds();
	float accumulator = 0.0f;

	while (this->data->window.isOpen())
	{
		this->data->machine.ProcessState();
		newTime = this->clock.getElapsedTime().asSeconds();
		frameTime = newTime - currentTime;

		if (frameTime > 0.25f)
		{
			frameTime = 0.25f;
		}

		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator >= dt)
		{
			this->data->machine.GetActiveState()->HandleInput();
			this->data->machine.GetActiveState()->Update(dt);

			accumulator -= dt;
		}

		interpolation = accumulator / dt;
		this->data->machine.GetActiveState()->Draw(interpolation);

	}
}