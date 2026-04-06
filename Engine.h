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
	AssetManager manager;
	unique_ptr<RenderWindow>  window = make_unique<RenderWindow>(VideoMode({ 1280, 720 }), "SFML works!", Style::Default);
	RectangleShape background = RectangleShape({ 1280, 720 });
	///////////////////////////////////////////////////////////////// BUTTON FOR TEST
	Button btn = Button({ 700,200 }, "Sprite/square.jpg", "START", "Font/BankGothic.otf", "", Color::Black, 35);
	Button exitBTN = Button({ 700,400 }, "Sprite/square.jpg", "EXIT", "Font/BankGothic.otf", "", Color::Black, 35);
	Button closeBTN = Button({ 50,50 }, "Sprite/square.jpg", "CL0SE", "Font/BankGothic.otf");
	RectangleShape scene = RectangleShape({ 1280, 720 });
	bool sceneActiv = false;

	Button P = Button({ 300,500 }, "Sprite/square.jpg", "Pause", "Font/BankGothic.otf");
	Button R = Button({ 600,500 }, "Sprite/square.jpg", "restart", "Font/BankGothic.otf");

	Texture fireTexture = AssetManager::GetTexture("Sprite/fire.png");
	Sprite* fire;
	Animator* fireAnim;// = Animator(*fire, 100);
	///////////////////////////////////////////////////////////////// 

	void Input();
	void Update(Time const& deltaTime);
	void Draw();
public:
	Engine();

	void Run();

};

