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
#include "GameLog.h"
#include "SaveSystem.h"

using namespace sf;
using namespace std;

class Engine
{
	unique_ptr<RenderWindow> window = make_unique<RenderWindow>(VideoMode({ 1280, 720 }), "SFML works!", Style::Default);

	enum State { Menu, Game, Statistic, Logs };
	State state = State::Menu;

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

	ItemList items;

	Object menuBackground = Object(AssetManager::GetTexture("Sprite/MainMenu.jpg"), IntRect({ 0,0 }, { 1280,720 }), 9, 1, 100);
	Object StartCutscene = Object(AssetManager::GetTexture("Sprite/Cutscen.jpg"), IntRect({ 0,0 }, { 1280,720 }), 10, 5, 60);
	Button startBTN = Button({ 100,80 }, "Sprite/btn.png", "START", "Font/BankGothic.otf", "", Color::White, 45);
	Button menuLoadBTN = Button({ 100,200 }, "Sprite/btn.png", "LOAD", "Font/BankGothic.otf", "", Color::White, 45);
	Button statBTN = Button({ 100,320 }, "Sprite/btn.png", "STATISTICS", "Font/BankGothic.otf", "", Color::White, 35);
	Button logsBTN = Button({ 100,440 }, "Sprite/btn.png", "LOGS", "Font/BankGothic.otf", "", Color::White, 45);
	Button exitBTN = Button({ 100,560 }, "Sprite/btn.png", "EXIT", "Font/BankGothic.otf", "", Color::White, 45);

	Object gameBackground = Object(AssetManager::GetTexture("Sprite/GameBackground.jpg"), IntRect({ 0,0 }, { 1280,720 }), 9, 1, 100);
	Button toMenuBTN = Button({ 50,50 }, "Sprite/btn.png", "MENU", "Font/BankGothic.otf", "", Color::White, 45);
	Button saveBTN = Button({ 50,120 }, "Sprite/btn.png", "SAVE", "Font/BankGothic.otf", "", Color::White, 45);
	Button gameLoadBTN = Button({ 50,190 }, "Sprite/btn.png", "LOAD", "Font/BankGothic.otf", "", Color::White, 45);

	Player mob = Player("none", 1, 100, 1, 0, 3, 0, 2.f, 2, 6, 30, items.weapons[1], items.armors[1], AssetManager::GetTexture("Sprite/Player.png"), IntRect({ 0,0 }, { 256,256 }), 10, 1, 100);
	Slider hpBar = Slider({ 10,640 }, "Sprite/SliderBack.png", AssetManager::GetTexture("Sprite/SliderFront.png"), "", "Font/BankGothic.otf");

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

public:
	Engine();
	void Run();
};
