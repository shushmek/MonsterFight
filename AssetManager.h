#pragma once
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<iostream>
#include <unordered_map>

using namespace sf;
using namespace std;

class AssetManager
{
public: //функции для установки соответствующих типов данных 
	static Texture& GetTexture(string const& fileName); //для текстур
	static SoundBuffer& GetSoundBuffer(string const& fileName); //для звуковых буферов
	static Font& GetFont(string const& fileName); // для шрифтов
private:
	static unordered_map<string, Texture> _textures;
	static unordered_map<string, SoundBuffer> _soundBuffers;
	static unordered_map<string, Font> _fonts;
};
//раньше:
//Texture textur;
//texstur.loadFromFile("путь к файлу");
// может засорять память одной и той же текстурой

//теперь
//Texture textur = AssetManager::GetTexture("путь к файлу");
//загружается один раз; дальнейшие попытки использовать ту же текстуру возвращают уже загруженную 
