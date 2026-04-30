#pragma once
#include <iostream>
#include<SFML/Graphics.hpp>
#include "Animator.h"
#include "Object.h"
#include "Cards.h"
#include "Effects.h"

using namespace sf;
using namespace std;

class Weapon
{
	enum Rarity {Common, Rare, Epick, Mythic, Legendary};

	string name;
	Rarity _rarity;
	int _damage;
	int _minBet;
	int _maxBet;
	int _move;
	int _combo;
	Effects _effect;
};

