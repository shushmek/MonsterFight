#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<memory>
#include "AssetManager.h"

using namespace sf;
using namespace std;

class Engine
{
	AssetManager manager;
	unique_ptr<RenderWindow>  window = make_unique<RenderWindow>(VideoMode({ 1280, 720 }), "SFML works!", Style::Default);
	RectangleShape background = RectangleShape(Vector2f({1280, 720}));
	Texture backgroundTexture;
	void Input();
	void Update(Time const & deltaTime);
	void Draw();
public:
	Engine();

	void Run();

};

