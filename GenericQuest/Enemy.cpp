#include "stdafx.h"
#include "Random.h"
#include "Enemy.h"

Enemy::Enemy(int level)
{
	if (level <= 2)
	{
		int enemy = Random::random(Rat, Wolf);
		if (enemy == Rat)
		{
			name = "Rat";
			stats.health = 4;
			stats.strength = 2;
			stats.dexterity = 5;
			stats.intelligence = 3;
			Item wep("Bite", Weapon, 1, 0, 1);
			Item def("Hide", Armor, 0, 6, 0);
			weapon = wep;
			armor = def;
			cr = 1;
		}
		else if (enemy == Spider)
		{
			name = "Spider";
			stats.health = 5;
			stats.strength = 5;
			stats.dexterity = 3;
			stats.intelligence = 2;
			Item wep("Bite", Weapon, 2, 0, 1);
			Item def("Carapace", Armor, 2, 2, 0);
			weapon = wep;
			armor = def;
			cr = 2;
		}
		else if (enemy == Wolf)
		{
			name = "Wolf";
			stats.health = 5;
			stats.strength = 6;
			stats.dexterity = 3;
			stats.intelligence = 1;
			Item wep("Bite", Weapon, 3, 0, 0);
			Item def("Tough Hide", Armor, 3, 2, 0);
			weapon = wep;
			armor = def;
			cr = 2;
		}
	}
	else if (level  <= 4)
	{
		int enemy = Random::random(Goblin, Kobold);
		if (enemy == Goblin)
		{
			name = "Goblin";
			stats.health = 7;
			stats.strength = 4;
			stats.dexterity = 5;
			stats.intelligence = 4;
			Item wep("Bow and Arrow", Weapon, 0, 4, 0);
			Item def("Leather Armor", Armor, 2, 5, 2);
			weapon = wep;
			armor = def;
			cr = 3;
		}
		else if (enemy == Ghoul)
		{
			name = "Ghoul";
			stats.health = 8;
			stats.strength = 4;
			stats.dexterity = 7;
			stats.intelligence = 2;
			Item wep("Bite", Weapon, 3, 0, 2);
			Item def("Festering Skin", Armor, 2, 5, 2);
			weapon = wep;
			armor = def;
			cr = 4;
		}
		else if (enemy == Centaur)
		{
			name = "Centaur";
			stats.health = 9;
			stats.strength = 4;
			stats.dexterity = 7;
			stats.intelligence = 4;
			Item wep("Bow and Arrow", Weapon, 0, 7, 0);
			Item def("Tough Skin", Armor, 2, 6, 0);
			weapon = wep;
			armor = def;
			cr = 4;
		}
		else if (enemy == Kobold)
		{
			name = "Kobold";
			stats.health = 8;
			stats.strength = 7;
			stats.dexterity = 4;
			stats.intelligence = 3;
			Item wep("Shortsword", Weapon, 0, 7, 0);
			Item def("Crude Armor", Armor, 3, 4, 1);
			weapon = wep;
			armor = def;
			cr = 3;
		}
	}
	else if (level  <= 6)
	{
		int enemy = Random::random(Orc, Ogre);
		if (enemy == Orc)
		{
		}
		else if (enemy == Harpy)
		{
		}
		else if (enemy == Sorcerer)
		{
		}
		else if (enemy == Ogre)
		{
		}
	}
	else if (level  <= 8)
	{
		int enemy = Random::random(Basilisk, Giant);
		if (enemy == Basilisk)
		{
		}
		else if (enemy == Demon)
		{
		}
		else if (enemy == Elemental)
		{
		}
		else if (enemy == Giant)
		{
		}
	}
	else if (level  <= 10)
	{
		int enemy = Random::random(Succubus, IronGolem);
		if (enemy == Succubus)
		{
		}
		else if (enemy == Beholder)
		{
		}
		else if (enemy == Wyvern)
		{
		}
		else if (enemy == IronGolem)
		{
		}
	}
	else
	{
		int enemy = Random::random(Chimera, Lich);
		if (enemy == Chimera)
		{
		}
		else if (enemy == Dragon)
		{
		}
		else if (enemy == Hydra)
		{
		}
		else if (enemy == Lich)
		{
		}
	}
}

Enemy::~Enemy()
{
}

void Enemy::inflict (int melee, int ranged, int magic)
{
	int hp = stats.health;
	hp -= ((melee - stats.armor) + (ranged - stats.armor) + (magic - stats.resist));
	if (hp > 0)
		stats.health = hp;
	else
		stats.health = 0;
}

Stats Enemy::getStats()
{
	return stats;
}

int Enemy::getCR()
{
	return cr;
}

bool Enemy::isDead()
{
	if (stats.health <= 0)
		return true;
	else
		return false;
}