#ifndef CHARACTER
#define CHARACTER

#include <string>
#include "Item.h"
#include "Inventory.h"

using namespace std;

class Enemy;

enum Role
{
	Knight, Ranger, Wizard
};

struct Gold
{
	int gold, silver, copper;
};

struct Usables
{
	int hpPotions, strPotions, dexPotions, intPotions;
};

class Character
{
	public:
		const static Character * player;

		Character();
		Character(Role myRole);
		~Character();
		void init(Role myRole);
		void attack(Enemy enemy);
		void damage(int damage);
		void heal(int heal);
		void addXP(int exp);
		void levelUp();
		void calculateStats();
		void earnGold(int g, int s, int c);
		bool giveGold(int g, int s, int c);
		void calculateGold();
		void equip(Item item);
		void setName(string newName);
		Role getRole();
		Stats getStats();
		Stats getBaseStats();
		Gold getGold();
		Usables getUsables();
		string getName();
		int getHealth();
		int getLevel();
		int getXP();
		int getXPToLevel();
		Item getWeapon();
		Item getArmor();
		Inventory getInventory();

	private:
		Role role;
		Stats stats, baseStats;
		Gold gold;
		Usables usables;
		string name;
		int health, level, xp, xpToLevel;
		Item weapon, armor;
		Inventory inventory;
};

#endif