#include "Engine.h"

void Engine::Input()
{
	while (const optional event = window->pollEvent())
	{
		if (event->is<Event::Closed>()) window->close();//когда на крестик нажал игра закроется
		/////////////////////////////////////////// BUTTON FOR TEST∨
		//проверка кнопок на нажатие
		start.handleEvent(*event, *window);
		exitBTN.handleEvent(*event, *window);
		closeBTN.handleEvent(*event, *window);
		P.handleEvent(*event, *window);
		R.handleEvent(*event, *window);
		plus.handleEvent(*event, *window);
		minus.handleEvent(*event, *window);
		slider.handleEvent(*event, *window);
		/////////////////////////////////////////// BUTTON FOR TEST∧
	}
}

Engine::Engine()
{
	///////////////////////////////////////////////////////////////// BUTTON FOR TEST∨
	fire.setPosition({ 864, 250 });

	hpText = new Text(AssetManager::GetFont("Font/BankGothic.otf"));
	hpText->setPosition({ 200, 100 });


	hpBack = new Sprite(sq);
	hpBack->setPosition({ 200, 300 });
	hpBack->setScale({ 2, 1 });

	hpBar = new Sprite(sq);
	hpBar->setScale({ 2,1 });
	hpBar->setPosition({ 210, 290 });

	hpBack->setColor(Color(100, 0, 0));
	hpBar->setColor(Color(220, 0, 0));

	plus.setOnClick([this]() {hp += 1; plus.isPressed = true; if (hp > 100) hp = 100; hpBar->setScale({ (static_cast<float>(hp) * 2 / 100),1 });});
	minus.setOnClick([this]() {hp -= 1; minus.isPressed = true; if (hp < 0) hp = 0; hpBar->setScale({ (static_cast<float>(hp) * 2 / 100),1 });});

	start.setSize(2, 1); // задал размер кнопки
	start.setSpriteColor(Color(255, 0, 0)); // задал цвет кнопки
	start.setOnClick([this]() {start.isPressed = true;  cutsceneActiv = true; cutscene._anim->play();}); //задал лямбда функцию, при нажатии "открывает" сцену
	P.setSize(2, 1);
	P.setOnClick([this]() {
		P.isPressed = true;
		if (fire.AnimGetPlay()) fire.AnimPause();
		else fire.AnimPlay();});
	R.setSize(2, 1);
	R.setOnClick([this]() {R.isPressed = true; fire.AnimReset();});

	exitBTN.setSpriteColor(Color::Red);
	exitBTN.setSize(2, 1);
	exitBTN.setOnClick([this] {window->close();});
	closeBTN.setSpriteColor(Color(200, 0, 0));
	closeBTN.setOnClick([this] {sceneActiv = false;});
	cutscene._anim->setLoop(false);
	cutscene._anim->setOnFinished([this]() {cutsceneActiv = false; cutscene.AnimStop(); sceneActiv = true;});
	slider.setScale({ 5, 1 });
	slider.setOnClick([this]() {hp = static_cast<int>(round(100 * slider.getSliderNum()));});
	///////////////////////////////////////////////////////////////// BUTTON FOR TEST∧
}

void Engine::Run()
{
	cout << "is start" << endl;
	cout << slider.getPosition().x << "|" << slider.getPosition().y << endl;
	Clock clock; // инициализировал таймер
	cutscene._anim->stop();
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
	hpText->setString(to_string(hp) + " HP");
	if (start.isPressed)
	{
		start.setSpriteColor(Color::Yellow);
		if (start.clock.getElapsedTime() > milliseconds(100))
		{
			start.clock.restart();
			start.isPressed = false;
		}
	}
	else start.setSpriteColor(Color::White);
	//---------------------------------------------------------
	if (plus.isPressed)
	{
		plus.setSpriteColor(Color::Yellow);
		if (plus.clock.getElapsedTime() > milliseconds(100))
		{
			plus.clock.restart();
			plus.isPressed = false;
		}
	}
	else plus.setSpriteColor(Color::White);

	if (minus.isPressed)
	{
		minus.setSpriteColor(Color::Yellow);
		if (minus.clock.getElapsedTime() > milliseconds(100))
		{
			minus.clock.restart();
			minus.isPressed = false;
		}
	}
	else minus.setSpriteColor(Color::White);

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

	fire.AnimUpdate(deltaTime);//тут анимация запускается
	menuBackground.AnimUpdate(deltaTime);
	gameBackground.AnimUpdate(deltaTime);
	cutscene.AnimUpdate(deltaTime);
	///////////////////////////////////////////////////////////////// BUTTON FOR TEST∧

}

void Engine::Draw()
{
	window->clear();
	menuBackground.draw(*window);
	///////////////////////////////////////////////////////////////// BUTTON FOR TEST∨
	//отрисовка обЪектов, если сцена(2) активна то рисуется она, иначе первая P.s.(по хорошему сделать состояния через switch, но для примера пойдет)
	if (sceneActiv)
	{
		start.setEnable(false);
		exitBTN.setEnable(false);
		plus.setEnable(true);
		minus.setEnable(true);
		slider.setEnable(true);

		gameBackground.draw(*window);
		fire.draw(*window);
		P.draw(*window);
		R.draw(*window);
		plus.draw(*window);
		minus.draw(*window);
		closeBTN.draw(*window);
		window->draw(*hpBack);
		window->draw(*hpBar);
		window->draw(*hpText);
		slider.draw(*window);
	}
	else {
		slider.setEnable(false);
		plus.setEnable(false);
		minus.setEnable(false);
		start.setEnable(true);
		exitBTN.setEnable(true);
		start.draw(*window);
		exitBTN.draw(*window);
		if(cutsceneActiv)
			cutscene.draw(*window);
	}
	window->display();
	///////////////////////////////////////////////////////////////// BUTTON FOR TEST∧
}
