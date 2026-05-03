#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<memory>
#include "AssetManager.h"
#include "Animator.h"

using namespace sf;
using namespace std;

class Object //будет дополнятся
{
public:
	Object(Texture const& texture, IntRect const& rect, int frameCount, int Ycount, int frameTime = 0, float animTime = 0); //конструктор
		// 	          1						2
		//1-ссылка на  текстуру, 2 как в аниматоре
	//функции из аниматора
	void AnimPlay(); // играть анимацию
	void AnimPause(); // остановить анимацию
	bool AnimGetPlay(); // получить состояние _playing
	void AnimSetLoop(bool loop); //задать, будет ли анимация цикличной
	void AnimSetFrameTime(int frametime = 100); //задать время кадра
	void AminSetAnimTime(float animTime = 1.f); // задать время анимации 
	void AnimReset(); //сбрость(перейти к первому кадру) анимацию
	bool AnimIsFinished() const;//получить состояние _finished
	void AnimSetOnFinished(function<void()> callback); // лямбда функция вызываем
	void AnimUpdate(Time dt); //игра анимации. Нужно засунуть в Update() в Engine.cpp  
	void AnimStop();// остановить и сбрость(перейти к первому кадру) анимацию
	void draw(RenderWindow& window) const;
	//бфзовые функции
	Vector2f getPosition();
	void setPosition(Vector2f pos);
	Vector2f getScale();
	void setScale(Vector2f scale);

	Texture _texture;
	Sprite* _sprite;
	Animator* _anim;
};

