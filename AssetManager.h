#pragma once
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<iostream>
#include <unordered_map>

using namespace sf;
using namespace std;

class AssetManager
{
public: //функции для задания соответствующих типов даных 
	static Texture& GetTexture(string const& fileName); //для текстур
	static SoundBuffer& GetSoundBuffer(string const& fileName); //для буффуров звука
	static Font& GetFont(string const& fileName); // для шрифтов
private:
	static unordered_map<string, Texture> _textures;
	static unordered_map<string, SoundBuffer> _soundBuffers;
	static unordered_map<string, Font> _fonts;
};
//раньше:
//Texture textur;
//texstur.loadFromFile("путь к файлу");
// может засрать память одной и тойже текстурой

//сейчас
//Texture textur = AssetManager::GetTexture("путь к файлу");
//один раз загрузил, при осталальных попытках использовать ту же тексуру, даст уже загруженную 
