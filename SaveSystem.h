#pragma once

#include <string>
#include "SaveData.h"

class SaveSystem
{
public:
	static bool Save(SaveData const& data, std::string const& filePath, std::string& error);
	static bool Load(SaveData& data, std::string const& filePath, std::string& error);
};
