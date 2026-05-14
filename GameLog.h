#pragma once

#include <string>
#include <vector>

// Одна строка в постоянной таблице истории игр.
struct GameResult
{
	std::string playerName;
	int         level = 0;
	int         cash  = 0;
	bool        won   = false;
};

class GameLog
{
public:
	// Загружает сохраненные строки истории игр из Data/gameLog.txt.
	void LoadFromFile(std::string const& filePath);

	// Добавляет одну строку истории игр в формате: имя - уровень - деньги - WIN/LOSE.
	void AddGameResult(GameResult const& result, std::string const& filePath);

	// Сохраняет короткие события времени выполнения в памяти. Они полезны для отладочного вывода.
	void AddEvent(std::string const& message);

	// Возвращает последние N событий времени выполнения.
	std::vector<std::string> GetRecentEvents(size_t count) const;

	// Возвращает постоянные строки истории игр для экрана LOGS.
	std::vector<GameResult> const& GetHistory() const;

private:
	// события относятся только к текущему запуску; история загружается из файла и сохраняется в файл.
	std::vector<std::string> events;
	std::vector<GameResult>  history;

	static std::string ResultToLine(GameResult const& r);
	static bool        LineToResult(std::string const& line, GameResult& out);
};
