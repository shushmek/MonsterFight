#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<memory>
#include "AssetManager.h"
#include "Animator.h"

using namespace sf;
using namespace std;

class Object //будет расширяться
{
public:
	Object(Texture const& texture, IntRect const& rect, int frameCount, int Ycount, int frameTime = 0, float animTime = 0); //конструктор
		// 	          1						2
		//1-ссылка на текстуру, 2 как в аниматоре
	//функции из аниматора
	void AnimPlay(); // воспроизвести анимацию
	void AnimPause(); // приостановить анимацию
	bool AnimGetPlay(); // получить состояние _playing
	void AnimSetLoop(bool loop); //задать, будет ли анимация зациклена
	void AnimSetFrameTime(int frametime = 100); //задать время кадра
	void AminSetAnimTime(float animTime = 1.f); // задать время анимации 
	void AnimReset(); //сбросить анимацию (перейти к первому кадру)
	bool AnimIsFinished() const;//получить состояние _finished
	void AnimSetOnFinished(function<void()> callback); // лямбда-функция для вызова
	void AnimUpdate(Time dt); //воспроизводит анимацию. Поместите это в Update() в Engine.cpp  
	void AnimStop();// остановить и сбросить анимацию (перейти к первому кадру)
	void draw(RenderWindow& window) const;
	//базовые функции
	Vector2f getPosition();
	void setPosition(Vector2f pos);
	Vector2f getScale();
	void setScale(Vector2f scale);
	void setRect(IntRect rect);

	Texture _texture;
	Sprite* _sprite;
	Animator* _anim;
};
