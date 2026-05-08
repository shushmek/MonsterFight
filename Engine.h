#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<memory>
#include "AssetManager.h"
#include "Button.h"
#include "Object.h"
#include "Slider.h"
#include "Creature.h"
#include "ItemList.h"
#include "Player.h"

using namespace sf;
using namespace std;

class Engine
{
	unique_ptr<RenderWindow>  window = make_unique<RenderWindow>(VideoMode({ 1280, 720 }), "SFML works!", Style::Default); //указатель на окно
///////////////////////////////////////////////////////////////// DEMO ∨∨∨
	enum State {Menu, Game, Statistic};
	State state = State::Menu;
	ItemList items;
	//MENU
	Object menuBackground = Object(AssetManager::GetTexture("Sprite/MainMenu.jpg"), IntRect({ 0,0 }, { 1280,720 }), 9, 1, 100);
	Object StartCutscene = Object(AssetManager::GetTexture("Sprite/Cutscen.jpg"), IntRect({0,0}, {1280,720}), 10, 5, 60);
	Button startBTN = Button({ 100,200 }, "Sprite/btn.png", "START", "Font/BankGothic.otf", "", Color::White, 45); //переход на "другую" сцену(просто отрисовка нового фона поверх других)
	Button statBTN = Button({ 100,350 }, "Sprite/btn.png", "STATISTICS", "Font/BankGothic.otf", "", Color::White, 35); //переход на "другую" сцену(просто отрисовка нового фона поверх других)
	Button exitBTN = Button({ 100,500 }, "Sprite/btn.png", "EXIT", "Font/BankGothic.otf", "", Color::White, 45); //выход из игры
	//Game
	Object gameBackground = Object(AssetManager::GetTexture("Sprite/GameBackground.jpg"), IntRect({0,0}, {1280,720}), 9, 1, 100);

	Button toMenuBTN = Button({ 50,50 }, "Sprite/btn.png", "CL0SE", "Font/BankGothic.otf", "", Color::White, 45); //вернутся в первую сцену
	
	Player mob = Player("none", 1, 100, 1, 0, 3, 0, 2.f, 2, 6, 30, items.weapons[1], items.armors[1], AssetManager::GetTexture("Sprite/Player.png"), IntRect({ 0,0 }, { 256,256 }), 10, 1, 100);

	Slider hpBar = Slider({ 10,640 }, "Sprite/SliderBack.png", AssetManager::GetTexture("Sprite/SliderFront.png"), "", "Font/BankGothic.otf");
	///////////////////////////////////////////////////////////////// DEMO ∧∧∧

	void Input(); // обработка нажатий и ввода с клавиатуры
	void Update(Time const& deltaTime); // цикл наподобие while(true), deltaTime - это время, тут писать логику зависящую от времени
	void Draw();//ортисовка объектов, всякое говно не связанное с отрисовкой не пихать
	void BTNOff(); // все кнопки не активны
public:
	Engine(); //конструктор, ничего не требует

	void Run(); // функция котораязапускает прокгамму в ней можно обьявлять переменные и т.д.
};

