#include "Anchor.h"

Anchor::Anchor(int id, sf::Vector2f position){

	this->id = id;
	setPosition(position);
}

void Anchor::fly(sf::Vector2f position) {

	setPosition(position);
}

void Anchor::setPosition(sf::Vector2f position)
{
	this->position = position;
}

int Anchor::getID() {
	return id;
}

int Anchor::getPositionX()
{
	return position.x;
}

int Anchor::getPositionY()
{
	return position.y;
}