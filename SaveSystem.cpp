#include "SaveSystem.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <unordered_map>

namespace
{
	// save.txt использует простой формат key=value, чтобы его можно было проверить вручную.
	// Эти вспомогательные функции читают одно значение и отклоняют некорректные числа.
	bool TryGetString(std::unordered_map<std::string, std::string> const& values, std::string const& key, std::string& out)
	{
		auto it = values.find(key);
		if (it == values.end())
			return false;
		out = it->second;
		return true;
	}

	bool TryGetInt(std::unordered_map<std::string, std::string> const& values, std::string const& key, int& out)
	{
		auto it = values.find(key);
		if (it == values.end())
			return false;

		try
		{
			size_t processed = 0;
			int value = std::stoi(it->second, &processed);
			if (processed != it->second.size())
				return false;
			out = value;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	bool TryGetFloat(std::unordered_map<std::string, std::string> const& values, std::string const& key, float& out)
	{
		auto it = values.find(key);
		if (it == values.end())
			return false;

		try
		{
			size_t processed = 0;
			float value = std::stof(it->second, &processed);
			if (processed != it->second.size())
				return false;
			out = value;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}
}

bool SaveSystem::Save(SaveData const& data, std::string const& filePath, std::string& error)
{
	try
	{
		// Создаем Data при первом сохранении; игрок не должен создавать папки вручную.
		std::filesystem::path path(filePath);
		if (!path.parent_path().empty())
			std::filesystem::create_directories(path.parent_path());

		std::ofstream file(filePath, std::ios::trunc);
		if (!file.is_open())
		{
			error = "Cannot open save file for writing.";
			return false;
		}

		// Текстовый формат выбран намеренно: его легко отлаживать и расширять для этого демо.
		file << "playerName=" << data.playerName << '\n';
		file << "level=" << data.level << '\n';
		file << "health=" << data.health << '\n';
		file << "maxHealth=" << data.maxHealth << '\n';
		file << "damage=" << data.damage << '\n';
		file << "armor=" << data.armor << '\n';
		file << "move=" << data.move << '\n';
		file << "maxMove=" << data.maxMove << '\n';
		file << "critChance=" << data.critChance << '\n';
		file << "critMod=" << data.critMod << '\n';
		file << "minBet=" << data.minBet << '\n';
		file << "maxBet=" << data.maxBet << '\n';
		file << "cash=" << data.cash << '\n';
		file << "weaponIndex=" << data.weaponIndex << '\n';
		file << "armorIndex=" << data.armorIndex << '\n';
		file << "saves=" << data.stats.saves << '\n';
		file << "loads=" << data.stats.loads << '\n';
		file << "hpDamageTaken=" << data.stats.hpDamageTaken << '\n';
		file << "hpHealed=" << data.stats.hpHealed << '\n';
		file << "hpChanges=" << data.stats.hpChanges << '\n';
		file << "minHealthSeen=" << data.stats.minHealthSeen << '\n';
		file << "maxHealthSeen=" << data.stats.maxHealthSeen << '\n';

		if (!file.good())
		{
			error = "Cannot finish writing save file.";
			return false;
		}

		error.clear();
		return true;
	}
	catch (std::exception const& ex)
	{
		error = ex.what();
		return false;
	}
}

bool SaveSystem::Load(SaveData& data, std::string const& filePath, std::string& error)
{
	// Отсутствующее сохранение — нормальный случай первого запуска, поэтому сообщаем об этом вместо сбоя.
	std::ifstream file(filePath);
	if (!file.is_open())
	{
		error = "Save file not found.";
		return false;
	}

	std::unordered_map<std::string, std::string> values;
	std::string line;
	while (std::getline(file, line))
	{
		if (line.empty())
			continue;

		size_t separator = line.find('=');
		if (separator == std::string::npos)
		{
			error = "Save file contains invalid line: " + line;
			return false;
		}

		values[line.substr(0, separator)] = line.substr(separator + 1);
	}

	// Сначала загружаем во временный объект. Если проверка не пройдет, текущая игра останется без изменений.
	SaveData loaded;
	if (!TryGetString(values, "playerName", loaded.playerName) ||
		!TryGetInt(values, "level", loaded.level) ||
		!TryGetInt(values, "health", loaded.health) ||
		!TryGetInt(values, "maxHealth", loaded.maxHealth) ||
		!TryGetInt(values, "damage", loaded.damage) ||
		!TryGetInt(values, "armor", loaded.armor) ||
		!TryGetInt(values, "move", loaded.move) ||
		!TryGetInt(values, "maxMove", loaded.maxMove) ||
		!TryGetInt(values, "critChance", loaded.critChance) ||
		!TryGetFloat(values, "critMod", loaded.critMod) ||
		!TryGetInt(values, "minBet", loaded.minBet) ||
		!TryGetInt(values, "maxBet", loaded.maxBet) ||
		!TryGetInt(values, "cash", loaded.cash) ||
		!TryGetInt(values, "weaponIndex", loaded.weaponIndex) ||
		!TryGetInt(values, "armorIndex", loaded.armorIndex) ||
		!TryGetInt(values, "saves", loaded.stats.saves) ||
		!TryGetInt(values, "loads", loaded.stats.loads) ||
		!TryGetInt(values, "hpDamageTaken", loaded.stats.hpDamageTaken) ||
		!TryGetInt(values, "hpHealed", loaded.stats.hpHealed) ||
		!TryGetInt(values, "hpChanges", loaded.stats.hpChanges) ||
		!TryGetInt(values, "minHealthSeen", loaded.stats.minHealthSeen) ||
		!TryGetInt(values, "maxHealthSeen", loaded.stats.maxHealthSeen))
	{
		error = "Save file is missing required fields or contains invalid values.";
		return false;
	}

	data = loaded;
	error.clear();
	return true;
}
