#include "GameLog.h"

#include <filesystem>
#include <fstream>
#include <sstream>

// Преобразует результат игры в читаемую строку, которую позже также можно разобрать обратно.
std::string GameLog::ResultToLine(GameResult const& r)
{
	return r.playerName + " - " + std::to_string(r.level)
		+ " - " + std::to_string(r.cash)
		+ " - " + (r.won ? "WIN" : "LOSE");
}

// Разбирает одну строку: "имя - уровень - деньги - WIN/LOSE".
// Некорректные строки игнорируются LoadFromFile, а не ломают весь экран журнала.
bool GameLog::LineToResult(std::string const& line, GameResult& out)
{
	if (line.empty())
		return false;

	auto splitNext = [](std::string const& src, size_t from, char delim, std::string& token) -> size_t
	{
		size_t pos = src.find(delim, from);
		if (pos == std::string::npos)
			return std::string::npos;
		token = src.substr(from, pos - from);
		while (!token.empty() && token.back() == ' ')
			token.pop_back();
		return pos + 1;
	};

	auto ltrim = [](std::string& s)
	{
		size_t i = 0;
		while (i < s.size() && s[i] == ' ') ++i;
		if (i) s = s.substr(i);
	};

	std::string name, levelStr, cashStr, resultStr;

	size_t pos = splitNext(line, 0, '-', name);
	if (pos == std::string::npos) return false;
	ltrim(name);

	pos = splitNext(line, pos, '-', levelStr);
	if (pos == std::string::npos) return false;
	ltrim(levelStr);

	pos = splitNext(line, pos, '-', cashStr);
	if (pos == std::string::npos) return false;
	ltrim(cashStr);

	resultStr = line.substr(pos);
	ltrim(resultStr);
	while (!resultStr.empty() && (resultStr.back() == '\r' || resultStr.back() == ' '))
		resultStr.pop_back();

	if (name.empty()) return false;

	try
	{
		out.playerName = name;
		out.level      = std::stoi(levelStr);
		out.cash       = std::stoi(cashStr);
		out.won        = (resultStr == "WIN");
	}
	catch (...)
	{
		return false;
	}

	return true;
}

void GameLog::LoadFromFile(std::string const& filePath)
{
	// При первом запуске файл истории может еще отсутствовать.
	history.clear();
	std::ifstream file(filePath);
	if (!file.is_open())
		return;

	std::string line;
	while (std::getline(file, line))
	{
		GameResult r;
		if (LineToResult(line, r))
			history.push_back(r);
	}
}

void GameLog::AddGameResult(GameResult const& result, std::string const& filePath)
{
	history.push_back(result);

	try
	{
		// Автоматически создаем Data при записи первого результата игры.
		std::filesystem::create_directories(
			std::filesystem::path(filePath).parent_path());

		std::ofstream file(filePath, std::ios::app);
		if (file.is_open())
			file << ResultToLine(result) << '\n';
	}
	catch (...) {}
}

void GameLog::AddEvent(std::string const& message)
{
	events.push_back(message);
}

std::vector<std::string> GameLog::GetRecentEvents(size_t count) const
{
	if (events.size() <= count)
		return events;
	return std::vector<std::string>(events.end() - count, events.end());
}

std::vector<GameResult> const& GameLog::GetHistory() const
{
	return history;
}
