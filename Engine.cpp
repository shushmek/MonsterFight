#include "Engine.h"

void Engine::Input()
{
	while (const optional event = window->pollEvent())
	{
		if (event->is<Event::Closed>()) window->close();//когда на крестик нажал игра закроется
		/////////////////////////////////////////// BUTTON FOR TEST∨
		//проверка кнопок на нажатие
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
	background.setTexture(&AssetManager::GetTexture("Sprite/Background.jpg")); //задал текстуру заднику
	fire = new Sprite(fireTexture); //задал текстуру для спрайта
	fireAnim = new Animator(*fire, IntRect({ 0,0 }, { 32,48 }), 8, 50); //задал настройки анимации
	fire->setPosition({ 564, 200 }); // задал положение спрайта
	fire->setScale({ 4,4 }); // задал размер спрайта
}

void Engine::Run()
{
	cout << "is start" << endl;
	///////////////////////////////////////////////////////////////// BUTTON FOR TEST∨
	btn.setSize(2, 1); // задал размер кнопки
	btn.setSpriteColor(Color(255, 0, 0)); // задал цвет кнопки
	btn.setOnClick([this]() {btn.isPressed = true;  sceneActiv = true;}); //задал лямбда функцию, при нажатии "открывает" сцену
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
	Clock clock; // инициализировал таймер


	while (window->isOpen())//условие работы программы(работает пока открыто окно)
	{
		Time dt = clock.restart(); //переменная изменения времени
		Input();
		Update(dt);
		Draw();
	}
}

void Engine::Update(Time const& deltaTime)
{
	///////////////////////////////////////////////////////////////// BUTTON FOR TEST∨
	//---------------------------------------------------------этот блок для красивого нажатия кнопки + событие
	if (btn.isPressed)
	{
		btn.setSpriteColor(Color::Yellow);
		if (btn.clock.getElapsedTime() > milliseconds(100))
		{
			btn.clock.restart(); 
			btn.isPressed = false;
		}
		sceneActiv = true; //событие, конкретно тут "открытие" сцены
	}
	else btn.setSpriteColor(Color::White); 
	//---------------------------------------------------------
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

	fireAnim->update(deltaTime);//тут анимация запускается
	///////////////////////////////////////////////////////////////// BUTTON FOR TEST∧

}

void Engine::Draw()
{
	window->clear();
	window->draw(background);
	///////////////////////////////////////////////////////////////// BUTTON FOR TEST∨
	//отрисовка обЪектов, если сцена(2) активна то рисуется она, иначе первая P.s.(по хорошему сделать состояния через switch, но для примера пойдет)
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
