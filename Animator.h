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
	explicit Animator(Sprite& sprite, IntRect const& rect, int frameCount , int Ycount, int frameTime = 0, float animTime = 0);
	//конструктор аниматора Animator anim(sprite, IntRect({0,0},{32,32}), 10, 0, 2f);
										//  1				2			   3   4  5; 
										// 1-спрайт-лист для анимации (тип Sprite), 
										// 2- первая скобка {0,0} задает начало отсчета кадров, размер кадра {32,32}
										// 3- количество кадров в анимации
										// 4- длительность показа одного кадра (в миллисекундах); если не задаете, пишите "0"
										// 5- длительность всей анимации (в секундах); если указан frameTime, не пишите animTime
	void play(); // воспроизвести анимацию
	void pause(); // приостановить анимацию
	void stop(); // остановить и сбросить анимацию (перейти к первому кадру)
	bool getPlay(); // получить состояние _playing
	void setLoop(bool loop); //задать, будет ли анимация зациклена
	void setFrameTime(int frametime = 100); //задать время кадра
	void setAnimTime(float animTime = 1.f); // задать время анимации
	void update(Time delta); //воспроизводит анимацию. Поместите это в Update() в Engine.cpp  
	void reset(); //сбросить анимацию (перейти к первому кадру)
	bool isFinished() const;//получить состояние _finished
	void setOnFinished(function<void()> callback); // лямбда-функция, вызываемая при завершении анимации, т.е. функция, которая может делать что угодно при вызове, 
										       //например: Anim._onFinished([]() {cout << "привет" << endl; }); 
											   // печатает "привет" в консоль при завершении анимации (не работает, когда _loop = true)		
private:
	Sprite& _sprite;
	int _currentFrame = 0;
	int _cerrentYFrame = 0;
	int _maxYframe = 1;
	vector<IntRect> _frames;
	Clock _clock;
	int _frameTime;
	float _animTime;
	bool _playing;
	bool _loop;
	bool _finished;
	function<void()> _onFinished;
};
