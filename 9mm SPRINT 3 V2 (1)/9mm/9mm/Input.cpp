#include "Input.h"

bool Input::isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(button))
	{
		sf::IntRect playButton(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);

		if (playButton.contains(sf::Mouse::getPosition(window)))
		{
			return true;
		}
	}

	return false;
}

sf::Vector2i Input::GetMousePosition(sf::RenderWindow& window)
{
	return sf::Mouse::getPosition(window);
}



