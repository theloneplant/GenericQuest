#ifndef CHARACTER
#define CHARACTER

#include <string>
#include "Item.h"
#include "Inventory.h"

using namespace std;

class Enemy;

enum Role
{
	Knight, Ranger, Wizard, None
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
		static Character * player;

		Character();
		Character(Role myRole);
		~Character();
		void init(Role myRole);
		void inflict (int melee, int ranged, int magic);
		void heal(int heal);
		void useHPPotion();
		void reward(int cr);
		void addXP(int exp);
		void setXP(int exp);
		void levelUp();
		void calculateStats();
		void capStat(int& stat);
		void earnGold(int g, int s, int c);
		bool giveGold(int g, int s, int c);
		void calculateGold();
		void equip(Item item);
		void addItem(Item newItem);
		void removeItem(string itemName);
		void setRole(Role newRole);
		void setName(string newName);
		void setArea(string newArea);
		void setPet(string newPet);
		void setPetDmg(int cr);
		void setInit(bool newInit);
		Role getRole();
		Stats getStats();
		Stats getBaseStats();
		Gold getGold();
		Usables getUsables();
		string getName();
		string getArea();
		string getPet();
		int getPetDmg();
		int getHealth();
		int getLevel();
		int getXP();
		int getXPToLevel();
		Item getWeapon();
		Item getArmor();
		Inventory getInventory();
		bool isDead();

	private:
		Role role;
		Stats stats, baseStats;
		Gold gold;
		Usables usables;
		string name, area, pet;
		int level, xp, xpToLevel, petDmg;
		Item weapon, armor;
		Inventory inventory;
		bool initialized;
};

#endif