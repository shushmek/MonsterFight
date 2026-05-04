#include "Engine.h"

void Engine::Input()
{
	while (const optional event = window->pollEvent())
	{
		if (event->is<Event::Closed>()) window->close();//когда на крестик нажал игра закроется
		/////////////////////////////////////////// DEMOT∨
		//проверка кнопок на нажатие
		StartBTN.handleEvent(*event, *window);
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
	
	StartBTN.setOnClick([this]() {StartCutscene._anim->play();}); //задал лямбда функцию, при нажатии "открывает" сцену
	
	exitBTN.setSpriteColor(Color(200,0,0));
	exitBTN.setOnClick([this] {window->close();});

	//GAME
	toMenuBTN.setOnClick([this]() {state = State::Menu;});
	toMenuBTN.setSpriteColor(Color(200, 0, 0));
	
	mob.AnimStop();
	mob.setPosition({200,300});

	///////////////////////////////////////////////////////////////// DEMO∧
}

void Engine::Run()
{
	cout << "is start" << endl;
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
		StartBTN.setActive(true);
		exitBTN.setActive(true);

		menuBackground.draw(*window);
		StartBTN.draw(*window);
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
	StartBTN.setActive(false);
	exitBTN.setActive(false);
	toMenuBTN.setActive(false);
}
