#ifndef ENEMY
#define ENEMY

#include "Item.h"

enum EnemyType
{
	//Random Encounters
	Rat, Spider, Wolf, 
	Goblin, Ghoul, Centaur, Kobold, 
	Orc, Harpy, Sorcerer, Ogre,
	Basilisk, Demon, Elemental, Giant, 
	Succubus, Beholder, Wyvern, IronGolem,
	Chimera, Dragon, Hydra, Lich
};

class Enemy
{
	public:
		Enemy();
		Enemy(int level);
		~Enemy();
		void inflict (int melee, int ranged, int magic);
		void changeEnemy(int level);
		void calculateStats();
		Stats getStats();
		Stats getBaseStats();
		string getName();
		int getCR();
		bool isDead();
	private:
		string name;
		EnemyType type;
		Item weapon, armor;
		Stats stats, baseStats;
		int cr;
};

#endif