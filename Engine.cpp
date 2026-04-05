#include "Engine.h"
#include "Engine.h"

void Engine::Input()
{
	while (const optional event = window->pollEvent())
	{
		if (event->is<Event::Closed>()) window->close();
		if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) window->close();
	}
}

void Engine::Update(Time const& deltaTime)
{
	
}

void Engine::Draw()
{
	window->clear();
	window->draw(background);
	btn.draw(*window);
	window->display();
}

Engine::Engine()
{
	background.setTexture(&AssetManager::GetTexture("Sprite/Background.jpg"));
}

void Engine::Run()
{
	cout << "is start" << endl;
	btn.setSize(2, 1);

	Clock clock;


	while (window->isOpen())
	{
		Time dt = clock.restart();
		Input();
		Update(dt);
		Draw();
	}
}S
