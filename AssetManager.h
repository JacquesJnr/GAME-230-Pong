#pragma once
#include <map>
#include<SFML/Graphics.hpp>
using namespace std;

namespace Pong 
{
	class AssetManager
	{
	public:

		AssetManager() {}
		~AssetManager() {}

		void LoadTexture(std::string name, std::string fileName) {
			sf::Texture& GetTexture(std::string name);
		}

		void loadFont(std::string name, std::string fileName) {
			sf::Font& GetFont(std::string name);
		}

	private:
		map<string, sf::Texture>  _textures;
		map<string, sf::Font>  _fonts;
	};
}


