#include "stdafx.h"
#include "Random.h"
#include "Enemy.h"
#include "Character.h"

const int EXPERIENCE_MODIFIER = 100;
const Character * Character::player = new Character();

Character::Character()
{
	name = "Hero";
	init(Knight);
}

Character::Character(Role myRole)
{
	name = "Hero";
	init(myRole);
}

Character::~Character()
{}

void Character::init(Role myRole)
{
	role = myRole;

	if (role == Knight)
	{
		baseStats.health = 10;
		baseStats.strength = 10;
		baseStats.dexterity = 5;
		baseStats.intelligence = 2;
	}
	else if (role == Ranger)
	{
		baseStats.health = 7;
		baseStats.strength = 5;
		baseStats.dexterity = 11;
		baseStats.intelligence = 4;
	}
	else if (role == Wizard)
	{
		baseStats.health = 5;
		baseStats.strength = 3;
		baseStats.dexterity = 7;
		baseStats.intelligence = 12;
	}

	stats.health = 0;
	stats.strength = 0;
	stats.dexterity = 0;
	stats.intelligence = 0;
	stats.armor = 0;
	stats.dodge = 0;
	stats.resist = 0;
	stats.melee = 0;
	stats.range = 0;
	stats.magic = 0;

	gold.gold = 0;
	gold.silver = 0;
	gold.copper = 1;

	usables.hpPotions = 0;
	usables.strPotions = 0;
	usables.dexPotions = 0;
	usables.intPotions = 0;
}

void Character::attack(Enemy enemy)
{
}

void Character::damage(int damage)
{
	health -= damage;
}

void Character::heal(int heal)
{
	health += heal;
}

void Character::addXP(int exp)
{
	xp += exp;
}

void Character::levelUp()
{
	xp = 0;
	xpToLevel += EXPERIENCE_MODIFIER;

	if (role == Knight)
	{
		baseStats.health += Random::random(2, 4);
		baseStats.strength += Random::random(2, 4);
		baseStats.dexterity += Random::random(1, 2);
		baseStats.intelligence += Random::random(0, 1);
	}
	else if (role == Ranger)
	{
		baseStats.health += Random::random(2, 3);
		baseStats.strength += Random::random(0, 2);
		baseStats.dexterity += Random::random(2, 5);
		baseStats.intelligence += Random::random(0, 2);
	}
	else if (role == Wizard)
	{
		baseStats.health += Random::random(1, 2);
		baseStats.strength += Random::random(0, 1);
		baseStats.dexterity += Random::random(2, 3);
		baseStats.intelligence += Random::random(2, 5);
	}

	calculateStats();
}

void Character::calculateStats()
{
	stats.strength = baseStats.strength + armor.getStats().strength + weapon.getStats().strength;
	stats.dexterity = baseStats.dexterity + armor.getStats().dexterity + weapon.getStats().dexterity;
	stats.intelligence = baseStats.intelligence + armor.getStats().intelligence + weapon.getStats().intelligence;

	stats.armor = stats.strength / 5 + armor.getStats().armor + weapon.getStats().armor;
	stats.dodge = stats.dexterity / 5 + armor.getStats().dodge + weapon.getStats().dodge;
	stats.resist = stats.intelligence / 5 + armor.getStats().resist + weapon.getStats().resist;

	stats.melee = stats.strength / 4 + armor.getStats().melee + weapon.getStats().melee;
	stats.range = stats.dexterity / 4 + armor.getStats().range + weapon.getStats().range;
	stats.magic = stats.intelligence / 4 + armor.getStats().magic + weapon.getStats().magic;
}

void Character::earnGold(int g, int s, int c)
{
	gold.gold += g;
	gold.silver += s;
	gold.copper += c;
}

bool Character::giveGold(int g, int s, int c)
{
	int tempC = gold.copper;
	int tempS = gold.silver;
	int tempG = gold.gold;

	tempC -= c;
	while (tempC < 0)
	{
		tempS--;
		tempC += 10;
	}

	tempS -= s;
	while (tempS < 0)
	{
		tempG--;
		tempS += 10;
	}

	tempG -= g;
	if (tempG < 0)
		return false;
	else
	{
		gold.copper = tempC;
		gold.silver = tempS;
		gold.gold = tempG;
		return true;
	}
}

void Character::calculateGold()
{
	int copper = gold.copper % 10;
	gold.silver += gold.copper / 10;
	int silver = gold.silver % 10;
	gold.gold += gold.silver / 10;

	gold.copper = copper;
	gold.silver = silver;
}

void Character::equip(Item item)
{
	if (item.getItemType() == Weapon)
		weapon = item;
	else if (item.getItemType() == Armor)
		armor = item;

	calculateStats();
}

void Character::setName(string newName)
{
	name = newName;
}

Role Character::getRole()
{
	return role;
}

Stats Character::getStats()
{
	return stats;
}

Stats Character::getBaseStats()
{
	return baseStats;
}

Gold Character::getGold()
{
	return gold;
}

Usables Character::getUsables()
{
	return usables;
}

string Character::getName()
{
	return name;
}

int Character::getHealth()
{
	return health;
}

int Character::getLevel()
{
	return level;
}
int Character::getXP()
{
	return xp;
}

Item Character::getWeapon()
{
	return weapon;
}

Item Character::getArmor()
{
	return armor;
}

Inventory Character::getInventory()
{
	return inventory;
}