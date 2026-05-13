#include "Engine.h"

#include <algorithm>
#include <optional>
#include <sstream>
#include <vector>

using namespace std;

namespace
{
	// Новые постоянные файлы хранятся в Data, чтобы прогресс игры не смешивался с исходными файлами.
	const string SavePath   = "Data/save.txt";
	const string GameLogPath = "Data/gameLog.txt";

	// Keyboard::isKeyPressed проверяется каждый кадр, поэтому это преобразует удержание клавиши в один щелчок.
	bool WasPressed(Keyboard::Key key, bool& wasDown)
	{
		bool isDown = Keyboard::isKeyPressed(key);
		bool pressed = isDown && !wasDown;
		wasDown = isDown;
		return pressed;
	}
}

void Engine::Input()
{
	while (const optional event = window->pollEvent())
	{
		if (event->is<Event::Closed>())
			window->close();

		// Кнопки игнорируют события, пока неактивны, поэтому сюда можно направлять все экранные кнопки.
		startBTN.handleEvent(*event, *window);
		menuLoadBTN.handleEvent(*event, *window);
		statBTN.handleEvent(*event, *window);
		logsBTN.handleEvent(*event, *window);
		exitBTN.handleEvent(*event, *window);
		toMenuBTN.handleEvent(*event, *window);
		saveBTN.handleEvent(*event, *window);
		gameLoadBTN.handleEvent(*event, *window);
	}

	HandleHotkeys();
}

Engine::Engine()
{
	StartCutscene.AnimSetLoop(false);
	StartCutscene.AnimSetOnFinished([this]() { SetState(State::Game); });
	StartCutscene.AnimStop();

	startBTN.setOnClick([this]() {
		LogEvent("Start cutscene launched.");
		StartCutscene._anim->play();
	});
	startBTN.setSpriteColor(Color(180, 86, 140));

	menuLoadBTN.setOnClick([this]() { LoadGame(); });
	menuLoadBTN.setSpriteColor(Color(180, 86, 140));

	statBTN.setOnClick([this]() { SetState(State::Statistic); });
	statBTN.setSpriteColor(Color(180, 86, 140));

	logsBTN.setOnClick([this]() { SetState(State::Logs); });
	logsBTN.setSpriteColor(Color(180, 86, 140));

	exitBTN.setSpriteColor(Color(222, 32, 32));
	exitBTN.setOnClick([this] {
		LogEvent("Game closed from menu.");
		window->close();
	});


	toMenuBTN.setOnClick([this]() { SetState(State::Menu); });
	toMenuBTN.setSpriteColor(Color(222, 32, 32));
	toMenuBTN.setSize(0.6f, 0.6f);

	saveBTN.setOnClick([this]() { SaveGame(); });
	saveBTN.setSpriteColor(Color(180, 86, 140));
	saveBTN.setSize(0.6f, 0.6f);

	gameLoadBTN.setOnClick([this]() { LoadGame(); });
	gameLoadBTN.setSpriteColor(Color(180, 86, 140));
	gameLoadBTN.setSize(0.6f, 0.6f);

	hpBar.setScale({ 0.6f, 1.f });
	hpBar.setColor(Color(200, 0, 0));
	hpBar.setSliderNum(static_cast<float>(mob.getHealth()) / mob.getMaxHealth());

	mob.AnimStop();
	mob.setPosition({ 200,300 });

	stats.StartSession(mob.getHealth());
	LogEvent("Game started.");

	// Загружаем постоянные строки истории игр для экрана LOGS.
	logger.LoadFromFile(GameLogPath);
}

void Engine::Run()
{
	cout << "is start" << endl;
	Clock clock;
	while (window->isOpen())
	{
		Time dt = clock.restart();
		Input();
		Update(dt);
		Draw();
	}
}

void Engine::Update(Time const& deltaTime)
{
	menuBackground.AnimUpdate(deltaTime);
	StartCutscene.AnimUpdate(deltaTime);
	gameBackground.AnimUpdate(deltaTime);
	mob.AnimUpdate(deltaTime);
}

void Engine::Draw()
{
	window->clear();
	switch (state)
	{
	case State::Menu:
		BTNOff();
		startBTN.setActive(true);
		menuLoadBTN.setActive(true);
		statBTN.setActive(true);
		logsBTN.setActive(true);
		exitBTN.setActive(true);

		menuBackground.draw(*window);
		startBTN.draw(*window);
		menuLoadBTN.draw(*window);
		statBTN.draw(*window);
		logsBTN.draw(*window);
		exitBTN.draw(*window);
		if (StartCutscene.AnimGetPlay())
			StartCutscene.draw(*window);
		break;
	case State::Game:
		BTNOff();
		mob.AnimPlay();
		toMenuBTN.setActive(true);
		saveBTN.setActive(true);
		gameLoadBTN.setActive(true);

		gameBackground.draw(*window);
		mob.draw(*window);
		hpBar.draw(*window);
		toMenuBTN.draw(*window);
		saveBTN.draw(*window);
		gameLoadBTN.draw(*window);
		break;
	case State::Statistic:
		BTNOff();
		toMenuBTN.setActive(true);
		DrawStatistics();
		break;
	case State::Logs:
		BTNOff();
		toMenuBTN.setActive(true);
		DrawLogs();
		break;
	default:
		SetState(State::Menu);
		break;
	}
	window->display();
}

void Engine::BTNOff()
{
	startBTN.setActive(false);
	menuLoadBTN.setActive(false);
	statBTN.setActive(false);
	logsBTN.setActive(false);
	exitBTN.setActive(false);
	toMenuBTN.setActive(false);
	saveBTN.setActive(false);
	gameLoadBTN.setActive(false);
	hpBar.setActive(false);
}

void Engine::HandleHotkeys()
{
	if (state == State::Game)
	{
		// Управление в демо: W лечит на 1 HP, S наносит 1 урон.
		if (WasPressed(Keyboard::Key::W, keyWDown))
			ChangeHealth(1);
		if (WasPressed(Keyboard::Key::S, keySDown))
			ChangeHealth(-1);
	}
	else
	{
		WasPressed(Keyboard::Key::W, keyWDown);
		WasPressed(Keyboard::Key::S, keySDown);
	}

	if (WasPressed(Keyboard::Key::F3, keyF3Down))
		SetState(State::Statistic);
	if (WasPressed(Keyboard::Key::F4, keyF4Down))
		SetState(State::Logs);
	if (WasPressed(Keyboard::Key::F5, keyF5Down))
		SaveGame();
	if (WasPressed(Keyboard::Key::F9, keyF9Down))
		LoadGame();
	if (WasPressed(Keyboard::Key::Escape, keyEscDown) && state != State::Menu)
		SetState(State::Menu);
}

void Engine::ChangeHealth(int delta)
{
	// Держим HP, шкалу HP, статистику и журналы событий синхронизированными в одном месте.
	int oldHealth = mob.getHealth();
	int newHealth = std::clamp(oldHealth + delta, 0, mob.getMaxHealth());

	if (oldHealth == newHealth)
		return;

	mob.setHealth(newHealth);
	hpBar.setSliderNum(static_cast<float>(mob.getHealth()) / mob.getMaxHealth());
	stats.RecordHealthChange(oldHealth, newHealth);

	ostringstream stream;
	stream << "HP changed: " << oldHealth << " -> " << newHealth << ".";
	LogEvent(stream.str());
}

void Engine::SetState(State nextState)
{
	if (state == nextState)
		return;

	state = nextState;
	switch (state)
	{
	case State::Menu:
		LogEvent("Screen changed: Menu.");
		break;
	case State::Game:
		LogEvent("Screen changed: Game.");
		break;
	case State::Statistic:
		LogEvent("Screen changed: Statistics.");
		break;
	case State::Logs:
		LogEvent("Screen changed: Logs.");
		break;
	default:
		break;
	}
}

void Engine::SaveGame()
{
	// Засчитываем сохранение только после успешной записи снимка на диск.
	SaveData data = MakeSaveData();
	data.stats.saves++;

	string error;
	if (SaveSystem::Save(data, SavePath, error))
	{
		stats = data.stats;
		LogEvent("Game saved to " + SavePath + ".");

		// В демо пока нет настоящего условия победы, поэтому ручные сохранения записываются как LOSE.
		// Когда появится победа в бою, задавайте r.won из фактического результата битвы.
		GameResult r;
		r.playerName = mob.getName();
		r.level      = mob.getLevel();
		r.cash       = mob.getCash();
		r.won        = false;
		logger.AddGameResult(r, GameLogPath);
	}
	else
	{
		LogEvent("Save failed: " + error);
	}
}

void Engine::LoadGame()
{
	// Файл сохранения проверяется перед применением, поэтому поврежденное сохранение не портит игру.
	SaveData data;
	string error;
	if (!SaveSystem::Load(data, SavePath, error))
	{
		LogEvent("Load failed: " + error);
		return;
	}

	if (!ApplySaveData(data, error))
	{
		LogEvent("Load failed: " + error);
		return;
	}

	stats.loads++;
	stats.TrackHealth(mob.getHealth());
	LogEvent("Game loaded from " + SavePath + ".");

	// Обновляем историю на случай, если Data/gameLog.txt был изменен вне игры.
	logger.LoadFromFile(GameLogPath);
}

SaveData Engine::MakeSaveData()
{
	// Сохраняем в снимке только значения, которые текущие демо-классы могут безопасно восстановить.
	SaveData data;
	data.playerName = mob.getName();
	data.level = mob.getLevel();
	data.health = mob.getHealth();
	data.maxHealth = mob.getMaxHealth();
	data.damage = mob.getDamage();
	data.armor = mob.getArm();
	data.move = mob.getMove();
	data.maxMove = mob.getMaxMove();
	data.critChance = mob.getCritChance();
	data.critMod = mob.getCritMod();
	data.minBet = mob.getMinBet();
	data.maxBet = mob.getMaxBet();
	data.cash = mob.getCash();
	data.weaponIndex = currentWeaponIndex;
	data.armorIndex = currentArmorIndex;
	data.stats = stats;
	return data;
}

bool Engine::ApplySaveData(SaveData const& data, string& error)
{
	// Защищаемся от вручную измененных или частично записанных файлов сохранения.
	if (data.maxHealth <= 0)
	{
		error = "Saved max health must be greater than zero.";
		return false;
	}
	if (data.health < 0 || data.health > data.maxHealth)
	{
		error = "Saved health is outside valid range.";
		return false;
	}
	if (data.weaponIndex < 0 || data.weaponIndex >= ItemList::WeaponCount)
	{
		error = "Saved weapon index is invalid.";
		return false;
	}
	if (data.armorIndex < 0 || data.armorIndex >= ItemList::ArmorCount)
	{
		error = "Saved armor index is invalid.";
		return false;
	}
	if (data.minBet > data.maxBet)
	{
		error = "Saved min bet is greater than max bet.";
		return false;
	}

	mob.setName(data.playerName);
	mob.setLevel(data.level);
	mob.setMaxHealth(data.maxHealth);
	mob.setHealth(data.health);
	mob.setDamage(data.damage);
	mob.setArm(data.armor);
	mob.setMove(data.move);
	mob.setMaxMove(data.maxMove);
	mob.setCritChance(data.critChance);
	mob.setCritMod(data.critMod);
	mob.setMinBet(data.minBet);
	mob.setMaxBet(data.maxBet);
	mob.setCash(data.cash);
	mob.setWeapon(items.weapons[data.weaponIndex]);
	mob.setArmor(items.armors[data.armorIndex]);
	mob.setPosition({ 200,300 });

	currentWeaponIndex = data.weaponIndex;
	currentArmorIndex = data.armorIndex;
	stats = data.stats;
	stats.TrackHealth(data.health);
	hpBar.setSliderNum(static_cast<float>(mob.getHealth()) / mob.getMaxHealth());

	error.clear();
	return true;
}

void Engine::DrawStatistics()
{
	// Повторно используем существующий фон меню; темная панель нужна только для читаемости текста.
	menuBackground.draw(*window);
	toMenuBTN.draw(*window);

	RectangleShape panel({ 780.f, 520.f });
	panel.setPosition({ 380.f, 100.f });
	panel.setFillColor(Color(0, 0, 0, 160));
	window->draw(panel);

	DrawText("STATISTICS", { 420.f, 125.f }, 42);

	vector<string> lines = {
		"PLAYER",
		"Name: " + mob.getName(),
		"Level: " + to_string(mob.getLevel()),
		"HP: " + to_string(mob.getHealth()) + " / " + to_string(mob.getMaxHealth()),
		"Damage: " + to_string(mob.getDamage()),
		"Armor: " + to_string(mob.getArm()),
		"Move: " + to_string(mob.getMove()) + " / " + to_string(mob.getMaxMove()),
		"Cash: " + to_string(mob.getCash()),
		"Bet: " + to_string(mob.getMinBet()) + " - " + to_string(mob.getMaxBet()),
		"",
		"SESSION",
		"Saves: " + to_string(stats.saves),
		"Loads: " + to_string(stats.loads),
		"HP changes: " + to_string(stats.hpChanges),
		"Damage taken: " + to_string(stats.hpDamageTaken),
		"HP healed: " + to_string(stats.hpHealed),
		"Min HP seen: " + to_string(stats.minHealthSeen),
		"Max HP seen: " + to_string(stats.maxHealthSeen)
	};

	float y = 190.f;
	for (string const& line : lines)
	{
		if (line.empty())
		{
			y += 18.f;
			continue;
		}

		DrawText(line, { 420.f, y }, 24);
		y += 28.f;
	}
}

void Engine::DrawLogs()
{
	// LOGS показывает постоянную таблицу истории из Data/gameLog.txt.
	menuBackground.draw(*window);
	toMenuBTN.draw(*window);

	RectangleShape panel({ 890.f, 520.f });
	panel.setPosition({ 320.f, 100.f });
	panel.setFillColor(Color(0, 0, 0, 160));
	window->draw(panel);

	DrawText("GAME LOG", { 360.f, 125.f }, 42);

	// Заголовок таблицы истории.
	DrawText("Player            Lvl    Cash   Result", { 360.f, 180.f }, 20, Color(200, 200, 200));

	vector<GameResult> const& history = logger.GetHistory();
	if (history.empty())
	{
		DrawText("No game records yet.", { 360.f, 220.f }, 24);
		return;
	}

	// Показываем только последние 14 строк, чтобы текст оставался внутри панели.
	size_t startIdx = history.size() > 14 ? history.size() - 14 : 0;

	float y = 210.f;
	for (size_t i = startIdx; i < history.size(); ++i)
	{
		GameResult const& r = history[i];

		// Сохраняем строку на экране в том же формате, что и файл журнала.
		string line = r.playerName
			+ " - " + to_string(r.level)
			+ " - " + to_string(r.cash)
			+ " - " + (r.won ? "WIN" : "LOSE");

		Color c = r.won ? Color(100, 255, 100) : Color(255, 100, 100);
		DrawText(line, { 360.f, y }, 20, c);
		y += 26.f;
	}
}

void Engine::DrawText(string const& value, Vector2f const& position, unsigned int size, Color const& color)
{
	Text text(AssetManager::GetFont("Font/BankGothic.otf"));
	text.setString(value);
	text.setCharacterSize(size);
	text.setFillColor(color);
	text.setOutlineColor(Color::Black);
	text.setOutlineThickness(2.f);
	text.setPosition(position);
	window->draw(text);
}

void Engine::LogEvent(string const& message)
{
	logger.AddEvent(message);
	cout << message << endl;
}
