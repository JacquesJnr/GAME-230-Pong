#pragma once
#include <map>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
using namespace std;

namespace Pong
{

	class AssetManager
	{
	public:

		AssetManager();
		~AssetManager() {}

		void LoadTexture(string name, string path);
		sf::Texture &GetTexture( string name );

		void loadFont(string name, string path);
		sf::Font &GetFont( string name );

		void LoadSound(string name, string path);
		sf::SoundBuffer& GetBuffer(string name);

	private:
		map<string, sf::Texture>  _textures;
		map<string, sf::Font>  _fonts;
		map<string, sf::SoundBuffer>_sounds;
	};

}


