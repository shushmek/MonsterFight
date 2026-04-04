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
	window->display();
}

Engine::Engine()
{
	backgroundTexture.loadFromFile("Sprite/lavash.jpg");
	background.setTexture(&backgroundTexture);
}

void Engine::Run()
{
	Clock clock;
	while (window->isOpen())
	{
		Time dt = clock.restart();
		Input();
		Update(dt);
		Draw();

	}

}
