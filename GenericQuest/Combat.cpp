#include "stdafx.h"
#include "Canvas.h"
#include "Color.h"
#include "Random.h"
#include "Character.h"
#include "Enemy.h"
#include "Frame.h"
#include "Text.h"
#include "Animation.h"
#include "Menu.h"
#include "StatusBar.h"
#include "BranchManager.h"
#include "Branch.h"
#include "Combat.h"

Combat::Combat(BranchManager* bm)
{
	Branch::Branch(bm);
	manager = bm;

	enemy = new Enemy(Character::player->getLevel());
	string fileName = "combat/" + enemy->getName() + "Intro.txt";
	text = new Text(true, fileName, false, 20, 500, 0, 1);
	text1 = new Text(false, "Message2", true, 20, 500, 0, 1);

	meleeChoice = rangeChoice = magicChoice = knightBash = knightCharge = rangerStun
		= wizardFreeze = wizardShock = backUpChoice = backUpChoice = potionsChoice = -1;
	distance = 10;

	//MENU INIT
	Text* message = new Text(false, "What do you do?", false, 0, 0, -2, 0);
	Animation* cursor = new Animation("cursor.anim", 15, 10, true, false, 3);
	cursor->play();

	choice = new Menu(message, cursor, text->getPosition().x + 3, 
		text->getPosition().y + text->getDimension().y + 1, 72, 80);
	
	melee = new Text(false, "", false, 0, 0, 0, 0);
	range = new Text(false, "", false, 0, 0, 0, 0);
	magic = new Text(false, "", false, 0, 0, 0, 0);
	bash = new Text(false, "", false, 0, 0, 0, 0);
	charge = new Text(false, "", false, 0, 0, 0, 0);
	stun = new Text(false, "", false, 0, 0, 0, 0);
	freeze = new Text(false, "", false, 0, 0, 0, 0);
	shock = new Text(false, "", false, 0, 0, 0, 0);
	potions = new Text(false, "", false, 0, 0, 0, 0);
	backUp = new Text(false, "", false, 0, 0, 0, 0);
	moveIn = new Text(false, "", false, 0, 0, 0, 0);

	updateMenu();
	choice->setHidden(true);

	//STATUS BARS
	playerHP = new StatusBar(25, FG_WHITE, BG_RED, BG_DARKGRAY, 0, 23);
	enemyHP = new StatusBar(25, FG_WHITE, BG_RED, BG_DARKGRAY, 55, 23);

	myFrames.push_back(text);
	myFrames.push_back(choice);
	myFrames.push_back(playerHP);
	myFrames.push_back(enemyHP);
}

Combat::~Combat()
{
	delete enemy;
	delete text;
	delete text1;
	delete choice;
	delete melee;
	delete range;
	delete magic;
	delete bash;
	delete charge;
	delete stun;
	delete freeze;
	delete shock;
	delete potions;
	delete backUp;
	delete moveIn;
	delete playerHP;
	delete enemyHP;
}

void Combat::update(float delta)
{
	Branch::update(delta);
	updateMenu();

	string hpText1 = to_string(static_cast<long long>(Character::player->getStats().health))
		+ "/" + to_string(static_cast<long long>(Character::player->getHealth()));
	playerHP->calculateBar(hpText1, Character::player->getStats().health, Character::player->getHealth());
	string hpText2 = to_string(static_cast<long long>(enemy->getStats().health))
		+ "/" + to_string(static_cast<long long>(enemy->getBaseStats().health));
	enemyHP->calculateBar(hpText2, enemy->getStats().health, enemy->getBaseStats().health);
}

void Combat::draw(Canvas* canvas)
{
	Branch::draw(canvas);
}

void Combat::start(float delta)
{
	if (text->isFinished())
	{
		state = Input;
		choice->setHidden(false);
	}
}

void Combat::input(float delta)
{
	int input = choice->input();

	if (input != -1)
	{
		state = End;
		if (input == backUpChoice)
		{
			text->setText(false, "Back up");
			distance = 10;
		}
		else if (input == moveInChoice)
		{
			text->setText(false, "Move in");
			distance = 0;
		}
		else if (input == potionsChoice)
		{
			text->setText(false, "Use potion");
			Character::player->useHPPotion();
		}
		else if (Random::random(1, 100) > enemy->getStats().dodge)
		{
			text->setText(false, "Hit");
			playerMiss = false;
			if (input == meleeChoice)
			{
				enemy->inflict(Character::player->getStats().melee, 0, 0);
			}
			else if (input == rangeChoice)
			{
				enemy->inflict(0, Character::player->getStats().range, 0);
			}
			else if (input == magicChoice)
			{
				enemy->inflict(0, 0, Character::player->getStats().magic);
			}
			else if (input == knightBash)
			{
				enemy->inflict(Character::player->getStats().melee / 2, 0, 0);

				if (Random::random(1, 100) > 50)
					enemyStunned = true;
			}
			else if (input == knightCharge)
			{
				enemy->inflict(Character::player->getStats().melee * 2 / 3, 0, 0);
				distance = 0;
			}
			else if (input == rangerStun)
			{
				enemy->inflict(Character::player->getPetDmg() * 2 / 3, 0, 0);

				if (Random::random(1, 100) > 67)
					enemyStunned = true;
			}
			else if (input == wizardFreeze)
			{
				enemyRooted = true;
			}
			else if (input == wizardShock)
			{
				enemy->inflict(0, 0, Character::player->getStats().magic / 2);

				if (Random::random(1, 100) > 67)
					enemyStunned = true;
			}
		}
		else
		{
			playerMiss = true;
			text->setText(false, "Miss");
		}
	}
}
void Combat::end(float delta)
{
	if (Random::random(1, 100) > Character::player->getStats().dodge)
	{
		Character::player->inflict(enemy->getStats().melee, enemy->getStats().range, enemy->getStats().magic);
	}
	state = Start;
}

void Combat::updateMenu()
{
	choice->clear();
	int count = 0;

	//BASIC ATTACKS
	if (Character::player->getWeapon().getStats().melee > 0 && distance <= 0)
	{
		meleeChoice = count;
		melee->setText(false, "Attack with your <LIGHTCYAN>" + Character::player->getWeapon().getName()
			+ "<LIGHTGRAY> (" + to_string(static_cast<long long>(Character::player->getStats().melee))
			+ " Dmg)");
		melee->setPosition(0, count + 1);
		choice->addMember(melee);
		count++;
	}
	if (Character::player->getWeapon().getStats().range > 0)
	{
		rangeChoice = count;
		range->setText(false, "Shoot with your <LIGHTCYAN>" + Character::player->getWeapon().getName()
			+ "<LIGHTGRAY> (" + to_string(static_cast<long long>(Character::player->getStats().range))
			+ " Dmg)");
		range->setPosition(0, count + 1);
		choice->addMember(range);
		count++;
	}
	if (Character::player->getWeapon().getStats().magic > 0)
	{
		magicChoice = count;
		magic->setText(false, "Cast magic with your <LIGHTCYAN>" + Character::player->getWeapon().getName()
			+ "<LIGHTGRAY> (" + to_string(static_cast<long long>(Character::player->getStats().magic))
			+ " Dmg)");
		magic->setPosition(0, count + 1);
		choice->addMember(magic);
		count++;
	}

	//CLASS ABILITIES
	if (Character::player->getRole() == Knight)
	{
		if (Character::player->getWeapon().getStats().melee > 0  && distance <= 0)
		{
			knightBash = count;
			bash->setText(false, "Pummel with your <LIGHTCYAN>" + Character::player->getWeapon().getName()
				+ "<LIGHTGRAY> (50% Stun, " + to_string(static_cast<long long>(Character::player->getStats().melee / 2))
				+ " Dmg)");
			bash->setPosition(0, count + 1);
			choice->addMember(bash);
			count++;
		}
		if (distance > 0)
		{
			knightCharge = count;
			charge->setText(false, "Charge with your <LIGHTCYAN>" + Character::player->getWeapon().getName()
				+ "<LIGHTGRAY> (Close distance, " + to_string(static_cast<long long>(Character::player->getStats().melee * 2 / 3))
				+ " Dmg)");
			charge->setPosition(0, count + 1);
			choice->addMember(charge);
			count++;
		}
	}
	else if (Character::player->getRole() == Ranger)
	{
		rangerStun = count;
		stun->setText(false, "Command your <YELLOW>" + Character::player->getPet()
			+ "<LIGHTGRAY> to stun (33% Stun, " + to_string(static_cast<long long>(Character::player->getPetDmg() * 2 / 3))
			+ " Dmg)");
		stun->setPosition(0, count + 1);
		choice->addMember(stun);
		count++;
	}
	else if (Character::player->getRole() == Wizard)
	{
		wizardFreeze = count;
		freeze->setText(false, "Freeze the enemy with your <LIGHTCYAN>" + Character::player->getWeapon().getName()
			+ "<LIGHTGRAY> (Root for 1 round)");
		freeze->setPosition(0, count + 1);
		choice->addMember(freeze);
		count++;

		wizardShock = count;
		shock->setText(false, "Shock the enemy with your <LIGHTCYAN>" + Character::player->getWeapon().getName()
			+ "<LIGHTGRAY> (33% Stun, " + to_string(static_cast<long long>(Character::player->getStats().magic / 2))
			+ " Dmg)");
		shock->setPosition(0, count + 1);
		choice->addMember(shock);
		count++;
	}
	Usables use = Character::player->getUsables();
	if (use.hpPotions > 0)
	{
		potionsChoice = count;
		potions->setText(false, "Use <LIGHTRED>HP potion");
		potions->setPosition(0, count + 1);
		choice->addMember(potions);
		count++;
	}
	if (distance <= 0)
	{
		backUpChoice = count;
		backUp->setText(false, "Back away (Add 10ft between you and the enemy)");
		backUp->setPosition(0, count + 1);
		choice->addMember(backUp);
		count++;
	}
	else
	{
		moveInChoice = count;
		moveIn->setText(false, "Move in (Close distance by 10ft)");
		moveIn->setPosition(0, count + 1);
		choice->addMember(moveIn);
		count++;
	}

	if (choice->getFocusedIndex() >= count)
		choice->setFocusedIndex(0);
}