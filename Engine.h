#pragma once
#include<iostream>
#include<fstream>
#include<SFML/Graphics.hpp>
#include<memory>
#include "AssetManager.h"
#include "Button.h"
#include "Object.h"
#include "Slider.h"
#include "Creature.h"
#include "ItemList.h"
#include "Player.h"
#include "Cards.h"
#include "Bet.h"

using namespace sf;
using namespace std;

// ---- Persistent statistics (saved to stats.dat) ----
struct GameStats
{
	int totalKills = 0;       // всего убито монстров
	int totalDamageDealt = 0; // весь нанесённый урон за все игры
	int totalDamageTaken = 0; // весь полученный урон за все игры
	int totalGoldEarned = 0;  // всё заработанное золото
	int totalGamesPlayed = 0; // кол-во начатых прохождений
	int totalWins = 0;        // кол-во побед (дошёл до 20)
	int totalLosses = 0;      // кол-во поражений
	int highestLevel = 0;     // максимальный достигнутый уровень

	void save(const string& path) const;
	void load(const string& path);
};

class Engine
{
	unique_ptr<RenderWindow>  window = make_unique<RenderWindow>(VideoMode({ 1280, 720 }), "SFML works!", Style::Default); //указатель на окно
///////////////////////////////////////////////////////////////// DEMO ∨∨∨
	enum State {Menu, Game, Statistic};
	State state = State::Menu;
	ItemList _items;
	ItemList items;

	Enemy* enemys = new Enemy[]{
		Enemy("Billi", 1, 20, 1, 0, 3, 1, 2.f, 2, 6, items.weapons[0], items.armors[0], AssetManager::GetTexture("Sprite/Enemy.png"), IntRect({ 0,256 }, { 256,256 }), 10, 1, 100),		//0
		Enemy("Goblin", 1, 15, 1, 0, 3, 1, 2.f, 2, 6, items.weapons[0], items.armors[2], AssetManager::GetTexture("Sprite/Enemy.png"), IntRect({ 0,0 }, { 256,256 }), 10, 1, 100),	//1
		Enemy("Rat", 1, 10, 1, 0, 3, 10, 1.5f, 2, 6, items.weapons[0], items.armors[0], AssetManager::GetTexture("Sprite/Enemy.png"), IntRect({ 0,512 }, { 256,256 }), 10, 1, 100),		//2
		Enemy("Billi", 1, 20, 1, 0, 3, 1, 2.f, 2, 6, items.weapons[1], items.armors[0], AssetManager::GetTexture("Sprite/Enemy.png"), IntRect({ 0,256 }, { 256,256 }), 10, 1, 100),		//3
		Enemy("Rat", 1, 10, 1, 0, 3, 10, 1.5f, 2, 6, items.weapons[2], items.armors[0], AssetManager::GetTexture("Sprite/Enemy.png"), IntRect({ 0,512 }, { 256,256 }), 10, 1, 100),		//4
		Enemy("Billi", 1, 20, 1, 0, 3, 1, 2.f, 2, 6, items.weapons[4], items.armors[0], AssetManager::GetTexture("Sprite/Enemy.png"), IntRect({ 0,256 }, { 256,256 }), 10, 1, 100),		//5
		Enemy("Goblin", 1, 15, 1, 0, 3, 1, 2.f, 2, 6, items.weapons[0], items.armors[3], AssetManager::GetTexture("Sprite/Enemy.png"), IntRect({ 0,0 }, { 256,256 }), 10, 1, 100),	//6
		Enemy("Rat", 1, 10, 1, 0, 3, 10, 1.5f, 2, 6, items.weapons[1], items.armors[0], AssetManager::GetTexture("Sprite/Enemy.png"), IntRect({ 0,512 }, { 256,256 }), 10, 1, 100),		//7
		Enemy("Billi", 1, 20, 1, 0, 3, 1, 2.f, 2, 6, items.weapons[1], items.armors[0], AssetManager::GetTexture("Sprite/Enemy.png"), IntRect({ 0,256 }, { 256,256 }), 10, 1, 100),		//8
		Enemy("Rat", 1, 10, 1, 0, 3, 10, 1.5f, 2, 6, items.weapons[2], items.armors[0], AssetManager::GetTexture("Sprite/Enemy.png"), IntRect({ 0,512 }, { 256,256 }), 10, 1, 100),		//9

		Enemy("Goblin", 2, 20, 1, 0, 3, 1, 2.f, 2, 6, items.weapons[3], items.armors[4], AssetManager::GetTexture("Sprite/Enemy.png"), IntRect({ 0,0 }, { 256,256 }), 10, 1, 100),	//10
		Enemy("Billi", 2, 25, 1, 0, 3, 1, 2.f, 2, 6, items.weapons[1], items.armors[2], AssetManager::GetTexture("Sprite/Enemy.png"), IntRect({ 0,256 }, { 256,256 }), 10, 1, 100),		//11
		Enemy("Rat", 2, 15, 1, 0, 3, 10, 1.5f, 2, 6, items.weapons[2], items.armors[6], AssetManager::GetTexture("Sprite/Enemy.png"), IntRect({ 0,512 }, { 256,256 }), 10, 1, 100),		//12
		Enemy("Goblin", 2, 20, 1, 0, 3, 1, 2.f, 2, 6, items.weapons[6], items.armors[4], AssetManager::GetTexture("Sprite/Enemy.png"), IntRect({ 0,0 }, { 256,256 }), 10, 1, 100),	//13
		Enemy("Billi", 2, 25, 1, 0, 3, 1, 2.f, 2, 6, items.weapons[3], items.armors[5], AssetManager::GetTexture("Sprite/Enemy.png"), IntRect({ 0,256 }, { 256,256 }), 10, 1, 100),		//14
		Enemy("Goblin", 2, 20, 1, 0, 3, 1, 2.f, 2, 6, items.weapons[3], items.armors[1], AssetManager::GetTexture("Sprite/Enemy.png"), IntRect({ 0,0 }, { 256,256 }), 10, 1, 100),	//15
		Enemy("Billi", 2, 25, 1, 0, 3, 1, 2.f, 2, 6, items.weapons[1], items.armors[2], AssetManager::GetTexture("Sprite/Enemy.png"), IntRect({ 0,256 }, { 256,256 }), 10, 1, 100),		//16
		Enemy("Rat", 2, 15, 1, 0, 3, 10, 1.5f, 2, 6, items.weapons[2], items.armors[3], AssetManager::GetTexture("Sprite/Enemy.png"), IntRect({ 0,512 }, { 256,256 }), 10, 1, 100),		//17
		Enemy("Goblin", 2, 20, 1, 0, 3, 1, 2.f, 2, 6, items.weapons[6], items.armors[4], AssetManager::GetTexture("Sprite/Enemy.png"), IntRect({ 0,0 }, { 256,256 }), 10, 1, 100),	//18
		Enemy("Billi", 2, 25, 1, 0, 3, 1, 2.f, 2, 6, items.weapons[3], items.armors[5], AssetManager::GetTexture("Sprite/Enemy.png"), IntRect({ 0,256 }, { 256,256 }), 10, 1, 100),		//19

		Enemy("Rat", 2, 30, 1, 0, 3, 10, 1.5f, 2, 6, items.weapons[4], items.armors[5], AssetManager::GetTexture("Sprite/Enemy.png"), IntRect({ 0,256 }, { 256,256 }), 10, 1, 100),		//20
		Enemy("Billi", 1, 50, 1, 0, 3, 1, 2.f, 2, 6, items.weapons[7], items.armors[7], AssetManager::GetTexture("Sprite/Enemy.png"), IntRect({ 0,256 }, { 256,256 }), 10, 1, 100),		//21
		Enemy("Goblin", 1, 40, 5, 0, 3, 1, 2.f, 2, 6, items.weapons[5], items.armors[6], AssetManager::GetTexture("Sprite/Enemy.png"), IntRect({ 0,0 }, { 256,256 }), 10, 1, 100),		//22
		Enemy("Goblin", 1, 42, 2, 0, 3, 1, 2.f, 2, 6, items.weapons[2], items.armors[5], AssetManager::GetTexture("Sprite/Enemy.png"), IntRect({ 0,0 }, { 256,256 }), 10, 1, 100),		//23
		Enemy("Rat", 1, 25, 2, 0, 3, 1, 2.f, 2, 6, items.weapons[5], items.armors[4], AssetManager::GetTexture("Sprite/Enemy.png"), IntRect({ 0,512 }, { 256,256 }), 10, 1, 100),		//24
		Enemy("Billi", 1, 45, 2, 0, 3, 1, 2.f, 2, 6, items.weapons[6], items.armors[8], AssetManager::GetTexture("Sprite/Enemy.png"), IntRect({ 0,256 }, { 256,256 }), 10, 1, 100),		//25
		Enemy("Rat", 2, 30, 1, 0, 3, 10, 1.5f, 2, 6, items.weapons[4], items.armors[5], AssetManager::GetTexture("Sprite/Enemy.png"), IntRect({ 0,256 }, { 256,256 }), 10, 1, 100),		//26
		Enemy("Billi", 1, 50, 1, 0, 3, 1, 2.f, 2, 6, items.weapons[3], items.armors[10], AssetManager::GetTexture("Sprite/Enemy.png"), IntRect({ 0,256 }, { 256,256 }), 10, 1, 100),	//27
		Enemy("Goblin", 1, 40, 5, 0, 3, 1, 2.f, 2, 6, items.weapons[5], items.armors[4], AssetManager::GetTexture("Sprite/Enemy.png"), IntRect({ 0,0 }, { 256,256 }), 10, 1, 100),		//28
		Enemy("Goblin", 1, 42, 2, 0, 3, 1, 2.f, 2, 6, items.weapons[8], items.armors[3], AssetManager::GetTexture("Sprite/Enemy.png"), IntRect({ 0,0 }, { 256,256 }), 10, 1, 100),		//29
		Enemy("Rat", 1, 25, 2, 0, 3, 1, 2.f, 2, 6, items.weapons[2], items.armors[9], AssetManager::GetTexture("Sprite/Enemy.png"), IntRect({ 0,512 }, { 256,256 }), 10, 1, 100),		//30
		
	};
	//MENU
	Object menuBackground = Object(AssetManager::GetTexture("Sprite/MainMenu.jpg"), IntRect({ 0,0 }, { 1280,720 }), 9, 1, 100);
	Object StartCutscene = Object(AssetManager::GetTexture("Sprite/Cutscen.jpg"), IntRect({0,0}, {1280,720}), 10, 5, 60);
	Button continueBTN = Button({ 100,100 }, "Sprite/btn.png", "CONTINUE", "Font/BankGothic.otf", "", Color::White, 35); // продолжить (если есть сейв)
	Button startBTN = Button({ 100,225 }, "Sprite/btn.png", "START", "Font/BankGothic.otf", "", Color::White, 45);
	Button statBTN = Button({ 100,350 }, "Sprite/btn.png", "STATISTICS", "Font/BankGothic.otf", "", Color::White, 35);
	Button exitBTN = Button({ 100,475 }, "Sprite/btn.png", "EXIT", "Font/BankGothic.otf", "", Color::White, 45); //выход из игры
	//Game
	int _bet = 0;

	Button panel = Button({ 250, 50 }, "Sprite/square.jpg", "", "Font/BankGothic.otf", "");
	Button closePanel = Button({ 400, 100 }, "Sprite/square.jpg", "close", "Font/BankGothic.otf", "");
	Button itemA = Button({ 350, 250 }, "Sprite/square.jpg", "", "Font/BankGothic.otf", "");
	Button itemB = Button({ 550, 250 }, "Sprite/square.jpg", "", "Font/BankGothic.otf", "");

	Object gameBackground = Object(AssetManager::GetTexture("Sprite/GameBackground.jpg"), IntRect({0,0}, {1280,720}), 9, 1, 100);

	Button endTurn = Button({ 1065,580 }, "Sprite/btn.png", "end turn", "Font/BankGothic.otf", "", Color::White, 45);

	Button toMenuBTN = Button({ 50,50 }, "Sprite/btn.png", "CL0SE", "Font/BankGothic.otf", "", Color::White, 45); //вернутся в первую сцену
	Button bag = Button({ 10, 510 }, "Sprite/bag.png", "100", "Font/BankGothic.otf", "");
	Button Bet = Button({ 510, 10 }, "Sprite/square.jpg", "999999", "Font/BankGothic.otf", "");

	Button escapeBTN = Button({ 10,200 }, "Sprite/arrow.png", "", "Font/BankGothic.otf", "", Color::White, 45);
	Button betValue = Button({ 1500,550 }, "Sprite/square.jpg", "", "Font/BankGothic.otf", "", Color::White, 45);

	Player player = Player("player", 1, 100, 1, 0, 2, 5, 1.5f, 2, 6, 30, 3, _items.weapons[1], _items.armors[0], AssetManager::GetTexture("Sprite/Player.png"), IntRect({ 0,0 }, { 256,256 }), 10, 1, 100);
	Slider hpBar = Slider({ 10,640 }, "Sprite/SliderBack.png", AssetManager::GetTexture("Sprite/SliderFront.png"), "", "Font/BankGothic.otf");
	Button armorBar = Button({ 250, 640 }, "Sprite/_arm.png", "", "Font/BankGothic.otf", "");
	Slider moveBar = Slider({ 10,10 }, "Sprite/SliderBack.png", AssetManager::GetTexture("Sprite/SliderFront.png"), "", "Font/BankGothic.otf");
	Slider comboBar = Slider({ 10,74 }, "Sprite/SliderBack.png", AssetManager::GetTexture("Sprite/SliderFront.png"), "", "Font/BankGothic.otf");
	
	vector<unique_ptr<Cards>> allCards;

	Cards attackCard = Cards(Cards::Attack, "Attack", 1, 0, 0, 0, { 310.f, 500.f }, "Sprite/cards.png", "", "Font/BankGothic.otf", "", Color::White, 24);
	Cards defenseCard = Cards(Cards::Defense, "Defense", 1, 0, 0, 0, { 470.f, 500.f }, "Sprite/cards.png", "0", "Font/BankGothic.otf", "", Color::White, 24);
	Cards utilityCard = Cards(Cards::Utility, "Health", 2, 0, 0, 0, { 630.f, 500.f }, "Sprite/cards.png", "0", "Font/BankGothic.otf", "", Color::White, 24);
	Cards bonusCard1 =  Cards(Cards::Attack, "Power Strike", 3, 0, 0, 0, { 790.f, 500.f }, "Sprite/cards.png", "0", "Font/BankGothic.otf", "", Color::White, 24);
	Cards bonusCard2 = Cards(Cards::Defense, "Shield Wall", 2, 0, 0, 0, { 950.f, 500.f }, "Sprite/cards.png", "0", "Font/BankGothic.otf", "", Color::White, 24);


	Cards* hand[5] = { nullptr };
	int handSize = 3;  

	void InitializeAllCards();
	void SetupBaseCards();   
	void UpdateBonusCards();    
	void HideItems();

	Enemy mob = enemys[0];
	Slider enemyHpBar = Slider({ 950,150 }, "Sprite/square.jpg", "999", "Font/BankGothic.otf");
	Button enemyArmorBar = Button({ 900, 150 }, "Sprite/_arm.png", "", "Font/BankGothic.otf", "");


	//STATISTIC
	RectangleShape statOverlay;                // полупрозрачный чёрный квадрат поверх фона меню
	GameStats stats;                           // глобальная статистика
	Text* statTexts[8] = { nullptr };          // тексты для экрана статистики

	// ---- Save / Load ----
	const string SAVE_PATH = "save.dat";
	const string STATS_PATH = "stats.dat";
	const string LOG_PATH = "battle_log.txt";
	bool hasSaveFile = false;                  // есть ли файл сохранения

	// ---- Battle log ----
	ofstream logFile;                          // лог-файл текущей сессии

	///////////////////////////////////////////////////////////////// DEMO ∧∧∧

	void Input(); // обработка нажатий и ввода с клавиатуры
	void Update(Time const& deltaTime); // цикл наподобие while(true), deltaTime - это время, тут писать логику зависящую от времени
	void Draw();//ортисовка объектов, всякое говно не связанное с отрисовкой не пихать
	void BTNOff(); // все кнопки не активны
	void Won();
public:
	Engine(); //конструктор, ничего не требует

	void Run(); // функция котораязапускает прокгамму в ней можно обьявлять переменные и т.д.

	void dealDamage( Cards* _card);
	void CardCast(Cards &card, int bet);
	void EndTurn();
	void EndBattle();
	bool canCast( Cards* _card);
	void mobMove();
	void RestartGame();
	int RandomNum(int x, int y);

	// Save / Load / Stats
	void SaveGame();
	void LoadGame();
	void DeleteSave();
	bool SaveExists() const;
	void CheckSaveFile();
	void SaveStats();
	void LoadStats();
	void InitStatTexts();
	void UpdateStatTexts();
	void LogBattle(const string& msg);

};

