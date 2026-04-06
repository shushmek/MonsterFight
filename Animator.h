#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <unordered_map>
#include<functional>
#include<iostream>
#include <cmath>

using namespace sf;
using namespace std;

class Animator
{
public:
	explicit Animator(Sprite& sprite, IntRect const& rect, int frameCount, int frameTime = 0, float animTime = 0);
	//конструктор аниматора Animator anim(sprite, IntRect({0,0},{32,32}), 10, 0, 2f);
										//  1				2			   3   4  5; 
										// 1-спрайтшит для анимации(тип спрайт), 
										// 2- первая скобка {0,0} то откуда начинать отсчитывать кадр, размер кадра {32,32}
										// 3- количестро кадров в анимации
										// 4- длитильность показа одного кадра(в милисекундах) если не указываешь пиши "0"
										// 5- длительность всей анимации (в секундах) если есть frameTime тогда animTime не пиши
	void play(); // играть анимацию
	void pause(); // остановить анимацию
	void stop(); // остановить и сбрость(перейти к первому кадру) анимацию
	bool getPlay(); // получить состояние _playing
	void setLoop(bool loop); //задать, будет ли анимация цикличной
	void setFrameTime(int frametime = 100); //задать время кадра
	void setAnimTime(float animTime = 1.f); // задать время анимации
	void update(Time delta); //игра анимации. Нужно засунуть в Update() в Engine.cpp  
	void reset(); //сбрость(перейти к первому кадру) анимацию
	bool isFinished() const;//получить состояние _finished
	void setOnFinished(function<void()> callback); // лямбда функция вызываемая при окончании анимации, т.е. функция при вызове которой происходит что угодно, 
											       //например: Anim._onFinished([]() {cout << "hello" << endl; }); 
												   // выведет в консоль "hello" когда закончится анимация(не работает когда _loop = true)		
private:
	Sprite& _sprite;
	int _currentFrame = 0;
	vector<IntRect> _frames;
	Clock _clock;
	int _frameTime;
	float _animTime;
	bool _playing;
	bool _loop;
	bool _finished;
	function<void()> _onFinished;
};

