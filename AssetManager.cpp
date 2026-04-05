#include "AssetManager.h"

unordered_map<string, Texture> AssetManager::mTextures;
unordered_map<string, SoundBuffer> AssetManager::mSoundBuffers;
unordered_map<string, Font> AssetManager::mFonts;

Texture& AssetManager::GetTexture(string const& fileName)
{
	auto it = mTextures.find(fileName);
	if (it != mTextures.end())
		return it->second;
	Texture& texture = mTextures[fileName];
	if (!texture.loadFromFile(fileName))
		cout << "Error load texture: " << fileName << endl;
	return texture;
}

SoundBuffer& AssetManager::GetSoundBuffer(string const& fileName)
{
	auto it = mSoundBuffers.find(fileName);
	if (it != mSoundBuffers.end())
		return it->second;
	SoundBuffer& soundBuf = mSoundBuffers[fileName];
	if (!soundBuf.loadFromFile(fileName))
		cout << "Error load sound: " << fileName << endl;
	return soundBuf;
}

Font& AssetManager::GetFont(string const& fileName)
{
	auto it = mFonts.find(fileName);
	if (it != mFonts.end())
		return it->second;
	Font& font = mFonts[fileName];
	if (!font.openFromFile(fileName))
		cout << "Error load font: " << fileName << endl;
	return font;
}
