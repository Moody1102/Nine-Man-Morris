#include <sstream>
#include "MainMenu.h"
#include "Config.h"
#include <iostream>
#include "GameState.h"

MainMenu::MainMenu(GameDataRef data) :_data(data) 
{

}

void MainMenu::Init() {

	this->_data->assets.LoadTexture("Background", MAIN_MENU_BACKGROUND);
	this->_data->assets.LoadTexture("Title", MAIN_MENU_TITLE);
	this->_data->assets.LoadTexture("Player Button", MAIN_MENU_BUTTON_PLAYER);
	this->_data->assets.LoadTexture("AI Button", MAIN_MENU_BUTTON_AI);

	this->background.setTexture(this->_data->assets.GetTexture("Background"));
	this->title.setTexture(this->_data->assets.GetTexture("Title"));
	this->player_button.setTexture(this->_data->assets.GetTexture("Player Button"));
	this->AI_button.setTexture(this->_data->assets.GetTexture("AI Button"));

	this->player_button.setPosition((SCREEN_WIDTH / 2) - (this->player_button.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 1.5) - (this->player_button.getGlobalBounds().height /1.5));

	this->AI_button.setPosition((SCREEN_WIDTH / 2) - (this->AI_button.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 1.1) - (this->AI_button.getGlobalBounds().height / 1.1));

	this->title.setPosition((SCREEN_WIDTH / 2) - (this->title.getGlobalBounds().width / 2), (this->title.getGlobalBounds().height * .1));

}

void MainMenu::HandleInput() {
	
	sf::Event event;

	while (this->_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			this->_data->window.close();
		}

		if (this->_data->input.isSpriteClicked(this->player_button, sf::Mouse::Left, this->_data->window))
		{
			std::cout << "Go to Game vs Player" << std::endl;
			this->_data->machine.AddState(StateRef(new GameState(_data)), true);
		}

		if (this->_data->input.isSpriteClicked(this->AI_button, sf::Mouse::Left, this->_data->window))
		{
			std::cout << "Go to Game vs AI" << std::endl;
		}
	}
}

void MainMenu::Update(float dt)
{

}

void MainMenu::Draw(float dt)
{
	this->_data->window.clear();
	this->_data->window.draw(this->background);
	this->_data->window.draw(this->player_button);
	this->_data->window.draw(this->AI_button);
	this->_data->window.draw(this->title);

	this->_data->window.display();
}