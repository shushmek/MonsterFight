#pragma once
#include <iostream>
#include<SFML/Graphics.hpp>
#include "Object.h"
#include "Cards.h"
#include "Effects.h"

using namespace sf;
using namespace std;

class Weapon
{
public:
	enum Rarity {None, Common, Rare, Epick, Mythic, Legendary};
	Weapon(const string& name, const Rarity& rarity, const int& damage, const int& min, const int& max, const int& move, const int& combo, const int& crit, const float& critMode,Texture const& texture, IntRect const& rect, int frameCount, int Ycount, int frameTime = 0, float animTime = 0);
	//void TakeDamage(Creature target, int damage);
	int getDamage();
	string getName();
	int getRarity();
	int getMinBet();
	int getMaxBet();
	int getMove();
	int getCombo();
	void setPosition(Vector2f pos);
	void setScale(Vector2f scale);
	void draw(RenderWindow& window) const;

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
	//Effects getEffect();
private:
	string _name;
	Rarity _rarity;
	int _damage;
	int _minBet;
	int _maxBet;
	int _move;
	int _combo;
	int _critChace;
	float _critMod;
	//Effects _effect;
	Object* _sWeapon;
};

