#pragma once
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<iostream>
#include <unordered_map>

using namespace sf;
using namespace std;

class AssetManager
{
public:
	static Texture& GetTexture(string const& fileName);
	static SoundBuffer& GetSoundBuffer(string const& fileName);
	static Font& GetFont(string const& fileName);
private:
	static unordered_map<string, Texture> mTextures;
	static unordered_map<string, SoundBuffer> mSoundBuffers;
	static unordered_map<string, Font> mFonts;
};
