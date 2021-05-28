#include <sstream>
#include "GameOverB.h"
#include "Config.h"
#include "MainMenu.h"
#include <iostream>
#include "GameState.h"

GameOverB::GameOverB(GameDataRef data) :_data(data)
{

}

void GameOverB::Init() {

	this->_data->assets.LoadTexture("p1", P1_WIN_PATH);


	this->background1.setTexture(this->_data->assets.GetTexture("p1"));




}

void GameOverB::HandleInput() {

	sf::Event event;

	while (this->_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			this->_data->window.close();
		}
	}
}

void GameOverB::Update(float dt)
{
	if (this->clock.getElapsedTime().asSeconds() > 3) {
		this->_data->machine.AddState(StateRef(new MainMenu(_data)), true);
	}
}

void GameOverB::Draw(float dt)
{
	this->_data->window.clear();
	this->_data->window.draw(this->background1);
	this->_data->window.display();
}