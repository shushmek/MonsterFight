#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<memory>
#include "AssetManager.h"
#include "Button.h"
#include "Animator.h"

using namespace sf;
using namespace std;

class Engine
{
	unique_ptr<RenderWindow>  window = make_unique<RenderWindow>(VideoMode({ 1280, 720 }), "SFML works!", Style::Default); //указатель на окно
	RectangleShape background = RectangleShape({ 1280, 720 }); // обьявление фона
	///////////////////////////////////////////////////////////////// демонстрация ∨∨∨
	// создвание кнопок
	Button btn = Button({ 700,200 }, "Sprite/square.jpg", "START", "Font/BankGothic.otf", "", Color::Black, 35); //переход на "другую" сцену(просто отрисовка нового фона поверх других)
	Button exitBTN = Button({ 700,400 }, "Sprite/square.jpg", "EXIT", "Font/BankGothic.otf", "", Color::Black, 35); //выход из игры
	Button closeBTN = Button({ 50,50 }, "Sprite/square.jpg", "CL0SE", "Font/BankGothic.otf"); //вернутся в первую сцену
	Button P = Button({ 300,500 }, "Sprite/square.jpg", "Pause", "Font/BankGothic.otf"); // пауза(для теста анимации)
	Button R = Button({ 600,500 }, "Sprite/square.jpg", "restart", "Font/BankGothic.otf"); //рестарт(для теста анимации)
	
	//вторая сцена для наглядности работы кнопок
	RectangleShape scene = RectangleShape({ 1280, 720 }); //задник сцены
	bool sceneActiv = false;//состояние для сцены(вкл\выкл)

	Texture fireTexture = AssetManager::GetTexture("Sprite/fire.png"); //текстура спрайтшита(спрайт с кадрами для аниамции) для огня
	Sprite* fire; //спрайт огня
	Animator* fireAnim;//агимация огня
	///////////////////////////////////////////////////////////////// демонстрация ∧∧∧

	void Input(); // обработка нажатий и ввода с клавиатуры
	void Update(Time const& deltaTime); // цикл наподобие while(true), deltaTime - это время, тут писать логику зависящую от времени
	void Draw();//ортисовка объектов, всякое говно не связанное с отрисовкой не пихать
public:
	Engine(); //конструктор, ничего не требует

	void Run(); // функция котораязапускает прокгамму в ней можно обьявлять переменные и т.д.
};

