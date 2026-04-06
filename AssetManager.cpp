#include "AssetManager.h"

unordered_map<string, Texture> AssetManager::_textures;
unordered_map<string, SoundBuffer> AssetManager::_soundBuffers;
unordered_map<string, Font> AssetManager::_fonts;

Texture& AssetManager::GetTexture(string const& fileName)
{
	auto it = _textures.find(fileName);
	if (it != _textures.end())
		return it->second;
	Texture& texture = _textures[fileName];
	if (!texture.loadFromFile(fileName))
		cout << "Error load texture: " << fileName << endl;
	return texture;
}

SoundBuffer& AssetManager::GetSoundBuffer(string const& fileName)
{
	auto it = _soundBuffers.find(fileName);
	if (it != _soundBuffers.end())
		return it->second;
	SoundBuffer& soundBuf = _soundBuffers[fileName];
	if (!soundBuf.loadFromFile(fileName))
		cout << "Error load sound: " << fileName << endl;
	return soundBuf;
}

Font& AssetManager::GetFont(string const& fileName)
{
	auto it = _fonts.find(fileName);
	if (it != _fonts.end())
		return it->second;
	Font& font = _fonts[fileName];
	if (!font.openFromFile(fileName))
		cout << "Error load font: " << fileName << endl;
	return font;
}
