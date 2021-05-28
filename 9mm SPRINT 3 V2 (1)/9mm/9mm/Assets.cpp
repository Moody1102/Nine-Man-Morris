#include "Assets.h"

void Assets::LoadTexture(std::string name, std::string fileName) {

	sf::Texture tex;

	if (tex.loadFromFile(fileName)) {

		this->textures[name] = tex;
	}
}

	sf::Texture& Assets::GetTexture(std::string name) {
		return this->textures.at(name);
	}


	void Assets::LoadFont(std::string name, std::string fileName) {

		sf::Font font;

		if (font.loadFromFile(fileName)) {

			this->fonts[name] = font;
		}
	}

	sf::Font& Assets::GetFont(std::string name) {
		return this->fonts.at(name);
	}