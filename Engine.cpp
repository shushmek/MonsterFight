#include "Engine.h"

void Engine::Input()
{
	while (const optional event = window->pollEvent())
	{
		/////////////////////////////////////////// DEMOT∨
		if (event->is<Event::Closed>()) window->close();//когда на крестик нажал игра закроется
		if (Keyboard::isKeyPressed(Keyboard::Key::W)) 
		{
			if (mob.getHealth() < mob.getMaxHealth())
				mob.TakeDamage(-1);
			else	
				mob.setHealth(mob.getMaxHealth());
			
			
			hpBar.setSliderNum(static_cast<float>(mob.getHealth()) / mob.getMaxHealth());
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::S)) 
		{
			if (mob.getHealth() > 0) 
				mob.TakeDamage(1);
			else
				mob.setHealth(0);

			hpBar.setSliderNum(static_cast<float>(mob.getHealth()) / mob.getMaxHealth());

		}
		//проверка кнопок на нажатие
		startBTN.handleEvent(*event, *window);
		exitBTN.handleEvent(*event, *window);
		toMenuBTN.handleEvent(*event, *window);
		/////////////////////////////////////////// DEMOT∧
	}
}

Engine::Engine()
{
	///////////////////////////////////////////////////////////////// DEMO∨
	//MENU
	StartCutscene.AnimSetLoop(false);
	StartCutscene.AnimSetOnFinished([this]() {state = State::Game;});
	StartCutscene.AnimStop();
	
	startBTN.setOnClick([this]() {StartCutscene._anim->play();}); //задал лямбда функцию, при нажатии "открывает" сцену
	startBTN.setSpriteColor(Color(180,86,140));
	
	statBTN.setOnClick([this]() {state = State::Statistic;}); //задал лямбда функцию, при нажатии "открывает" сцену
	statBTN.setSpriteColor(Color(180, 86, 140));

	exitBTN.setSpriteColor(Color(222, 32, 32));
	exitBTN.setOnClick([this] {window->close();});

	//GAME
	toMenuBTN.setOnClick([this]() {state = State::Menu;});
	toMenuBTN.setSpriteColor(Color(222, 32, 32));
	toMenuBTN.setSize(0.6, 0.6);
	
	hpBar.setScale({0.6, 1});

	mob.AnimStop();
	mob.setPosition({200,300});

	///////////////////////////////////////////////////////////////// DEMO∧
}

void Engine::Run()
{
	cout << "is start" << endl;
	Clock clock; // инициализировал таймер
	hpBar.setColor(Color(200,0,0));
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
	///////////////////////////////////////////////////////////////// DEMO∨
	//MENU
	menuBackground.AnimUpdate(deltaTime);
	StartCutscene.AnimUpdate(deltaTime);
	//GAME
	gameBackground.AnimUpdate(deltaTime);
	mob.AnimUpdate(deltaTime);
	///////////////////////////////////////////////////////////////// DEMO∧

}

void Engine::Draw()
{
	window->clear();
	///////////////////////////////////////////////////////////////// DEMO∨
	switch (state)
	{
		//MENU
	case State::Menu:
		BTNOff();
		startBTN.setActive(true);
		statBTN.setActive(true);
		exitBTN.setActive(true);

		menuBackground.draw(*window);
		startBTN.draw(*window);
		statBTN.draw(*window);
		exitBTN.draw(*window);
		if (StartCutscene.AnimGetPlay())
			StartCutscene.draw(*window);
		break;
		//GAME
	case State::Game:
		BTNOff();
		mob.AnimPlay();
		toMenuBTN.setActive(true);

		gameBackground.draw(*window);
		mob.draw(*window);
		hpBar.draw(*window);
		toMenuBTN.draw(*window);
		break;
		//Statistick
	case State::Statistic:
		break;
	default: state = State::Menu;
		break;
	}
	///////////////////////////////////////////////////////////////// DEMO∧
	window->display();
}

void Engine::BTNOff()
{
	startBTN.setActive(false);
	exitBTN.setActive(false);
	toMenuBTN.setActive(false);
	hpBar.setActive(false);
	statBTN.setActive(false);

}
