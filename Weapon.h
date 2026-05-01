#pragma once
#include <iostream>
#include<SFML/Graphics.hpp>
#include "Object.h"
#include "Cards.h"
#include "Effects.h"
#include "Creature.h"

using namespace sf;
using namespace std;

class Weapon
{
	enum Rarity {None, Common, Rare, Epick, Mythic, Legendary};
public:
	Weapon(const string& name, const Rarity& rarity, const int& damage, const int& min, const int& max, const int& move, const int& combo, Texture const& texture, IntRect const& rect, int frameCount, int Ycount, int frameTime = 0, float animTime = 0);
	void TakeDamage(Creature target, int damage);
	int getDamage();
	string getName();
	int getRarity();
	int getMinBet();
	int getMaxBet();
	int getMove();
	int getCombo();
	//Effects getEffect();
private:
	string _name;
	Rarity _rarity;
	int _damage;
	int _minBet;
	int _maxBet;
	int _move;
	int _combo;
	//Effects _effect;
	Object* _sWeapon;
};

