#include <sstream>
#include "GameOverW.h"
#include "Config.h"
#include "MainMenu.h"
#include <iostream>
#include "GameState.h"

GameOverW::GameOverW(GameDataRef data) :_data(data)
{

}

void GameOverW::Init() {

	this->_data->assets.LoadTexture("p2", P2_WIN_PATH);


	this->background1.setTexture(this->_data->assets.GetTexture("p2"));




}

void GameOverW::HandleInput() {

	sf::Event event;

	while (this->_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			this->_data->window.close();
		}
	}
}

void GameOverW::Update(float dt)
{
	if (this->clock.getElapsedTime().asSeconds() > 3) {
		this->_data->machine.AddState(StateRef(new MainMenu(_data)), true);
	}
}

void GameOverW::Draw(float dt)
{
	this->_data->window.clear();
	this->_data->window.draw(this->background1);
	this->_data->window.display();
}