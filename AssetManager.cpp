#include "AssetManager.h"

namespace Pong 
{
	void AssetManager::LoadTexture(std::string name, std::string path)
	{
		sf::Texture tex;

		if (tex.loadFromFile(path)) {
			this->_textures[name] = tex;
		}
	}

	sf::Texture& AssetManager::GetTexture(string name)
	{
		return this->_textures.at(name);
	}

	void AssetManager::loadFont(std::string name, std::string path)
	{
		sf::Font font;

		if (font.loadFromFile(path)) {
			this->_fonts[name] = font;
		}
	}

	sf::Font& AssetManager::GetFont(string name)
	{
		return this->_fonts.at(name);
	}

	void AssetManager::LoadSound(string name, string path)
	{
		sf::SoundBuffer buffer;

		if (buffer.loadFromFile(path)) {
			this->_sounds[name] = buffer;
		}
	}

	sf::SoundBuffer& AssetManager::GetBuffer(string name)
	{
		return this->_sounds.at(name);
	}

}
