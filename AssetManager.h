#pragma once
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<assert.h>
#include<map>

using namespace sf;
using namespace std;

class AssetManager
{
public:
	AssetManager() {};

	static Texture& GetTexture(string const& fileName);
	static SoundBuffer& GetSoundBuffer(string const& fileName);
	static Font& GetFont(string const& fileName);
};

