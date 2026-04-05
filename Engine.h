#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<memory>
#include "AssetManager.h"
#include "Button.h"


using namespace sf;
using namespace std;

class Engine
{
	AssetManager manager;
	unique_ptr<RenderWindow>  window = make_unique<RenderWindow>(VideoMode({ 1280, 720 }), "SFML works!", Style::Default);
	RectangleShape background = RectangleShape(Vector2f({ 1280, 720 }));
	
	Button btn = Button({700,200}, "Sprite/square.jpg", "text button", "Font/BankGothic.otf","", Color::Black, 35);

	void Input();
	void Update(Time const& deltaTime);
	void Draw();
public:
	Engine();

	void Run();

};

