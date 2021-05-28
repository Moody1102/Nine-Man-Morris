#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Anchor {
private:
	int id = -1;
	sf::Vector2f position;
	Anchor *points[24];

public:

	Anchor(int id, sf::Vector2f position);
	void fly(sf::Vector2f position);
	void setPosition(sf::Vector2f position);
	int getPositionX();
	int getPositionY();
	int getID();

};