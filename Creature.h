#pragma once
#include <iostream>
#include<SFML/Graphics.hpp>
#include "Object.h"
#include "Cards.h"
#include "Effects.h"
#include "Armor.h"
#include "Weapon.h"

using namespace sf;
using namespace std;

class Creature
{
public:
	Creature(const string& name, const int& lvl, const int& hp, const int& dmg, const int& arm, const int& move, const int& crit, const float& critMod, Weapon& weapon, Armor& armor, Texture const& texture, IntRect const& rect, int frameCount, int Ycount, int frameTime = 0, float animTime = 0);
	void draw(RenderWindow& win) const;
	void setPosition(Vector2f pos);
	Vector2f getPosition();
	void setScale(Vector2f scale);
	Vector2f getScale();
	string getName();
	int getLevel();
	int getMaxHealth();
	int getHealth();
	int getDamage();
	int getArm();
	int getMaxMove();
	int getMove();
	int getCritChance();
	float getCritMod();
	Weapon getWeapon();
	Armor getArmor();


	void setName(string name);
	void setLevel(int lvl);
	void setMaxHealth(int maxHP);
	void setHealth(int hp);
	void setDamage(int dmg);
	void setArm(int arm);
	void setMove(int move);
	void setMaxMove(int maxMove);
	void setCritChance(int critChance);
	void setCritMod(float critMod);
	void setWeapon(Weapon weapon);
	void setArmor(Armor armor);

	void TakeDamage(int damage);

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
	void AnimStop();

private:
	string _name;
	int _level;
	int _maxHP;
	int _health;
	int _damage;
	int _arm;
	int _maxMove;
	int _move;
	int _critChance;
	float _critMod;
	Object* _sprite;
	Weapon* _weapon;
	Armor* _armor;
};

