#include "Engine.h"

void Engine::Input()
{
	while (const optional event = window->pollEvent())
	{
		/////////////////////////////////////////// DEMOT∨
		if (event->is<Event::Closed>()) window->close();//когда на крестик нажал игра закроется
		if (Keyboard::isKeyPressed(Keyboard::Key::W)) 
		{
			if (player.getHealth() < player.getMaxHealth())
				player.TakeDamage(-1);
			else	
				player.setHealth(player.getMaxHealth());

			mob.TakeDamage(-1);
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::S)) 
		{
			if (player.getHealth() > 0) 
				player.TakeDamage(1);
			else
				player.setHealth(0);
			mob.TakeDamage(1);
		}
		//проверка кнопок на нажатие
		startBTN.handleEvent(*event, *window);
		statBTN.handleEvent(*event, *window);
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
	hpBar.setColor(Color(200,0,0));
	hpBar.setTextOutline(Color::Black);

	moveBar.setColor(Color(20,200,40));
	moveBar.setScale({ 0.8, 1 });

	comboBar.setColor(Color(255,200,0));
	comboBar.setScale({ 0.5, 0.5 });

	player.AnimStop();
	player.setPosition({100,250});
	
	mob.AnimStop();
	mob.setPosition({ 1200,250 });

	enemyHpBar.setColor(Color(150, 0, 0));

	Bet.setSpriteColor(Color(170,120, 50));
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
	hpBar.setSliderNum(static_cast<float>(player.getHealth()) / player.getMaxHealth());
	hpBar.setText(to_string(player.getHealth()));
	moveBar.setSliderNum(static_cast<float>(player.getMove()) / player.getMaxMove());
	comboBar.setSliderNum(static_cast<float>(player.getCombo()) / player.getMaxCombo());

	enemyHpBar.setSliderNum(static_cast<float>(mob.getHealth()) / mob.getMaxHealth());
	enemyHpBar.setText(to_string(mob.getHealth()));

	gameBackground.AnimUpdate(deltaTime);
	player.AnimUpdate(deltaTime);
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
		toMenuBTN.setPosition({ 1110,10 });
		BTNOff();
		player.AnimPlay();
		mob.AnimPlay();
		toMenuBTN.setActive(true);

		gameBackground.draw(*window);

		player.draw(*window);
		moveBar.draw(*window);
		hpBar.draw(*window);
		comboBar.draw(*window);

		mob.draw(*window);
		enemyHpBar.draw(*window);

		toMenuBTN.draw(*window);
		card.draw(*window);
		card1.draw(*window);
		card2.draw(*window);
		card3.draw(*window);
		card4.draw(*window);
		bag.draw(*window);
		Bet.draw(*window);


		break;
		//STATISTIC
	case State::Statistic:
		BTNOff();
		toMenuBTN.setPosition({ 50,50 });
		toMenuBTN.setActive(true);

		statBackground.draw(*window);
		toMenuBTN.draw(*window);
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
