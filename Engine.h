#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<memory>
#include "AssetManager.h"
#include "Button.h"
#include "Animator.h"
#include "Object.h"
#include "Slider.h"
#include "Creature.h"
#include "ItemList.h"

using namespace sf;
using namespace std;

class Engine
{
	unique_ptr<RenderWindow>  window = make_unique<RenderWindow>(VideoMode({ 1280, 720 }), "SFML works!", Style::Default); //указатель на окно
	Object menuBackground = Object(AssetManager::GetTexture("Sprite/MainMenu.jpg"), IntRect({ 0,0 }, { 1280,720 }), 9, 1, 0, 1.f);// обьявление фона
	Object gameBackground = Object(AssetManager::GetTexture("Sprite/GameBackground.jpg"), IntRect({0,0}, {1280,720}), 9, 1, 0, 1.f);
	Object cutscene = Object(AssetManager::GetTexture("Sprite/Cutscen.jpg"), IntRect({0,0}, {1280,720}), 10, 5, 60);
	bool cutsceneActiv = false;
///////////////////////////////////////////////////////////////// демонстрация ∨∨∨
	// создвание кнопок
	ItemList items;
	Button start = Button({ 700,200 }, "Sprite/square.jpg", "START", "Font/BankGothic.otf", "", Color::Black, 35); //переход на "другую" сцену(просто отрисовка нового фона поверх других)
	Button exitBTN = Button({ 700,400 }, "Sprite/square.jpg", "EXIT", "Font/BankGothic.otf", "", Color::Black, 35); //выход из игры
	Button closeBTN = Button({ 50,50 }, "Sprite/square.jpg", "CL0SE", "Font/BankGothic.otf"); //вернутся в первую сцену
	Button P = Button({ 700,500 }, "Sprite/square.jpg", "Pause", "Font/BankGothic.otf"); // пауза(для теста анимации)
	Button R = Button({ 1000,500 }, "Sprite/square.jpg", "restart", "Font/BankGothic.otf"); //рестарт(для теста анимации)
	bool sceneActiv = false;//состояние для сцены(вкл\выкл)

	//вторая сцена для наглядности работы кнопок

	int hp = 100;
	Texture sq = AssetManager::GetTexture("Sprite/square.jpg");
	Text* hpText;
	Sprite* hpBack;
	Sprite* hpBar;

	Button plus = Button({ 200,500 }, "Sprite/square.jpg", "+", "Font/BankGothic.otf"); // пауза(для теста анимации)
	Button minus = Button({ 400,500 }, "Sprite/square.jpg", "-", "Font/BankGothic.otf"); //рестарт(для теста анимации)
	Slider slider = Slider({ 300, 10 }, "Sprite/square.jpg", "", "Font/BankGothic.otf");
	
	Object fire = Object(AssetManager::GetTexture("Sprite/Player.png"), IntRect({ 0,0 }, { 256,256 }), 10, 1, 100);
	Creature mob = Creature("none", 1, 10, 1, 0, 3, 0, 2.f, items.weapons[0],items.armors[0], AssetManager::GetTexture("Sprite/Player.png"), IntRect({ 0,0 }, { 256,256 }), 10, 1, 100);
	///////////////////////////////////////////////////////////////// демонстрация ∧∧∧

	void Input(); // обработка нажатий и ввода с клавиатуры
	void Update(Time const& deltaTime); // цикл наподобие while(true), deltaTime - это время, тут писать логику зависящую от времени
	void Draw();//ортисовка объектов, всякое говно не связанное с отрисовкой не пихать
public:
	Engine(); //конструктор, ничего не требует

	void Run(); // функция котораязапускает прокгамму в ней можно обьявлять переменные и т.д.
};

