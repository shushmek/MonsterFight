#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include "Button.h"
#include "Object.h"
#include "Slider.h"
#include "Creature.h"
#include "ItemList.h"
#include "Player.h"
#include "Cards.h"
#include "Bet.h"
#include "GameLog.h"
#include "SaveSystem.h"

using namespace sf;
using namespace std;

class Engine
{
	unique_ptr<RenderWindow> window = make_unique<RenderWindow>(VideoMode({ 1280, 720 }), "SFML works!", Style::Default);

	enum State { Menu, Game, Statistic, Logs };
	State state = State::Menu;
	ItemList _items;
	ItemList items;

	Enemy* enemys = new Enemy[]{
		Enemy("Goblin", 1, 25, 1, 0, 3, 1, 2.f, 2, 6, items.weapons[1], items.armors[1], AssetManager::GetTexture("Sprite/Goblin.png"), IntRect({ 0,0 }, { 256,256 }), 10, 1, 100),		//0
		Enemy("Goblin", 1, 15, 5, 0, 3, 1, 2.f, 2, 6, items.weapons[0], items.armors[1], AssetManager::GetTexture("Sprite/Player.png"), IntRect({ 0,0 }, { 256,256 }), 10, 1, 100),		//1
		Enemy("Goblin", 1, 20, 2, 0, 3, 1, 2.f, 2, 6, items.weapons[1], items.armors[1], AssetManager::GetTexture("Sprite/Goblin.png"), IntRect({ 0,0 }, { 256,256 }), 10, 1, 100)
	};
	//MENU
	Object menuBackground = Object(AssetManager::GetTexture("Sprite/MainMenu.jpg"), IntRect({ 0,0 }, { 1280,720 }), 9, 1, 100);
	Object StartCutscene = Object(AssetManager::GetTexture("Sprite/Cutscen.jpg"), IntRect({0,0}, {1280,720}), 10, 5, 60);
	Button startBTN = Button({ 100,200 }, "Sprite/btn.png", "START", "Font/BankGothic.otf", "", Color::White, 45); //переход на "другую" сцену(просто отрисовка нового фона поверх других)
	Button statBTN = Button({ 100,350 }, "Sprite/btn.png", "STATISTICS", "Font/BankGothic.otf", "", Color::White, 35); //переход на "другую" сцену(просто отрисовка нового фона поверх других)
	Button exitBTN = Button({ 100,500 }, "Sprite/btn.png", "EXIT", "Font/BankGothic.otf", "", Color::White, 45); //выход из игры
  Button menuLoadBTN = Button({ 100,200 }, "Sprite/btn.png", "LOAD", "Font/BankGothic.otf", "", Color::White, 45);
	Button logsBTN = Button({ 100,440 }, "Sprite/btn.png", "LOGS", "Font/BankGothic.otf", "", Color::White, 45);
  
	//Game
	int _bet = 0;

	Object gameBackground = Object(AssetManager::GetTexture("Sprite/GameBackground.jpg"), IntRect({0,0}, {1280,720}), 9, 1, 100);

	Button endTurn = Button({ 1065,580 }, "Sprite/btn.png", "end turn", "Font/BankGothic.otf", "", Color::White, 45);

	Button toMenuBTN = Button({ 50,50 }, "Sprite/btn.png", "CL0SE", "Font/BankGothic.otf", "", Color::White, 45); //вернутся в первую сцену
	
	Cards card = Cards(Cards::Attack, "Default", 1, 0, 0, 0, { 310, 500 }, "Sprite/cards.png", to_string(items.weapons[1].getDamage()), "Font/BankGothic.otf", "");
	Button card1 = Button({ 470, 510 }, "Sprite/_card.jpg", "", "Font/BankGothic.otf", "");
	Button card2 = Button({ 620, 510 }, "Sprite/_card.jpg", "", "Font/BankGothic.otf", "");
	Button card3 = Button({ 770, 510 }, "Sprite/_card.jpg", "", "Font/BankGothic.otf", "");
	Button card4 = Button({ 920, 510 }, "Sprite/_card.jpg", "", "Font/BankGothic.otf", "");
	Button bag = Button({ 10, 510 }, "Sprite/bag.png", "100", "Font/BankGothic.otf", "");
	Button Bet = Button({ 510, 10 }, "Sprite/square.jpg", "999999", "Font/BankGothic.otf", "");

	Player player = Player("player", 1, 100, 1, 0, 3, 1, 2.f, 2, 6, 30, 3, _items.weapons[1], _items.armors[1], AssetManager::GetTexture("Sprite/Player.png"), IntRect({ 0,0 }, { 256,256 }), 10, 1, 100);
	Slider hpBar = Slider({ 10,640 }, "Sprite/SliderBack.png", AssetManager::GetTexture("Sprite/SliderFront.png"), "", "Font/BankGothic.otf");
	Button armorBar = Button({ 250, 640 }, "Sprite/_arm.png", "", "Font/BankGothic.otf", "");
	Slider moveBar = Slider({ 10,10 }, "Sprite/SliderBack.png", AssetManager::GetTexture("Sprite/SliderFront.png"), "", "Font/BankGothic.otf");
	Slider comboBar = Slider({ 10,74 }, "Sprite/SliderBack.png", AssetManager::GetTexture("Sprite/SliderFront.png"), "", "Font/BankGothic.otf");

	Enemy mob = enemys[0];
	Slider enemyHpBar = Slider({ 950,150 }, "Sprite/square.jpg", "999", "Font/BankGothic.otf");
	Button enemyArmorBar = Button({ 900, 150 }, "Sprite/_arm.png", "", "Font/BankGothic.otf", "");


	//STATISTIC
	Object statBackground = Object(AssetManager::GetTexture("Sprite/Background.jpg"), IntRect({ 0,0 }, { 1280,720 }), 1, 1, 100);
	
	///////////////////////////////////////////////////////////////// DEMO ∧∧∧

	GameStats stats;
	GameLog logger;
	int currentWeaponIndex = 1;
	int currentArmorIndex = 1;

	bool keyWDown = false;
	bool keySDown = false;
	bool keyF3Down = false;
	bool keyF4Down = false;
	bool keyF5Down = false;
	bool keyF9Down = false;
	bool keyEscDown = false;

	Button saveBTN = Button({ 50,120 }, "Sprite/btn.png", "SAVE", "Font/BankGothic.otf", "", Color::White, 45);
	Button gameLoadBTN = Button({ 50,190 }, "Sprite/btn.png", "LOAD", "Font/BankGothic.otf", "", Color::White, 45);

public:
	void Input();
	void Update(Time const& deltaTime);
	void Draw();
	void BTNOff();
	void HandleHotkeys();
	void ChangeHealth(int delta);
	void SetState(State nextState);
	void SaveGame();
	void LoadGame();
	SaveData MakeSaveData();
	bool ApplySaveData(SaveData const& data, string& error);
	void DrawStatistics();
	void DrawLogs();
	void DrawText(string const& text, Vector2f const& position, unsigned int size, Color const& color = Color::White);
	void LogEvent(string const& message);

	void Run(); // функция котораязапускает прокгамму в ней можно обьявлять переменные и т.д.
	void dealDamage();
	void CardCast(Cards &card, int bet);
	void EndTurn();
	void EndBattle();
	bool canCast();
	void mobMove();
	void RestartGame();
	int RandomNum(int x, int y);

};
