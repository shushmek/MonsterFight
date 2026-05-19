#include "Engine.h"
#include <ctime>
#include <sstream>
#include <filesystem>

// ======================== GameStats ========================

void GameStats::save(const string& path) const
{
	ofstream f(path, ios::binary);
	if (!f) return;
	f.write(reinterpret_cast<const char*>(this), sizeof(GameStats));
}

void GameStats::load(const string& path)
{
	ifstream f(path, ios::binary);
	if (!f) return;
	f.read(reinterpret_cast<char*>(this), sizeof(GameStats));
}

// ======================== Engine ========================


void Engine::Input()
{
	while (const optional event = window->pollEvent())
	{
		if (event->is<Event::Closed>()) window->close();
		if (Keyboard::isKeyPressed(Keyboard::Key::Num1))
			Won();
		// проверка кнопок на нажатие
		startBTN.handleEvent(*event, *window);
		continueBTN.handleEvent(*event, *window);
		statBTN.handleEvent(*event, *window);
		exitBTN.handleEvent(*event, *window);
		toMenuBTN.handleEvent(*event, *window);
		endTurn.handleEvent(*event, *window);
		escapeBTN.handleEvent(*event, *window);
		for (int i = 0; i < handSize; i++)
		{
			if (hand[i] && hand[i]->getActive())
				hand[i]->handleEvent(*event, *window);
		}
		Bet.handleEvent(*event, *window);
		itemA.handleEvent(*event, *window);
		itemB.handleEvent(*event, *window);
		closePanel.handleEvent(*event, *window);

	}
}

Engine::Engine()
{
	///////////////////////////////////////////////////////////////// DEMO∨
	// Загружаем статистику
	LoadStats();
	CheckSaveFile();
	InitStatTexts();

	// Полупрозрачный чёрный оверлей для экрана статистики
	statOverlay.setSize({ 1280.f, 720.f });
	statOverlay.setFillColor(Color(0, 0, 0, 160));
	statOverlay.setPosition({ 0.f, 0.f });

	//MENU
	StartCutscene.AnimSetLoop(false);
	StartCutscene.AnimSetOnFinished([this]() {
		// Новая игра: увеличиваем счётчик прохождений
		stats.totalGamesPlayed++;
		SaveStats();
		state = State::Game;
	});
	StartCutscene.AnimStop();
	
	// START — новая игра (всегда видна)
	startBTN.setOnClick([this]() {
		// Удаляем старый сейв если есть
		DeleteSave();
		// Сброс игрока до начальных значений
		player.setLevel(1);
		player.setCash(30);
		player.setHealth(player.getMaxHealth());
		player.setCombo(0);
		player.setArm(player.getArmorValue());
		player.setMove(player.getMaxMove());
		_bet = 0;
		EndBattle();

		// Открываем лог
		logFile.open(LOG_PATH, ios::trunc);
		LogBattle("=== NEW GAME STARTED ===");

		StartCutscene._anim->play();
	});
	startBTN.setSpriteColor(Color(180,86,140));

	// CONTINUE — продолжить (видна только если есть сейв)
	continueBTN.setOnClick([this]() {
		LoadGame();

		// Открываем лог (дописываем)
		logFile.open(LOG_PATH, ios::app);
		LogBattle("=== GAME CONTINUED ===");

		state = State::Game;
	});
	continueBTN.setSpriteColor(Color(80, 180, 100));
	
	statBTN.setOnClick([this]() {
		UpdateStatTexts();
		state = State::Statistic;
	});
	statBTN.setSpriteColor(Color(180, 86, 140));

	exitBTN.setSpriteColor(Color(222, 32, 32));
	exitBTN.setOnClick([this] {
		if (logFile.is_open()) logFile.close();
		window->close();
	});

	//GAME
	toMenuBTN.setOnClick([this]() {state = State::Menu;});
	toMenuBTN.setSpriteColor(Color(222, 32, 32));
	toMenuBTN.setSize(0.6f, 0.6f);
	
	endTurn.setSize(0.8f , 0.8f);
	endTurn.setSpriteColor(Color(255,225,0));
	endTurn.setOnClick([this]() {
		endTurn.isPressed = true;
		if (endTurn.isPressed)
		{
			if (endTurn.clock.getElapsedTime() > milliseconds(100))
			{
				EndTurn();
				mobMove();
				endTurn.clock.restart();
				endTurn.isPressed = false;
			}
		}
			
	});

	hpBar.setScale({0.6f, 1.f});
	hpBar.setColor(Color(200,0,0));
	hpBar.setTextOutline(Color::Black, 2.f);

	moveBar.setColor(Color(20,200,40));
	moveBar.setScale({ 0.8f, 1.f });

	comboBar.setColor(Color(255,200,0));
	comboBar.setScale({ 0.5f, 0.5f });

	betValue.setSize(0.6f, 1.f);
	betValue.setSpriteColor(Color(140, 46, 100));

	escapeBTN.setSize(0.5f, 0.8f);
	escapeBTN.setOnClick([this]() {if (RandomNum(1, 2) == 1) EndBattle();});

	player.AnimStop();
	player.setPosition({100,250});
	
	mob.AnimStop();
	mob.setPosition({ 1200,250 });

	enemyHpBar.setColor(Color(150, 0, 0));
	enemyHpBar.setTextOutline(Color::Black, 2.f);

	Bet.setSpriteColor(Color(170,120, 50));
	Bet.setTextOutline(Color::Black, 2.f);
	Bet.setOnClick([this]() {
		int x = RandomNum(player.getMinBet(), player.getMaxBet());
		if (player.getMove() - 1 >= 0 && _bet - x >= 0)
		{
			player.setMove(player.getMove() - 1);
			player.setCash(player.getCash() + x);
			_bet -= x;
		}
	});

	InitializeAllCards();
	SetupBaseCards();
	UpdateBonusCards();

	attackCard.setEffectPosition({ 100, 134 }, { 32, 128 });

	panel.setSpriteColor(Color(0, 0, 0, 200));
	panel.setSize(3, 10);
	panel.setIsDrawed(false);
	closePanel.setIsDrawed(false);
	itemA.setIsDrawed(false);
	itemB.setIsDrawed(false);

	closePanel.setOnClick([this]() {
		panel.setIsDrawed(false);
		itemA.setIsDrawed(false);
		itemB.setIsDrawed(false);
		itemA.setActive(false);
		itemB.setActive(false);
		closePanel.setActive(false);
		closePanel.setIsDrawed(false);
		});
	///////////////////////////////////////////////////////////////// DEMO∧
}

void Engine::Run()
{
	cout << "is start" << endl;
	Clock clock;
	EndBattle();
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
	///////////////////////////////////////////////////////////////// DEMO∨
	//MENU
	menuBackground.AnimUpdate(deltaTime);
	StartCutscene.AnimUpdate(deltaTime);
	//GAME
	hpBar.setSliderNum(static_cast<float>(player.getHealth()) / player.getMaxHealth());
	hpBar.setText(to_string(player.getHealth()));
	armorBar.setText(to_string(player.getArm()));
	if (player.getArm() == 0) armorBar.setIsDrawed(false);
	else armorBar.setIsDrawed(true);
	moveBar.setSliderNum(static_cast<float>(player.getMove()) / player.getMaxMove());
	moveBar.setText(to_string(player.getMove()) + "/" + to_string(player.getMaxMove()));
	comboBar.setSliderNum(static_cast<float>(player.getCombo()) / player.getMaxCombo());
	comboBar.setText(to_string(player.getCombo()) + "/" + to_string(player.getMaxCombo()));
	betValue.setText(to_string(player.getMinBet()) + "< | " + to_string(player.getMaxBet()) + ">");

	enemyHpBar.setSliderNum(static_cast<float>(mob.getHealth()) / mob.getMaxHealth());
	enemyHpBar.setText(to_string(mob.getHealth()));
	enemyArmorBar.setText(to_string(mob.getArm()));
	if (mob.getArm() == 0) enemyArmorBar.setIsDrawed(false);
	else enemyArmorBar.setIsDrawed(true);

	gameBackground.AnimUpdate(deltaTime);
	player.AnimUpdate(deltaTime);

	bag.setText(to_string(player.getCash()));
	Bet.setText(to_string(_bet));
	
	mob.AnimUpdate(deltaTime);

	for (int i = 0; i < handSize; i++)
	{
		if (hand[i] && hand[i]->getActive())
			hand[i]->setSliderText(to_string(static_cast<int>(round(player.getMaxBet() * hand[i]->getSliderValue()))));
	}
	///////////////////////////////////////////////////////////////// DEMO∧

}


void Engine::Draw()
{
	window->clear();
	///////////////////////////////////////////////////////////////// DEMO∨
	switch (state)
	{
		//MENU
	case State::Menu: ////////////////////////////////////////////////////////////////////////////////////////MENU
		BTNOff();
		CheckSaveFile();

		statBTN.setActive(true);
		exitBTN.setActive(true);
		startBTN.setActive(true);

		menuBackground.draw(*window);

		// Если есть сейв — показываем CONTINUE вместо START на той же позиции
		if (hasSaveFile)
		{
			startBTN.setPosition({ 100, 225 });
			exitBTN.setPosition({ 100, 475 });
			continueBTN.setActive(true);
			continueBTN.draw(*window);
		}
		else
		{
			startBTN.setPosition({ 100, 200 });
			exitBTN.setPosition({ 100, 500 });
		}

		startBTN.draw(*window);
		statBTN.draw(*window);
		exitBTN.draw(*window);

		if (StartCutscene.AnimGetPlay())
			StartCutscene.draw(*window);
		break;
		//GAME
	case State::Game: //////////////////////////////////////////////////////////////////GAME
		BTNOff();
		Bet.setActive(true);
		toMenuBTN.setPosition({ 1110,10 });
		toMenuBTN.setActive(true);
		player.AnimPlay();
		mob.AnimPlay();
		endTurn.setActive(true);


		gameBackground.draw(*window);

		player.draw(*window);
		hpBar.draw(*window);
		armorBar.draw(*window);
		moveBar.draw(*window);
		comboBar.draw(*window);
		betValue.draw(*window);


		mob.draw(*window);
		enemyHpBar.draw(*window);
		enemyArmorBar.draw(*window);
		
		for (int i = 0; i < handSize; i++)
		{
			if (hand[i] && hand[i]->getActive())
				hand[i]->draw(*window);
		}

		bag.draw(*window);
		Bet.draw(*window);
		escapeBTN.draw(*window);
		endTurn.draw(*window);
		toMenuBTN.draw(*window);

		panel.draw(*window);
		closePanel.draw(*window);
		itemA.draw(*window);
		itemB.draw(*window);


		break;
		//STATISTIC
	case State::Statistic: ///////////////////////////////////////////////////////////////////////////STATISTIC
		BTNOff();
		toMenuBTN.setPosition({ 50,50 });
		toMenuBTN.setActive(true);

		menuBackground.draw(*window);
		window->draw(statOverlay);
		for (int i = 0; i < 8; i++)
		{
			if (statTexts[i]) window->draw(*statTexts[i]);
		}
		toMenuBTN.draw(*window);
		break;
	default: state = State::Menu;
		break;
	}
	///////////////////////////////////////////////////////////////// DEMO∧
	window->display();
}

void Engine::BTNOff()
{
	//closePanel.setActive(false);
	//itemA.setActive(false);
	//itemB.setActive(false);
	Bet.setActive(false);
	startBTN.setActive(false);
	continueBTN.setActive(false);
	exitBTN.setActive(false);
	toMenuBTN.setActive(false);
	hpBar.setActive(false);
	statBTN.setActive(false);
	endTurn.setActive(false);
}

void Engine::Won()
{
			itemA.setActive(true);
			itemB.setActive(true);
			panel.setIsDrawed(true);
			itemA.setIsDrawed(true);
			itemB.setIsDrawed(true);
			closePanel.setActive(true);
			closePanel.setIsDrawed(true);


	std::cout << "itemA active: " << itemA.isActive() << std::endl;
	std::cout << "itemB active: " << itemB.isActive() << std::endl;
	std::cout << "closePanel active: " << closePanel.isActive() << std::endl;
	std::cout << "itemA drawed: " << itemA.getIsDrawed() << std::endl;

	int x = RandomNum(1, 4);
	int a, b;

	switch (x)
	{
	case 1: 
		a = RandomNum(1, 10);
		b = RandomNum(1, 10);

		itemA.setSprite(AssetManager::GetTexture("Sprite/Weapon.png"),
			IntRect({ 0, 256 * a -256 }, { 256,256 }));
		itemB.setSprite(AssetManager::GetTexture("Sprite/Weapon.png"),
			IntRect({ 0, 256 * b - 256 }, { 256,256 }));

		itemA.setOnClick([this, a]() {
			player.setWeapon(_items.weapons[a]);
			UpdateBonusCards();
			HideItems();
			});

		itemB.setOnClick([this, b]() {
			player.setWeapon(_items.weapons[b]);
			UpdateBonusCards();
			HideItems();
			});
		cout << _items.weapons[a].getName() << "|" << _items.weapons[b].getName() << endl;
		break;

	case 2: 
		a = RandomNum(1, 10);   
		b = RandomNum(1, 12); 

		itemA.setSprite(AssetManager::GetTexture("Sprite/Weapon.png"),
			IntRect({ 0, 256 * a - 256 }, { 256,256 }));
		itemB.setSprite(AssetManager::GetTexture("Sprite/Armor.png"),
			IntRect({ 0, 256 * b - 256 }, { 256,256 }));

		itemA.setOnClick([this, a]() {
			player.setWeapon(_items.weapons[a]);
			UpdateBonusCards();
			HideItems();
			});

		itemB.setOnClick([this, b]() {
			player.setArmor(_items.armors[b]);
			UpdateBonusCards();
			HideItems();
			});
		break;
		cout << _items.weapons[a].getName() << "|" << _items.armors[b].getName() << endl;

	case 3:  
		a = RandomNum(1, 12);  
		b = RandomNum(1, 10);   

		itemA.setSprite(AssetManager::GetTexture("Sprite/Armor.png"),
			IntRect({ 0, 256 * a - 256 }, { 256,256 }));
		itemB.setSprite(AssetManager::GetTexture("Sprite/Weapon.png"),
			IntRect({ 0, 256 * b - 256 }, { 256,256 }));

		itemA.setOnClick([this, a]() {
			player.setArmor(_items.armors[a]);
			UpdateBonusCards();
			HideItems();
			});

		itemB.setOnClick([this, b]() {
			player.setWeapon(_items.weapons[b]);
			UpdateBonusCards();
			HideItems();
			});
		break;
		cout << _items.armors[a].getName() << "|" << _items.weapons[b].getName() << endl;

	case 4:
		a = RandomNum(1, 12);
		b = RandomNum(1, 12);

		itemA.setSprite(AssetManager::GetTexture("Sprite/Armor.png"),
			IntRect({ 0, 256 * a - 256 }, { 256,256 }));
		itemB.setSprite(AssetManager::GetTexture("Sprite/Armor.png"),
			IntRect({ 0, 256 * b - 256 }, { 256,256 }));

		itemA.setOnClick([this, a]() {
			player.setArmor(_items.armors[a]);
			UpdateBonusCards();
			HideItems();
			});

		itemB.setOnClick([this, b]() {
			player.setArmor(_items.armors[b]);
			UpdateBonusCards();
			HideItems();
			});
		break;
		cout << _items.armors[a].getName() << "|" << _items.armors[b].getName() << endl;

	}
}
void Engine::HideItems()
{
	itemA.setActive(false);
	itemB.setActive(false);
	closePanel.setActive(false);
	panel.setIsDrawed(false);
	itemA.setIsDrawed(false);
	itemB.setIsDrawed(false);
	closePanel.setIsDrawed(false);
}

void Engine::dealDamage(Cards *_card)
{	
	int bet = static_cast<int>(round(player.getMaxBet() * _card->getSliderValue()));
	int dmg = static_cast<int>(round(player.Attack()* (bet/player.getMinBet())));
	if (dmg == 0) dmg = 1;

	// Статистика: суммарный нанесённый урон
	stats.totalDamageDealt += dmg;

	if (mob.getArm() > 0)
	{
		int x = mob.getArm();
		mob.setArm(mob.getArm() - dmg);
		dmg -= x;
		if (mob.getArm() < 0)	mob.setArm(0);
		if (dmg < 0) dmg = 0;

	}
	mob.TakeDamage(dmg);

	LogBattle("Player dealt " + to_string(dmg) + " damage to " + mob.getName()
		+ " (HP: " + to_string(mob.getHealth()) + "/" + to_string(mob.getMaxHealth()) + ")");

	if (mob.getHealth() <= 0)
	{
		// Статистика: убийство
		stats.totalKills++;
		LogBattle(mob.getName() + " killed! Total kills: " + to_string(stats.totalKills));

		int goldWon = _bet;
		stats.totalGoldEarned += goldWon;
		LogBattle("Gold won from battle: " + to_string(goldWon));

		EndBattle();
		player.LevelUp();

		// Обновляем рекорд уровня
		if (player.getLevel() > stats.highestLevel)
			stats.highestLevel = player.getLevel();

		LogBattle("Level up! Now level " + to_string(player.getLevel()));

		if (player.getLevel() % 2 == 0)
			Won();

		// Автосохранение после боя
		SaveGame();
		SaveStats();
	}
}

void Engine::CardCast(Cards& card, int bet)
{
	int x = player.getCash() - bet;
	_bet += bet;
	player.setCash(x);
	player.setMove(player.getMove() - card.getCostAP());
	player.setCombo(player.getCombo() - card.getCostCP());
}

void Engine::EndTurn()
{
	player.setMove(player.getMaxMove());
}

void Engine::EndBattle()
{
	if (player.getLevel() == 20)
	{
		cout << "you win\n";
		LogBattle("=== VICTORY! Player reached level 20! ===");

		stats.totalWins++;
		SaveStats();
		DeleteSave(); // удаляем сейв при победе

		// Закрываем лог
		if (logFile.is_open()) logFile.close();

		// Сброс
		player.setLevel(1);
		player.setCash(30);
		player.setHealth(player.getMaxHealth());
		player.setCombo(0);
		player.setArm(player.getArmorValue());
		player.setMove(player.getMaxMove());
		_bet = 0;
		state = State::Menu;
		return;
	}
	if (player.getLevel() <= 5)			 mob = enemys[RandomNum(1, 10) - 1];
	else if (player.getLevel() <= 10)	 mob = enemys[RandomNum(10, 20) - 1]; 
	else if (player.getLevel() <= 15)	 mob = enemys[RandomNum(20, 30) - 1]; 
	else if (player.getLevel() < 19)	 mob = enemys[RandomNum(30, 35) - 1]; 
	else								 mob = enemys[RandomNum(36, 40) - 1];
	mob.setPosition({ 1200, 250 });
	mob.AnimStop();
	EndTurn();
	player.setCombo(0);
	player.setArm(player.getArmorValue());
	player.setCash(player.getCash() + _bet);
	_bet = 0;

	mob.setHealth(mob.getMaxHealth());
	mob.setArm(mob.getArmorValue());
}

bool Engine::canCast(Cards* _card)
{
	return !(player.getCash() - static_cast<int>(round(player.getMaxBet() * _card->getSliderValue())) < 0 || player.getMove() - _card->getCostAP() < 0 || player.getCombo() - _card->getCostCP() < 0);
}

void Engine::mobMove()
{
	_bet += mob.Bet();
	int dmg = mob.Attack();

	// Статистика: полученный урон
	stats.totalDamageTaken += dmg;

	if (player.getArm() > 0)
	{
		int x = player.getArm();
		player.setArm(player.getArm() - dmg);
		dmg -= x;
		if (player.getArm() < 0)	player.setArm(0);
		if (dmg < 0) dmg = 0;
	}
	player.TakeDamage(dmg);

	LogBattle(mob.getName() + " dealt " + to_string(dmg) + " damage to Player"
		+ " (HP: " + to_string(player.getHealth()) + "/" + to_string(player.getMaxHealth()) + ")");

	if (player.getHealth() <= 0)
	{
		LogBattle("=== DEFEAT! Player died at level " + to_string(player.getLevel()) + " ===");

		stats.totalLosses++;
		if (player.getLevel() > stats.highestLevel)
			stats.highestLevel = player.getLevel();
		SaveStats();
		DeleteSave(); // удаляем сейв при проигрыше

		// Закрываем лог
		if (logFile.is_open()) logFile.close();

		RestartGame();
	}
}

void Engine::RestartGame()
{
	cout << "you lose\n";
	EndBattle();
	player.setLevel(1);
	player.setCash(30);
	player.setHealth(player.getMaxHealth());
	state = State::Menu;
}

int Engine::RandomNum(int x, int y)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(x, y);
	return dist(gen);
}

void Engine::InitializeAllCards()
{
	allCards.clear();

	//// ID 0: Мощная атака
	//auto card0 = make_unique<Cards>(Cards::Attack, "Power Strike", 3, 2, 0, 0,
	//	Vector2f{ 790.f, 500.f }, "Sprite/cards.png", "",
	//	"Font/BankGothic.otf", "", Color::White, 24);
	//card0->setEffect("add 2", IntRect({ 128,0 }, { 32,32 }));
	//card0->setEffectPosition({ 100, 134 }, { 32, 128 });
	//card0->setAction([this, ptr = card0.get()]() {
	//	if (canCast(ptr))
	//	{
	//		int bet = static_cast<int>(round(player.getMaxBet() * ptr->getSliderValue()));
	//		CardCast(*ptr, bet);
	//		dealDamage(ptr);
	//		player.setCombo(player.getCombo() + 2);
	//	}
	//	});
	//allCards.push_back(move(card0));

	//// ID 1: Стена щитов
	//auto card1 = make_unique<Cards>(Cards::Defense, "Shield Wall", 2, 1, 0, 0,
	//	Vector2f{ 790.f, 500.f }, "Sprite/cards.png", "",
	//	"Font/BankGothic.otf", "", Color::White, 24);
	//card1->setEffect("add 2", IntRect({ 128,0 }, { 32,32 }));
	//card1->setEffectPosition({ 100, 134 }, { 32, 128 });
	//card1->setAction([this, ptr = card1.get()]() {
	//	if (canCast(ptr))
	//	{
	//		int bet = static_cast<int>(round(player.getMaxBet() * ptr->getSliderValue()));
	//		CardCast(*ptr, bet);
	//		player.setArm(player.getArm() + 10);
	//		player.setCombo(player.getCombo() + 1);
	//	}
	//	});
	//allCards.push_back(move(card1));

	//// ID 2: Вампиризм
	//auto card2 = make_unique<Cards>(Cards::Attack, "Vampirism", 3, 1, 0, 0,
	//	Vector2f{ 790.f, 500.f }, "Sprite/cards.png", "",
	//	"Font/BankGothic.otf", "", Color::White, 24);
	//card2->setEffect("heal", IntRect({ 0,32 }, { 32,32 }));
	//card2->setEffectPosition({ 100, 134 }, { 32, 128 });
	//card2->setAction([this, ptr = card2.get()]() {
	//	if (canCast(ptr))
	//	{
	//		int bet = static_cast<int>(round(player.getMaxBet() * ptr->getSliderValue()));
	//		CardCast(*ptr, bet);
	//		int dmg = player.Attack() * (bet / player.getMinBet());
	//		mob.TakeDamage(dmg);
	//		player.setHealth(min(player.getHealth() + dmg / 2, player.getMaxHealth()));
	//		player.setCombo(player.getCombo() + 1);
	//	}
	//	});
	//allCards.push_back(move(card2));

	//// ID 3: Ядовитый удар
	//auto card3 = make_unique<Cards>(Cards::Attack, "Poison Strike", 2, 1, 0, 0,
	//	Vector2f{ 790.f, 500.f }, "Sprite/cards.png", "",
	//	"Font/BankGothic.otf", "", Color::White, 24);
	//card3->setEffect("poison", IntRect({ 64,32 }, { 32,32 }));
	//card3->setEffectPosition({ 100, 134 }, { 32, 128 });
	//card3->setAction([this, ptr = card3.get()]() {
	//	if (canCast(ptr))
	//	{
	//		int bet = static_cast<int>(round(player.getMaxBet() * ptr->getSliderValue()));
	//		CardCast(*ptr, bet);
	//		dealDamage(ptr);
	//		player.setCombo(player.getCombo() + 1);
	//	}
	//	});
	//allCards.push_back(move(card3));

	//// ID 4: Лечение
	//auto card4 = make_unique<Cards>(Cards::Utility, "Heal", 2, 0, 0, 0,
	//	Vector2f{ 790.f, 500.f }, "Sprite/cards.png", "",
	//	"Font/BankGothic.otf", "", Color::White, 24);
	//card4->setEffect("heal", IntRect({ 0,32 }, { 32,32 }));
	//card4->setEffectPosition({ 100, 134 }, { 32, 128 });
	//card4->setAction([this, ptr = card4.get()]() {
	//	if (canCast(ptr))
	//	{
	//		int bet = static_cast<int>(round(player.getMaxBet() * ptr->getSliderValue()));
	//		CardCast(*ptr, bet);
	//		player.setHealth(min(player.getHealth() + 20, player.getMaxHealth()));
	//		player.setCombo(player.getCombo() + 1);
	//	}
	//	});
	//allCards.push_back(move(card4));

}

void Engine::SetupBaseCards()
{
	attackCard.setEffect("add 1", IntRect({ 96,0 }, { 32,32 }));
	attackCard.setEffectPosition({ 100, 134 }, { 32, 128 });
	attackCard.setAction([this]() {
		if (canCast(&attackCard))
		{
			CardCast(attackCard, static_cast<int>(round(player.getMaxBet() * attackCard.getSliderValue())));
			dealDamage(&attackCard);
			player.setCombo(player.getCombo() + 1);
			if (player.getCombo() > player.getMaxCombo())
				player.setCombo(player.getMaxCombo());
		}
	});


	defenseCard.setAction([this]() {
		if (canCast(&defenseCard))
		{
			CardCast(defenseCard, static_cast<int>(round(player.getMaxBet() * defenseCard.getSliderValue())));
			
			player.setArm(player.getArm() + player.getArmorValue());
			player.setCombo(0);
		}
	});

	utilityCard.setTypeObj(5);
	utilityCard.setAction([this]() {
		if (canCast(&utilityCard))
		{
			CardCast(utilityCard, static_cast<int>(round(player.getMaxBet() * utilityCard.getSliderValue())));
			player.setHealth(min(player.getHealth() + player.getMinBet(), player.getMaxHealth()));
		}
	});
}

void Engine::UpdateBonusCards()
{
	int weaponCardID = player.getWeapon().getCardID();
	int armorCardID = player.getArmor().getCardID(); 
	utilityCard.setText(to_string(player.getMinBet()));
	attackCard.setText(to_string(player.getDamage()));
	defenseCard.setText(to_string(player.getArmorValue()));

	handSize = 3;  
	hand[0] = &utilityCard;
	hand[1] = &attackCard;
	hand[2] = &defenseCard;

	if (weaponCardID >= 0 && weaponCardID < allCards.size())
	{
		hand[handSize] = allCards[weaponCardID].get();
		handSize++;
	}
	if (armorCardID >= 0 && armorCardID < allCards.size())
	{
		hand[handSize] = allCards[armorCardID].get();
		handSize++;
	}
	for (int i = 0; i < handSize; i++)
	{
		if (hand[i])
		{
			hand[i]->setPosition({ 310.f + 160.f * i, 510.f });
			hand[i]->setActive(true);
		}
	}
}

// ======================== Save / Load ========================

void Engine::SaveGame()
{
	ofstream f(SAVE_PATH, ios::binary);
	if (!f) return;

	int level = player.getLevel();
	int health = player.getHealth();
	int cash = player.getCash();
	int combo = player.getCombo();
	int arm = player.getArm();
	int move = player.getMove();
	int bet = _bet;

	// Состояние моба
	int mobHP = mob.getHealth();
	int mobArm = mob.getArm();

	f.write(reinterpret_cast<char*>(&level), sizeof(int));
	f.write(reinterpret_cast<char*>(&health), sizeof(int));
	f.write(reinterpret_cast<char*>(&cash), sizeof(int));
	f.write(reinterpret_cast<char*>(&combo), sizeof(int));
	f.write(reinterpret_cast<char*>(&arm), sizeof(int));
	f.write(reinterpret_cast<char*>(&move), sizeof(int));
	f.write(reinterpret_cast<char*>(&bet), sizeof(int));
	f.write(reinterpret_cast<char*>(&mobHP), sizeof(int));
	f.write(reinterpret_cast<char*>(&mobArm), sizeof(int));

	hasSaveFile = true;
	cout << "Game saved (level " << level << ", hp " << health << ", cash " << cash << ")\n";
}

void Engine::LoadGame()
{
	ifstream f(SAVE_PATH, ios::binary);
	if (!f) return;

	int level, health, cash, combo, arm, move, bet, mobHP, mobArm;

	f.read(reinterpret_cast<char*>(&level), sizeof(int));
	f.read(reinterpret_cast<char*>(&health), sizeof(int));
	f.read(reinterpret_cast<char*>(&cash), sizeof(int));
	f.read(reinterpret_cast<char*>(&combo), sizeof(int));
	f.read(reinterpret_cast<char*>(&arm), sizeof(int));
	f.read(reinterpret_cast<char*>(&move), sizeof(int));
	f.read(reinterpret_cast<char*>(&bet), sizeof(int));
	f.read(reinterpret_cast<char*>(&mobHP), sizeof(int));
	f.read(reinterpret_cast<char*>(&mobArm), sizeof(int));

	player.setLevel(level);
	player.setHealth(health);
	player.setCash(cash);
	player.setCombo(combo);
	player.setArm(arm);
	player.setMove(move);
	_bet = bet;

	// Восстанавливаем моба по текущему уровню
	if (level <= 5)				mob = enemys[RandomNum(1, 3) - 1];
	else if (level <= 10)		mob = enemys[RandomNum(1, 3) - 1];
	else if (level <= 15)		mob = enemys[RandomNum(1, 3) - 1];
	else if (level <= 19)		mob = enemys[RandomNum(1, 3) - 1];
	else						mob = enemys[RandomNum(1, 3) - 1];
	mob.setPosition({ 1200, 250 });
	mob.AnimStop();
	mob.setHealth(mobHP);
	mob.setArm(mobArm);

	cout << "Game loaded (level " << level << ", hp " << health << ", cash " << cash << ")\n";
}

void Engine::DeleteSave()
{
	if (filesystem::exists(SAVE_PATH))
	{
		filesystem::remove(SAVE_PATH);
		cout << "Save deleted\n";
	}
	hasSaveFile = false;
}

bool Engine::SaveExists() const
{
	return filesystem::exists(SAVE_PATH);
}

void Engine::CheckSaveFile()
{
	hasSaveFile = SaveExists();
}

void Engine::SaveStats()
{
	stats.save(STATS_PATH);
}

void Engine::LoadStats()
{
	stats.load(STATS_PATH);
}

void Engine::InitStatTexts()
{
	Font& font = AssetManager::GetFont("Font/BankGothic.otf");
	for (int i = 0; i < 8; i++)
	{
		statTexts[i] = new Text(font);
		statTexts[i]->setCharacterSize(28);
		statTexts[i]->setFillColor(Color::White);
		statTexts[i]->setOutlineThickness(2.f);
		statTexts[i]->setOutlineColor(Color::Black);
		statTexts[i]->setPosition({ 100.f, 150.f + i * 55.f });
	}
}

void Engine::UpdateStatTexts()
{
	LoadStats();

	int totalGames = stats.totalWins + stats.totalLosses;
	float winRate = (totalGames > 0) ? (static_cast<float>(stats.totalWins) / totalGames * 100.f) : 0.f;

	// Форматируем винрейт
	stringstream ss;
	ss.precision(1);
	ss << fixed << winRate;
	string winRateStr = ss.str();

	statTexts[0]->setString("Monsters killed: " + to_string(stats.totalKills));
	statTexts[1]->setString("Total damage dealt: " + to_string(stats.totalDamageDealt));
	statTexts[2]->setString("Total damage taken: " + to_string(stats.totalDamageTaken));
	statTexts[3]->setString("Total gold earned: " + to_string(stats.totalGoldEarned));
	statTexts[4]->setString("Games played: " + to_string(stats.totalGamesPlayed));
	statTexts[5]->setString("Wins / Losses: " + to_string(stats.totalWins) + " / " + to_string(stats.totalLosses));
	statTexts[6]->setString("Win rate: " + winRateStr + "%");
	statTexts[7]->setString("Highest level: " + to_string(stats.highestLevel));
}

void Engine::LogBattle(const string& msg)
{
	if (!logFile.is_open()) return;

	// Получаем время
	time_t now = time(nullptr);
	struct tm t;
	localtime_s(&t, &now);
	char timeBuf[64];
	strftime(timeBuf, sizeof(timeBuf), "[%H:%M:%S]", &t);

	logFile << timeBuf << " " << msg << "\n";
	logFile.flush();
	cout << timeBuf << " " << msg << "\n";
}
