#include "Engine.h"
#include "Engine.h"

void Engine::Input()
{
	while (const optional event = window->pollEvent())
	{
		if (event->is<Event::Closed>()) window->close();
		//if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) window->close();
		/////////////////////////////////////////// BUTTON FOR TEST∨
		btn.handleEvent(*event, *window);		
		exitBTN.handleEvent(*event, *window);	
		closeBTN.handleEvent(*event, *window);
		/////////////////////////////////////////// BUTTON FOR TEST∧
	}
}



Engine::Engine()
{
	background.setTexture(&AssetManager::GetTexture("Sprite/Background.jpg"));
}

void Engine::Run()
{
	cout << "is start" << endl;
	///////////////////////////////////////////////////////////////// BUTTON FOR TEST∨
btn.setSize(2, 1);												
btn.setSpriteColor(Color(255, 0, 0));							
btn.setOnClick([this]() {btn.isPressed = true;  sceneActiv = true;});
																
exitBTN.setSpriteColor(Color::Red);								
exitBTN.setSize(2, 1);											
exitBTN.setOnClick([this] {window->close();});	
closeBTN.setSpriteColor(Color(200, 0 ,0));
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
	else closeBTN.setSpriteColor(Color(200,0,0));						
	///////////////////////////////////////////////////////////////// BUTTON FOR TEST∧

}

void Engine::Draw()
{
	window->clear();
	window->draw(background);
	///////////////////////////////////////////////////////////////// BUTTON FOR TEST∨
	btn.draw(*window);
	exitBTN.draw(*window);
	if (sceneActiv)
	{
		window->draw(scene);
		closeBTN.draw(*window);
	}
	///////////////////////////////////////////////////////////////// BUTTON FOR TEST∧
	window->display();
}
