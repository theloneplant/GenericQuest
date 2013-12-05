#include "stdafx.h"
#include "Random.h"
#include "Enemy.h"
#include "Character.h"

static Character playerValue;
Character* Character::player = &playerValue;

Character::Character()
{
	initialized = false;
	init(None);
}

Character::Character(Role myRole)
{
	initialized = false;
	init(myRole);
}

Character::~Character()
{
}

void Character::init(Role myRole)
{
	role = myRole;
	name = "Hero";
	area = "Foggybottom";
	pet = "None";
	petDmg = 0;
	level = 1;
	xp = 0;
	xpToLevel = EXPERIENCE_MODIFIER;

	inventory.clear();

	if (role == Knight)
	{
		stats.health = 10;
		baseStats.health = 10;
		baseStats.strength = 12;
		baseStats.dexterity = 4;
		baseStats.intelligence = 1;
		if (!initialized)
		{
			Item atk("Iron Longsword", Weapon, 1, 0, 0);
			weapon = atk;
			Item def("Chain Mail", Armor, 1, 0, 0);
			armor = def;
			inventory.add(atk);
			inventory.add(def);
		}
	}
	else if (role == Ranger)
	{
		pet = "Bear Bro";
		setPetDmg(1);
		stats.health = 7;
		baseStats.health = 7;
		baseStats.strength = 5;
		baseStats.dexterity = 11;
		baseStats.intelligence = 4;
		if (!initialized)
		{
			Item atk("Oak Longbow", Weapon, 0, 1, 0);
			weapon = atk;
			Item def("Leather Armor", Armor, 0, 1, 0);
			armor = def;
			inventory.add(atk);
			inventory.add(def);
		}
	}
	else if (role == Wizard)
	{
		stats.health = 5;
		baseStats.health = 5;
		baseStats.strength = 3;
		baseStats.dexterity = 7;
		baseStats.intelligence = 12;
		if (!initialized)
		{
			Item atk("Spellbook", Weapon, 0, 0, 1);
			weapon = atk;
			Item def("Blue Robe", Armor, 0, 0, 1);
			armor = def;
			inventory.add(def);
			inventory.add(atk);
		}
	}

	gold.gold = 0;
	gold.silver = 0;
	gold.copper = 1;

	usables.hpPotions = 1;
	usables.strPotions = 0;
	usables.dexPotions = 0;
	usables.intPotions = 0;

	calculateStats();
	if (role != None)
		initialized = true;
}

void Character::inflict (int melee, int ranged, int magic)
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

void Character::heal(int heal)
{
	stats.health += heal;
	if (stats.health > baseStats.health)
		stats.health = baseStats.health;
}

void Character::useHPPotion()
{
	usables.hpPotions--;
	heal(baseStats.health / 2);
}

void Character::reward(int cr)
{
	addXP(EXPERIENCE_MODIFIER * cr / level);
	unsigned int avgCopper = 5 * cr;
	earnGold(0, 0, Random::random(static_cast<int>(avgCopper * 0.7), static_cast<int>(avgCopper * 1.3)));
	calculateGold();
}

void Character::addXP(int exp)
{
	xp += exp;
	while (xp >= xpToLevel)
		levelUp();
}

void Character::setXP(int exp)
{
	xp = exp;
}

void Character::levelUp()
{
	level++;
	xp -= xpToLevel;
	xpToLevel += EXPERIENCE_MODIFIER;

	if (role == Knight)
	{
		baseStats.health += 4;
		baseStats.strength += 5;
		baseStats.dexterity += 2;
		baseStats.intelligence += 1;
	}
	else if (role == Ranger)
	{
		baseStats.health += 3;
		baseStats.strength += 2;
		baseStats.dexterity += 5;
		baseStats.intelligence += 2;
	}
	else if (role == Wizard)
	{
		baseStats.health += 2;
		baseStats.strength += 1;
		baseStats.dexterity += 3;
		baseStats.intelligence += 6;
	}

	stats.health = baseStats.health;
	calculateStats();
}

void Character::calculateStats()
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
		stats.melee = stats.strength / 3 + weapon.getStats().melee;
	if (weapon.getStats().range == 0)
		stats.range = 0;
	else
		stats.range = stats.dexterity / 4 + weapon.getStats().range;
	if (weapon.getStats().magic == 0)
		stats.magic = 0;
	else
		stats.magic = stats.intelligence / 4 + weapon.getStats().magic;

	//Check current stats
	capStat(stats.health);
	capStat(stats.strength);
	capStat(stats.dexterity);
	capStat(stats.intelligence);
	capStat(stats.armor);
	capStat(stats.dodge);
	capStat(stats.resist);
	capStat(stats.melee);
	capStat(stats.range);
	capStat(stats.magic);

	//Check base stats
	capStat(baseStats.health);
	capStat(baseStats.strength);
	capStat(baseStats.dexterity);
	capStat(baseStats.intelligence);
	capStat(baseStats.armor);
	capStat(baseStats.dodge);
	capStat(baseStats.resist);
	capStat(baseStats.melee);
	capStat(baseStats.range);
	capStat(baseStats.magic);
}

void Character::capStat(int& stat)
{
	if (stat > MAX_STAT)
		stat = MAX_STAT;
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
	{
		weapon.setName(item.getName());
		weapon.setStats(item.getStats());
		weapon.setItemType(item.getItemType());
	}
	else if (item.getItemType() == Armor)
	{
		armor.setName(item.getName());
		armor.setStats(item.getStats());
		armor.setItemType(item.getItemType());
	}

	calculateStats();
}

void Character::addItem(Item newItem)
{
	inventory.add(newItem);
}

void Character::removeItem(string itemName)
{
	inventory.remove(itemName);
}

void Character::setRole(Role newRole)
{
	role = newRole;
}

void Character::setName(string newName)
{
	name = newName;
}

void Character::setArea(string newArea)
{
	area = newArea;
}

void Character::setPet(string newPet)
{
	pet = newPet;
}

void Character::setPetDmg(int cr)
{
	petDmg = cr * 3;
}

void Character::setInit(bool newInit)
{
	initialized = newInit;
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

string Character::getArea()
{
	return area;
}

string Character::getPet()
{
	return pet;
}

int Character::getPetDmg()
{
	return petDmg;
}

int Character::getHealth()
{
	return baseStats.health;
}

int Character::getLevel()
{
	return level;
}

int Character::getXP()
{
	return xp;
}

int Character::getXPToLevel()
{
	return xpToLevel;
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

bool Character::isDead()
{
	if (stats.health <= 0)
		return true;
	else
		return false;
}