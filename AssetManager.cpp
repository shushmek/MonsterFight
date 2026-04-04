#include "AssetManager.h"

//AssetManager* AssetManager::sInstance = nullptr;

//AssetManager::AssetManager()
//{
//	assert(sInstance == nullptr);
//		sInstance = this;
//}
//
//Texture& AssetManager::GetTexture(string const& fileName)
//{
//	auto& texMap = sInstance->mTexture;
//	auto pairFound = texMap.find(fileName);
//	if (pairFound != texMap.end())
//		return pairFound->second;
//	else 
//	{
//		auto& texture = texMap[fileName];
//		texture.loadFromFile(fileName);
//		return texture;
//	}
//
//}
//
//SoundBuffer& AssetManager::GetSoundBuffer(string const& fileName)
//{
//	auto& soundBufMap = sInstance->mSoundBuffer;
//	auto pairFound = soundBufMap.find(fileName);
//	if (pairFound != soundBufMap.end())
//		return pairFound->second;
//	else
//	{
//		auto& sBuffer = soundBufMap[fileName];
//		sBuffer.loadFromFile(fileName);
//		return sBuffer;
//	}
//}
//
//Font& AssetManager::GetFont(string const& fileName)
//{
//	auto& fontMap = sInstance->mFont;
//	auto pairFound = fontMap.find(fileName);
//	if (pairFound != fontMap.end())
//		return pairFound->second;
//	else
//	{
//		auto& font = fontMap[fileName];
//		font.openFromFile(fileName);
//		return font;
//	}
//}
