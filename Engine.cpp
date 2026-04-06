#include "Engine.h"
#include "Engine.h"

void Engine::Input()
{
	while (const optional event = window->pollEvent())
	{
		if (event->is<Event::Closed>()) window->close();
		/////////////////////////////////////////// BUTTON FOR TEST∨
		btn.handleEvent(*event, *window);
		exitBTN.handleEvent(*event, *window);
		closeBTN.handleEvent(*event, *window);
		P.handleEvent(*event, *window);
		R.handleEvent(*event, *window);
		/////////////////////////////////////////// BUTTON FOR TEST∧
	}
}



Engine::Engine()
{
	background.setTexture(&AssetManager::GetTexture("Sprite/Background.jpg"));
	fire = new Sprite(fireTexture);
	fireAnim = new Animator(*fire, IntRect({ 0,0 }, { 32,48 }), 8, 100);
	fire->setPosition({ 564, 200 });
	fire->setScale({ 4,4 });
}

void Engine::Run()
{
	cout << "is start" << endl;
	///////////////////////////////////////////////////////////////// BUTTON FOR TEST∨
	btn.setSize(2, 1);
	btn.setSpriteColor(Color(255, 0, 0));
	btn.setOnClick([this]() {btn.isPressed = true;  sceneActiv = true;});
	P.setSize(2, 1);
	P.setOnClick([this]() {
		P.isPressed = true;
		if (fireAnim->getPlay()) fireAnim->pause();
		else fireAnim->play();});
	R.setSize(2, 1);
	R.setOnClick([this]() {R.isPressed = true; fireAnim->reset();});

	exitBTN.setSpriteColor(Color::Red);
	exitBTN.setSize(2, 1);
	exitBTN.setOnClick([this] {window->close();});
	closeBTN.setSpriteColor(Color(200, 0, 0));
	closeBTN.setOnClick([this] {sceneActiv = false;});
	scene.setTexture(&AssetManager::GetTexture("Sprite/lavash.jpg"));

	///////////////////////////////////////////////////////////////// BUTTON FOR TEST∧
	Clock clock;


	while (window->isOpen())
	{
		Time dt = clock.restart();
		Input();
		Update(dt);
		Draw();
	}
}

void Engine::Update(Time const& deltaTime)
{
	///////////////////////////////////////////////////////////////// BUTTON FOR TEST∨
	if (btn.isPressed)
	{
		btn.setSpriteColor(Color::Yellow);
		if (btn.clock.getElapsedTime() > milliseconds(100))
		{
			btn.clock.restart();
			btn.isPressed = false;
		}
		sceneActiv = true;
	}
	else btn.setSpriteColor(Color::White);

	if (P.isPressed)
	{
		P.setSpriteColor(Color::Yellow);
		if (P.clock.getElapsedTime() > milliseconds(100))
		{
			P.clock.restart();
			P.isPressed = false;
		}
	}
	else P.setSpriteColor(Color::White);

	if (R.isPressed)
	{
		R.setSpriteColor(Color::Yellow);
		if (R.clock.getElapsedTime() > milliseconds(100))
		{
			R.clock.restart();
			R.isPressed = false;
		}
	}
	else R.setSpriteColor(Color::White);

	if (closeBTN.isPressed)
	{
		closeBTN.setSpriteColor(Color::Red);
		if (closeBTN.clock.getElapsedTime() > milliseconds(100))
		{
			closeBTN.clock.restart();
			closeBTN.isPressed = false;
		}
		sceneActiv = false;
	}
	else closeBTN.setSpriteColor(Color(200, 0, 0));

	fireAnim->update(deltaTime);
	///////////////////////////////////////////////////////////////// BUTTON FOR TEST∧

}

void Engine::Draw()
{
	window->clear();
	window->draw(background);
	///////////////////////////////////////////////////////////////// BUTTON FOR TEST∨
	if (sceneActiv)
	{
		btn.setEnable(false);
		exitBTN.setEnable(false);

		window->draw(scene);
		window->draw(*fire);
		P.draw(*window);
		R.draw(*window);
		closeBTN.draw(*window);
	}
	else {
		btn.setEnable(true);
		exitBTN.setEnable(true);
		btn.draw(*window);
		exitBTN.draw(*window);
	}
	///////////////////////////////////////////////////////////////// BUTTON FOR TEST∧
	window->display();
}