#include "Engine.h"

void Engine::Input()
{
	while (const optional event = window->pollEvent())
	{
		/////////////////////////////////////////// DEMOT∨
		if (event->is<Event::Closed>()) window->close();//когда на крестик нажал игра закроется
		//if (Keyboard::isKeyPressed(Keyboard::Key::Num1)) 
		//{
	
		//	mob->AnimStop();
		//	mob->setPosition({ 1200, 250 });
		//}
		//if (Keyboard::isKeyPressed(Keyboard::Key::Num2))
		//{
		//	mob->AnimStop();
		//	mob->setPosition({ 1200, 250 });

		//}
		//if (Keyboard::isKeyPressed(Keyboard::Key::Num3))
		//{

		//	mob->AnimStop();
		//	mob->setPosition({ 1200, 250 });

		//}

		//проверка кнопок на нажатие
		startBTN.handleEvent(*event, *window);
		statBTN.handleEvent(*event, *window);
		exitBTN.handleEvent(*event, *window);
		toMenuBTN.handleEvent(*event, *window);
		endTurn.handleEvent(*event, *window);
		card.handleEvent(*event, *window);

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
	
	endTurn.setSize(0.8 , 0.8);
	endTurn.setSpriteColor(Color(255,225,0));
	endTurn.setOnClick([this]() {
		endTurn.isPressed = true;
		if (endTurn.isPressed)
		{
			if (endTurn.clock.getElapsedTime() > milliseconds(100))
			{
				EndTurn();
				mobMove();
				endTurn.clock.restart();
				endTurn.isPressed = false;
			}
		}
			
	});

	hpBar.setScale({0.6, 1});
	hpBar.setColor(Color(200,0,0));
	hpBar.setTextOutline(Color::Black, 2.f);

	moveBar.setColor(Color(20,200,40));
	moveBar.setScale({ 0.8, 1 });

	comboBar.setColor(Color(255,200,0));
	comboBar.setScale({ 0.5, 0.5 });

	player.AnimStop();
	player.setPosition({100,250});
	
	mob.AnimStop();
	mob.setPosition({ 1200,250 });

	enemyHpBar.setColor(Color(150, 0, 0));
	enemyHpBar.setTextOutline(Color::Black, 2.f);

	Bet.setSpriteColor(Color(170,120, 50));
	Bet.setTextOutline(Color::Black, 2.f);

	card.setEffect("add 1", IntRect({96,0}, {32,32}));
	card.setEffectPosition({100, 134}, {32, 128});
	card.setAction([this]() {
		if (canCast())
		{
			CardCast(card, static_cast<int>(round(player.getMaxBet() * card.getSliderValue()))); dealDamage(); 

		}
	});


	///////////////////////////////////////////////////////////////// DEMO∧
}

void Engine::Run()
{
	cout << "is start" << endl;
	Clock clock; // инициализировал таймер
	EndBattle();
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
	armorBar.setText(to_string(player.getArm()));
	if (player.getArm() == 0) armorBar.setIsDrawed(false);
	else armorBar.setIsDrawed(true);
	moveBar.setSliderNum(static_cast<float>(player.getMove()) / player.getMaxMove());
	moveBar.setText(to_string(player.getMove()) + "/" + to_string(player.getMaxMove()));
	comboBar.setSliderNum(static_cast<float>(player.getCombo()) / player.getMaxCombo());
	comboBar.setText(to_string(player.getCombo()) + "/" + to_string(player.getMaxCombo()));

	enemyHpBar.setSliderNum(static_cast<float>(mob.getHealth()) / mob.getMaxHealth());
	enemyHpBar.setText(to_string(mob.getHealth()));
	enemyArmorBar.setText(to_string(mob.getArm()));
	if (mob.getArm() == 0) enemyArmorBar.setIsDrawed(false);
	else enemyArmorBar.setIsDrawed(true);

	gameBackground.AnimUpdate(deltaTime);
	player.AnimUpdate(deltaTime);

	bag.setText(to_string(player.getCash()));
	Bet.setText(to_string(_bet));
	card.setSliderText(to_string(static_cast<int>(round(player.getMaxBet()*card.getSliderValue()))));
	
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
		endTurn.setActive(true);

		gameBackground.draw(*window);

		player.draw(*window);
		hpBar.draw(*window);
		armorBar.draw(*window);
		moveBar.draw(*window);
		comboBar.draw(*window);

		mob.draw(*window);
		enemyHpBar.draw(*window);
		enemyArmorBar.draw(*window);

		toMenuBTN.draw(*window);
		card.draw(*window);
		card1.draw(*window);
		card2.draw(*window);
		card3.draw(*window);
		card4.draw(*window);
		bag.draw(*window);
		Bet.draw(*window);
		endTurn.draw(*window);


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
	endTurn.setActive(false);

}

void Engine::dealDamage()
{	
	int dmg = static_cast<int>(round(player.Attack()* (static_cast<int>(round(player.getMaxBet() * card.getSliderValue()))/player.getMinBet())));
	if (dmg == 0) dmg = 1;
	if (mob.getArm() > 0)
	{
		int x = mob.getArm();
		mob.setArm(mob.getArm() - dmg);
		dmg -= x;
		if (mob.getArm() < 0)	mob.setArm(0);
	}
	mob.TakeDamage(dmg);
	if (mob.getHealth() <= 0)
	{
		EndBattle();
		player.LevelUp();
	}
}

void Engine::CardCast(Cards& card, int bet)
{
	int x = player.getCash() - bet;
	_bet += bet;
	player.setCash(x);
	player.setMove(player.getMove() - card.getCostAP());
	player.setCombo(player.getCombo() - card.getCostCP());
}

void Engine::EndTurn()
{
	player.setMove(player.getMaxMove());
}

void Engine::EndBattle()
{
	if (player.getLevel() == 20)	{ cout << "you win\n";	RestartGame(); }
	cout << player.getLevel() << endl;
	if (player.getLevel() <= 5)			 mob = enemys[RandomNum(1, 3) - 1];
	else if (player.getLevel() <= 10)	 mob = enemys[RandomNum(1, 3) - 1]; 
	else if (player.getLevel() <= 15)	 mob = enemys[RandomNum(1, 3) - 1]; 
	else if (player.getLevel() <= 19)	 mob = enemys[RandomNum(1, 3) - 1]; 
	else								 mob = enemys[RandomNum(1, 3) - 1];
	mob.setPosition({ 1200, 250 });
	mob.AnimStop();
	EndTurn();
	player.setCombo(0);
	player.setArm(player.getArmorValue());
	player.setCash(player.getCash() + _bet);
	_bet = 0;

	mob.setHealth(mob.getMaxHealth());
	mob.setArm(mob.getArmorValue());
}

bool Engine::canCast()
{
	return !(player.getCash() - static_cast<int>(round(player.getMaxBet() * card.getSliderValue())) < 0 || player.getMove() - card.getCostAP() < 0 || player.getCombo() - card.getCostCP() < 0);
}

void Engine::mobMove()
{
	_bet += mob.Bet();
	int dmg = mob.Attack();
	if (player.getArm() > 0)
	{
		int x = player.getArm();
		player.setArm(player.getArm() - dmg);
		dmg -= x;
		if (player.getArm() < 0)	player.setArm(0);
	}
	player.TakeDamage(dmg);
	if (player.getHealth() <= 0)	RestartGame();
}

void Engine::RestartGame()
{
	cout << "you lose\n";
	EndBattle();
	player.setLevel(1);
	player.setCash(30);
	player.setHealth(player.getMaxHealth());
}

int Engine::RandomNum(int x, int y)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(x, y);
	return dist(gen);
}
