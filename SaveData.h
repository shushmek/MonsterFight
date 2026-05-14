#pragma once

#include <string>
#include "GameStats.h"

// Снимок одного слота сохранения. Он хранит только состояние демо, которое сейчас можно восстановить:
// числовые параметры игрока, индексы выбранного снаряжения и накопленную статистику.
struct SaveData
{
	// Статистика игрока.
	std::string playerName = "none";
	int level = 1;
	int health = 100;
	int maxHealth = 100;
	int damage = 1;
	int armor = 0;
	int move = 3;
	int maxMove = 3;
	int critChance = 0;
	float critMod = 2.f;
	int minBet = 2;
	int maxBet = 6;
	int cash = 30;

	// Индексы указывают обратно на ItemList. Мы не сериализуем целые объекты Weapon/Armor.
	int weaponIndex = 1;
	int armorIndex = 1;

	// Сохраняется вместе с игроком, чтобы счетчики переживали загрузку.
	GameStats stats;
};
