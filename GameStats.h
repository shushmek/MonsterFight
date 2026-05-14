#pragma once

#include <algorithm>

// Счетчики времени выполнения для текущего демо-сохранения.
// Engine обновляет их при изменении HP, при сохранении игроком и при загрузке сохранения.
struct GameStats
{
	int saves = 0;
	int loads = 0;
	int hpDamageTaken = 0;
	int hpHealed = 0;
	int hpChanges = 0;
	int minHealthSeen = 0;
	int maxHealthSeen = 0;

	// Хранит минимальное и максимальное значения HP, замеченные в этой сессии/сохранении.
	void TrackHealth(int health)
	{
		minHealthSeen = std::min(minHealthSeen, health);
		maxHealthSeen = std::max(maxHealthSeen, health);
	}

	// Инициализирует минимальный/максимальный HP при запуске игры.
	void StartSession(int health)
	{
		minHealthSeen = health;
		maxHealthSeen = health;
	}

	// Записывает одно реальное изменение HP и разделяет его на урон или лечение.
	void RecordHealthChange(int oldHealth, int newHealth)
	{
		if (oldHealth == newHealth)
			return;

		++hpChanges;
		if (newHealth < oldHealth)
			hpDamageTaken += oldHealth - newHealth;
		else
			hpHealed += newHealth - oldHealth;

		TrackHealth(newHealth);
	}
};
