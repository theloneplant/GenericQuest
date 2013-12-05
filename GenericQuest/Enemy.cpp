#include "stdafx.h"
#include "Random.h"
#include "Enemy.h"

Enemy::Enemy()
{
	changeEnemy(Rat);
}

Enemy::Enemy(EnemyType enemy)
{
	changeEnemy(enemy);
}

Enemy::Enemy(int level)
{
	changeEnemy(level);
}

Enemy::~Enemy()
{
}

void Enemy::inflict (int melee, int ranged, int magic)
{
	int hp = stats.health;
	int meleeDmg = melee - stats.armor;
	if (meleeDmg > 0)
	hp -= meleeDmg;
	int rangedDmg = ranged - stats.armor;
	if (rangedDmg > 0)
	hp -= rangedDmg;
	int magicDmg = magic - stats.resist;
	if (magicDmg > 0)
	hp -= magicDmg;

	if (hp > 0)
		stats.health = hp;
	else
		stats.health = 0;
}

void Enemy::changeEnemy(int level)
{
	int rand;
	EnemyType enemy;
	if (level <= 2)
	{
		rand = Random::random(Rat, Wolf);
		if (rand == Rat)
			enemy = Rat;
		else if (rand == Spider)
			enemy = Spider;
		else if (rand == Wolf)
			enemy = Wolf;
	}
	else if (level  <= 4)
	{
		rand = Random::random(Goblin, Kobold);
		if (rand == Goblin)
			enemy = Goblin;
		else if (rand == Ghoul)
			enemy = Ghoul;
		else if (rand == Centaur)
			enemy = Centaur;
		else if (rand == Kobold)
			enemy = Kobold;
	}
	else
	{
		rand = Random::random(Orc, Ogre);
		if (rand == Orc)
			enemy = Orc;
		else if (rand == Harpy)
			enemy = Harpy;
		else if (rand == Sorcerer)
			enemy = Sorcerer;
		else if (rand == Ogre)
			enemy = Ogre;
	}
	changeEnemy(enemy);
}

void Enemy::changeEnemy(EnemyType enemy)
{
	if (enemy == Rat)
	{
		name = "Rat";
		stats.health = 4;
		stats.strength = 2;
		stats.dexterity = 5;
		stats.intelligence = 3;
		baseStats = stats;
		Item wep("Bite", Weapon, 1, 0, 1);
		Item def("Hide", Armor, 0, 4, 0);
		weapon = wep;
		armor = def;
		cr = 1;
		calculateStats();
	}
	else if (enemy == Spider)
	{
		name = "Spider";
		stats.health = 5;
		stats.strength = 5;
		stats.dexterity = 3;
		stats.intelligence = 2;
		baseStats = stats;
		Item wep("Bite", Weapon, 2, 0, 1);
		Item def("Carapace", Armor, 1, 2, 0);
		weapon = wep;
		armor = def;
		cr = 2;
		calculateStats();
	}
	else if (enemy == Wolf)
	{
		name = "Wolf";
		stats.health = 5;
		stats.strength = 6;
		stats.dexterity = 3;
		stats.intelligence = 1;
		baseStats = stats;
		Item wep("Bite", Weapon, 3, 0, 0);
		Item def("Tough Hide", Armor, 1, 3, 0);
		weapon = wep;
		armor = def;
		cr = 2;
		calculateStats();
	}
	else if (enemy == Goblin)
	{
		name = "Goblin";
		stats.health = 7;
		stats.strength = 4;
		stats.dexterity = 5;
		stats.intelligence = 4;
		baseStats = stats;
		Item wep("Bow and Arrow", Weapon, 0, 4, 0);
		Item def("Leather Armor", Armor, 2, 5, 1);
		weapon = wep;
		armor = def;
		cr = 3;
		calculateStats();
	}
	else if (enemy == Ghoul)
	{
		name = "Ghoul";
		stats.health = 8;
		stats.strength = 4;
		stats.dexterity = 7;
		stats.intelligence = 2;
		baseStats = stats;
		Item wep("Bite", Weapon, 3, 0, 2);
		Item def("Festering Skin", Armor, 1, 5, 2);
		weapon = wep;
		armor = def;
		cr = 4;
		calculateStats();
	}
	else if (enemy == Centaur)
	{
		name = "Centaur";
		stats.health = 9;
		stats.strength = 4;
		stats.dexterity = 7;
		stats.intelligence = 4;
		baseStats = stats;
		Item wep("Bow and Arrow", Weapon, 0, 7, 0);
		Item def("Tough Skin", Armor, 2, 6, 0);
		weapon = wep;
		armor = def;
		cr = 4;
		calculateStats();
	}
	else if (enemy == Kobold)
	{
		name = "Kobold";
		stats.health = 8;
		stats.strength = 7;
		stats.dexterity = 4;
		stats.intelligence = 3;
		baseStats = stats;
		Item wep("Shortsword", Weapon, 0, 7, 0);
		Item def("Crude Armor", Armor, 2, 4, 1);
		weapon = wep;
		armor = def;
		cr = 3;
		calculateStats();
	}
	else if (enemy == Orc)
	{
	}
	else if (enemy == Harpy)
	{
	}
	else if (enemy == Sorcerer)
	{
	}
	else //enemy == Ogre
	{
	}
}

void Enemy::calculateStats()
{
	stats.strength = baseStats.strength;
	stats.dexterity = baseStats.dexterity;
	stats.intelligence = baseStats.intelligence;

	stats.armor = stats.strength / 5 + armor.getStats().armor;
	float bonusDodge = static_cast<float>(stats.dexterity + armor.getStats().dodge) * 2;
	float cap = 95;
	float modifier = 0.986f;
	stats.dodge = static_cast<int>((bonusDodge * cap) / (bonusDodge + modifier * cap) + 5); //Uses diminishing returns
	stats.resist = stats.intelligence / 5 + armor.getStats().resist;
	stats.speed = 10 + stats.dexterity / 5 - stats.armor;

	if (weapon.getStats().melee == 0)
		stats.melee = 0;
	else
		stats.melee = stats.strength / 4 + weapon.getStats().melee;
	if (weapon.getStats().range == 0)
		stats.range = 0;
	else
		stats.range = stats.dexterity / 4 + weapon.getStats().range;
	if (weapon.getStats().magic == 0)
		stats.magic = 0;
	else
		stats.magic = stats.intelligence / 4 + weapon.getStats().magic;
}

Stats Enemy::getStats()
{
	return stats;
}

Stats Enemy::getBaseStats()
{
	return baseStats;
}

Item Enemy::getWeapon()
{
	return weapon;
}

Item Enemy::getArmor()
{
	return armor;
}

string Enemy::getName()
{
	return name;
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