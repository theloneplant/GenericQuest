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
#include "MainMenu.h"
#include "Combat.h"

Combat::Combat(BranchManager* bm)
{
	Branch::Branch(bm);
	manager = bm;

	enemy = new Enemy(Character::player->getLevel());
	string fileName = "combat/" + enemy->getName() + "Intro.txt";
	playerDesc = new Text(true, fileName, true, 10, 250, 0, 1);
	petDesc = new Text(false, "", true, 10, 250, 0, 1);
	petDesc->setPaused(true);
	enemyDesc = new Text(false, "", true, 10, 250, 0, playerDesc->getPosition().y + playerDesc->getDimension().y);
	enemyDesc->setPaused(true);

	meleeChoice = rangeChoice = magicChoice = knightBash = knightCharge = rangerStun
		= wizardFreeze = wizardShock = backUpChoice = moveInChoice = potionsChoice = nothingChoice = -1;
	pStunCounter = eStunCounter = pRootCounter = eRootCounter = 0;
	distance = 10;
	playerHit = false;

	//MENU INIT
	Text* message = new Text(false, "What do you do?", false, 0, 0, -2, 0);
	Animation* cursor = new Animation("cursor.anim", 15, 10, true, false, 3);
	cursor->play();

	choice = new Menu(message, cursor, enemyDesc->getPosition().x + 3, 
		enemyDesc->getPosition().y + enemyDesc->getDimension().y + 1, 72, 80);
	
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
	nothing = new Text(false, "", false, 0, 0, 0, 0);

	updateMenu();
	choice->setHidden(true);

	//STATUS BARS
	playerHP = new StatusBar(25, FG_WHITE, BG_RED, BG_DARKGRAY, 1, 21);
	enemyHP = new StatusBar(25, FG_WHITE, BG_RED, BG_DARKGRAY, 54, 21);

	string hpText1 = to_string(static_cast<long long>(Character::player->getStats().health))
			+ "/" + to_string(static_cast<long long>(Character::player->getHealth()));
	playerHP->calculateBar(hpText1, Character::player->getStats().health, Character::player->getHealth());
	string hpText2 = to_string(static_cast<long long>(enemy->getStats().health))
		+ "/" + to_string(static_cast<long long>(enemy->getBaseStats().health));
	enemyHP->calculateBar(hpText2, enemy->getStats().health, enemy->getBaseStats().health);

	//STATUS ICONS
	playerHit = petHit = enemyHit = playerStunned = playerRooted = enemyStunned = enemyRooted = false;

	playerStunFrame = new Animation("combat/stun.anim", playerHP->getPosition().x + playerHP->getDimension().x, 
		playerHP->getPosition().y, true, false, 3);
	playerRootFrame = new Animation("combat/root.anim", playerStunFrame->getPosition().x + playerStunFrame->getDimension().x, 
		playerStunFrame->getPosition().y, true, false, 3);
	enemyStunFrame = new Animation("combat/stun.anim", 0, 0, true, false, 3);
	enemyStunFrame->setPosition(enemyHP->getPosition().x - enemyStunFrame->getDimension().x, enemyHP->getPosition().y);
	enemyRootFrame = new Animation("combat/root.anim", enemyStunFrame->getPosition().x - enemyStunFrame->getDimension().x, 
		enemyStunFrame->getPosition().y, true, false, 3);
	playerStunFrame->play();
	playerStunFrame->setHidden(true);
	playerStunFrame->setForegroundColor(FG_YELLOW);
	playerRootFrame->play();
	playerRootFrame->setHidden(true);
	playerRootFrame->setForegroundColor(FG_LIGHTGREEN);
	enemyStunFrame->play();
	enemyStunFrame->setHidden(true);
	enemyStunFrame->setForegroundColor(FG_YELLOW);
	enemyRootFrame->play();
	enemyRootFrame->setHidden(true);
	enemyRootFrame->setForegroundColor(FG_LIGHTGREEN);

	//NAMES & DISTANCE
	playerName = new Text(false, Character::player->getName(), false, 0, 0, 0, 0);
	playerName->setPosition(playerHP->getPosition().x,
		playerHP->getPosition().y - 1);
	enemyName = new Text(false, enemy->getName(), false, 0, 0, 0, 0);
	enemyName->setPosition(enemyHP->getPosition().x,
		enemyHP->getPosition().y - 1);
	dist = new Text(false, "Distance: " + to_string(static_cast<long long>(distance)) + "ft", false, 0, 0, 0, 0);
	dist->setPosition(CONSOLE_WIDTH / 2 - dist->getDimension().x / 2, 23);

	//ANIMATIONS FOR HIT/MISS
	pHit = new Animation("combat/hit.anim", 0, 0, false, false, 30);
	pHit->setPosition(enemyHP->getPosition().x + enemyHP->getDimension().x / 2 - pHit->getDimension().x / 2, 
		enemyHP->getPosition().y - pHit->getDimension().y / 2);
	pHit->setHidden(true);

	myFrames.push_back(enemyDesc);
	myFrames.push_back(petDesc);
	myFrames.push_back(playerDesc);
	myFrames.push_back(choice);
	myFrames.push_back(playerHP);
	myFrames.push_back(enemyHP);
	myFrames.push_back(playerStunFrame);
	myFrames.push_back(playerRootFrame);
	myFrames.push_back(enemyStunFrame);
	myFrames.push_back(enemyRootFrame);
	myFrames.push_back(playerName);
	myFrames.push_back(enemyName);
	myFrames.push_back(pHit);
	myFrames.push_back(dist);
}

Combat::~Combat()
{
	delete enemy, enemyDesc, petDesc, playerDesc, choice, melee, range, magic, bash, 
		charge, stun, freeze, shock, potions, backUp, moveIn, playerHP, 
		enemyHP, playerStunFrame, playerRootFrame, enemyStunFrame, enemyStunFrame, pHit, dist;
}

void Combat::update(float delta)
{
	Branch::update(delta);
	updateMenu();
}

void Combat::draw(Canvas* canvas)
{
	Branch::draw(canvas);
}

void Combat::start(float delta)
{
	if (playerHit)
	{
		if (playerDesc->isFinished())
		{
			pHit->setPosition(enemyHP->getPosition().x + enemyHP->getDimension().x / 2 - pHit->getDimension().x / 2, 
				enemyHP->getPosition().y - pHit->getDimension().y / 2);
			pHit->play();
			pHit->setHidden(false);
			if (pHit->isFinished())
			{
				timer.reset();
				string hpText2 = to_string(static_cast<long long>(enemy->getStats().health))
					+ "/" + to_string(static_cast<long long>(enemy->getBaseStats().health));
				enemyHP->calculateBar(hpText2, enemy->getStats().health, enemy->getBaseStats().health);
				playerHit = false;
				pHit->restart();
				pHit->pause();
				pHit->setHidden(true);
			}
		}
	}
	else if (petHit && playerDesc->isFinished())
	{
		petDesc->setPaused(false);
		if (petDesc->isFinished())
		{
			pHit->setPosition(enemyHP->getPosition().x + enemyHP->getDimension().x / 2 - pHit->getDimension().x / 2, 
				enemyHP->getPosition().y - pHit->getDimension().y / 2);
			pHit->play();
			pHit->setHidden(false);
			if (pHit->isFinished())
			{
				timer.reset();
				enemy->inflict(Character::player->getPetDmg(), 0, 0);
				string hpText2 = to_string(static_cast<long long>(enemy->getStats().health))
					+ "/" + to_string(static_cast<long long>(enemy->getBaseStats().health));
				enemyHP->calculateBar(hpText2, enemy->getStats().health, enemy->getBaseStats().health);
				petHit = false;
				pHit->restart();
				pHit->pause();
				pHit->setHidden(true);
			}
		}
	}
	else if (enemyHit && petDesc->isFinished() && playerDesc->isFinished())
	{
		enemyDesc->setPaused(false);
		if (enemyDesc->isFinished())
		{
			pHit->setPosition(playerHP->getPosition().x + playerHP->getDimension().x / 2 - pHit->getDimension().x / 2, 
				playerHP->getPosition().y - pHit->getDimension().y / 2);
			pHit->play();
			pHit->setHidden(false);
			if (pHit->isFinished())
			{
				timer.reset();
				string hpText1 = to_string(static_cast<long long>(Character::player->getStats().health))
					+ "/" + to_string(static_cast<long long>(Character::player->getHealth()));
				playerHP->calculateBar(hpText1, Character::player->getStats().health, Character::player->getHealth());
				enemyHit = false;
				pHit->restart();
				pHit->pause();
				pHit->setHidden(true);
			}
		}
	}
	else
	{
		if (enemyDesc->isFinished() && petDesc->isFinished() && playerDesc->isFinished())
		{
			if (Character::player->getStats().health <= 0)
			{
				fadeOut();
				//manager->swap(new MainMenu(manager));
			}
			else if (enemy->getStats().health <= 0)
			{
				fadeOut();
			}
			else
			{
				state = Input;
				choice->setHidden(false);
			}
		}
		else if (petDesc->isFinished() && playerDesc->isFinished())
		{
			enemyDesc->setPaused(false);
		}
		else if (playerDesc->isFinished())
		{
			petDesc->setPaused(false);
		}
	}
}

void Combat::input(float delta)
{
	int input = choice->input();
	int hitRoll;

	if (input != -1)
	{
		const int CRIT = 95;
		state = End;
		hitRoll = Random::random(1, 100);
		if (input == backUpChoice)
		{
			playerHit = false;
			distance += Character::player->getStats().speed;
			playerDesc->setText(false, "You back up " + to_string(static_cast<long long>(Character::player->getStats().speed))
				+ "ft away from the <LIGHTMAGENTA>" + enemy->getName() + "<LIGHTGRAY>, there is now " 
				+ to_string(static_cast<long long>(distance)) + "ft between both of you.");
		}
		else if (input == moveInChoice)
		{
			playerHit = false;
			distance -= Character::player->getStats().speed;
			if (distance < 0)
				distance = 0;
			if (distance > 0)
			{
				playerDesc->setText(false, "You move in towards the <LIGHTMAGENTA>" + enemy->getName() 
					+ "<LIGHTGRAY>, there is now " + to_string(static_cast<long long>(distance)) 
					+ "ft between both of you.");
			}
			else
			{
				playerDesc->setText(false, "You move in towards the <LIGHTMAGENTA>" + enemy->getName() 
					+ "<LIGHTGRAY>, you are now close enough to attack it in melee combat.");
			}
		}
		else if (input == potionsChoice)
		{
			playerHit = false;
			playerDesc->setText(false, "You use an <LIGHTRED>HP Potion<LIGHTGRAY> to restore " 
				+ to_string(static_cast<long long>(Character::player->getBaseStats().health / 2))
				+ " HP.");
			Character::player->useHPPotion();
			string hpText1 = to_string(static_cast<long long>(Character::player->getStats().health))
				+ "/" + to_string(static_cast<long long>(Character::player->getHealth()));
			playerHP->calculateBar(hpText1, Character::player->getStats().health, Character::player->getHealth());
		}
		else if (input == nothingChoice)
		{
			playerHit = false;
			playerDesc->setText(false, "You sit on your ass and do nothing because you're <YELLOW>Stunned<LIGHTGRAY>.");
		}
		else if (hitRoll > enemy->getStats().dodge)
		{
			playerHit = true;

			if (input == meleeChoice)
			{
				if (hitRoll > CRIT)
				{
					enemy->inflict(Character::player->getStats().melee * 2, 0, 0);
					playerDesc->setText(false, "You hit with your <LIGHTCYAN>" 
						+ Character::player->getWeapon().getName() + "<LIGHTGRAY> right in the <LIGHTMAGENTA>"
						+ enemy->getName() + "'s<LIGHTGRAY> knee, dealing <LIGHTRED>double damage<LIGHTGRAY>!");
				}
				else
				{
					enemy->inflict(Character::player->getStats().melee, 0, 0);
					playerDesc->setText(false, "You swing with your <LIGHTCYAN>" 
						+ Character::player->getWeapon().getName() + "<LIGHTGRAY>, striking the <LIGHTMAGENTA>"
						+ enemy->getName() + "<LIGHTGRAY>.");
				}
			}
			else if (input == rangeChoice)
			{
				if (hitRoll > CRIT)
				{
					enemy->inflict(0, Character::player->getStats().range * 2, 0);
					playerDesc->setText(false, "You shoot with your <LIGHTCYAN>" 
						+ Character::player->getWeapon().getName() + "<LIGHTGRAY>, and the arrow hits the <LIGHTMAGENTA>"
						+ enemy->getName() + "<LIGHTGRAY> right in its knee, dealing <LIGHTRED>double damage<LIGHTGRAY>!");
				}
				else
				{
					enemy->inflict(0, Character::player->getStats().range, 0);
					playerDesc->setText(false, "You shoot with your <LIGHTCYAN>" 
						+ Character::player->getWeapon().getName() + "<LIGHTGRAY>, and get a good hit on the <LIGHTMAGENTA>"
						+ enemy->getName() + "<LIGHTGRAY>.");
				}
			}
			else if (input == magicChoice)
			{
				if (hitRoll > CRIT)
				{
					enemy->inflict(0, 0, Character::player->getStats().magic * 2);
					playerDesc->setText(false, "You cast a fireball with your <LIGHTCYAN>" 
						+ Character::player->getWeapon().getName() + "<LIGHTGRAY>, hitting the <LIGHTMAGENTA>"
						+ enemy->getName() + "<LIGHTGRAY> right in its knee, dealing <LIGHTRED>double damage<LIGHTGRAY>!");
				}
				else
				{
					enemy->inflict(0, 0, Character::player->getStats().magic);
					playerDesc->setText(false, "You cast fire with your <LIGHTCYAN>" 
						+ Character::player->getWeapon().getName() + "<LIGHTGRAY>, and the <LIGHTMAGENTA>"
						+ enemy->getName() + "<LIGHTGRAY> gets enveloped in flames.");
				}
			}
			else if (input == knightBash)
			{
				if (hitRoll > CRIT)
				{
					enemyStunned = true;
					eStunCounter = 2;
					enemy->inflict(Character::player->getStats().melee, 0, 0);
					playerDesc->setText(false, "You bash the <LIGHTMAGENTA>" + enemy->getName() 
						+ "<LIGHTGRAY> with your <LIGHTCYAN>" + Character::player->getWeapon().getName() 
						+ "<LIGHTGRAY>, shattering its knee, dealing <LIGHTRED>double damage<LIGHTGRAY>!");
				}
				else
				{
					if (Random::random(1, 100) > 25)
					{
						enemyStunned = true;
						eStunCounter = 2;
					}
					enemy->inflict(Character::player->getStats().melee / 2, 0, 0);
					playerDesc->setText(false, "You bash the <LIGHTMAGENTA>" + enemy->getName() 
						+ "<LIGHTGRAY> with your <LIGHTCYAN>" + Character::player->getWeapon().getName() 
						+ "<LIGHTGRAY>.");
				}
			}
			else if (input == knightCharge)
			{
				if (hitRoll > CRIT)
				{
					enemy->inflict(Character::player->getStats().melee * 4 / 3, 0, 0);
					distance = 0;
					playerDesc->setText(false, "You charge the <LIGHTMAGENTA>" + enemy->getName() 
						+ "<LIGHTGRAY> with your <LIGHTCYAN>" + Character::player->getWeapon().getName() 
						+ "<LIGHTGRAY>, closing your distance and hitting it right in its knee, dealing <LIGHTRED>double damage<LIGHTGRAY>!");
				}
				else
				{
					enemy->inflict(Character::player->getStats().melee * 2 / 3, 0, 0);
					distance = 0;
					playerDesc->setText(false, "You charge  the <LIGHTMAGENTA>" + enemy->getName() 
						+ "<LIGHTGRAY> with your <LIGHTCYAN>" + Character::player->getWeapon().getName() 
						+ "<LIGHTGRAY>, and manage to hit it as you run in, closing your distance.");
				}
			}
			else if (input == rangerStun)
			{
				if (hitRoll > CRIT)
				{
					enemyStunned = true;
					eStunCounter = 2;
					enemy->inflict(Character::player->getPetDmg(), 0, 0);
					distance = 0;
					playerDesc->setText(false,  "Your <YELLOW>" + Character::player->getPet() 
						+ "<LIGHTGRAY> attacks the <LIGHTMAGENTA>" + enemy->getName() 
						+ "<LIGHTGRAY>, biting it in the knee, dealing <LIGHTRED>double damage<LIGHTGRAY>.");
				}
				else
				{
					if (Random::random(1, 100) > 50)
					{
						enemyStunned = true;
						eStunCounter = 2;
					}
					enemy->inflict(Character::player->getPetDmg() / 2, 0, 0);
					distance = 0;
					playerDesc->setText(false,  "Your <YELLOW>" + Character::player->getPet() 
						+ "<LIGHTGRAY> attempts to stun the <LIGHTMAGENTA>"
						+ enemy->getName() + "<LIGHTGRAY> with its <LIGHTCYAN>Swipe<LIGHTGRAY>.");
				}
			}
			else if (input == wizardFreeze)
			{
				if (hitRoll > CRIT)
				{
					enemyRooted = true;
					eRootCounter = 2;
					playerDesc->setText(false, "You cast a ray of frost with your <LIGHTCYAN>" 
						+ Character::player->getWeapon().getName() + "<LIGHTGRAY>, hitting the <LIGHTMAGENTA>" + enemy->getName() 
						+ "<LIGHTGRAY> right in its knee, freezing it completely!");
				}
				else
				{
					if (Random::random(1, 100) > 25)
					{
						enemyRooted = true;
						eRootCounter = 2;
					}
					playerDesc->setText(false, "You cast frost with your <LIGHTCYAN>" 
						+ Character::player->getWeapon().getName() + "<LIGHTGRAY>, and the <LIGHTMAGENTA>"
						+ enemy->getName() + "<LIGHTGRAY> gets hit with an intense cold.");
				}
			}
			else if (input == wizardShock)
			{
				enemy->inflict(0, 0, Character::player->getStats().magic / 2);

				if (hitRoll > CRIT)
				{
					enemyStunned = true;
					eStunCounter = 2;
					enemy->inflict(0, 0, Character::player->getStats().magic);
					playerDesc->setText(false, "You cast a lightning bolt with your <LIGHTCYAN>" 
						+ Character::player->getWeapon().getName() + "<LIGHTGRAY>, hitting the <LIGHTMAGENTA>" + enemy->getName() 
						+ "<LIGHTGRAY> right in its knee, causing it to spasm uncontrollably and dealing <LIGHTRED>double damage<LIGHTGRAY>!");
				}
				else
				{
					if (Random::random(1, 100) > 50)
					{
						enemyStunned = true;
						eStunCounter = 2;
					}
					enemy->inflict(0, 0, Character::player->getStats().magic / 2);
					playerDesc->setText(false, "You cast lightning with your <LIGHTCYAN>" 
						+ Character::player->getWeapon().getName() + "<LIGHTGRAY>, and the <LIGHTMAGENTA>"
						+ enemy->getName() + "<LIGHTGRAY> gets an intense electric jolt sent through it.");
				}
			}
		}
		else
		{
			playerHit = false;
			if (input == meleeChoice)
			{
				if (hitRoll < 5)
				{
					playerDesc->setText(false, "You fall flat on your face as you try to flail your <LIGHTCYAN>" 
						+ Character::player->getWeapon().getName() + "<LIGHTGRAY> in hopes that it might hit something."
						+ " You are stunned the next round.");
					playerStunned = true;
					pStunCounter = 2;
				}
				else if (hitRoll < enemy->getStats().dodge / 2)
				{
					playerDesc->setText(false, "You swing your <LIGHTCYAN>" + Character::player->getWeapon().getName() 
						+ "<LIGHTGRAY>, but as you begin the attack it gets flung to the side and falls flat.");
				}
				else
				{
					playerDesc->setText(false, "You swing your <LIGHTCYAN>" + Character::player->getWeapon().getName() 
						+ "<LIGHTGRAY>, but it scrapes the side of the <LIGHTMAGENTA>" + enemy->getName() 
						+ "<LIGHTGRAY> and falls flat.");
				}
			}
			else if (input == rangeChoice)
			{
				if (hitRoll < 5)
				{
					playerDesc->setText(false, "You try to shoot your <LIGHTCYAN>" + Character::player->getWeapon().getName() 
						+ "<LIGHTGRAY>, but it backfires and you get hit in your beautiful face."
						+ " You are stunned the next round.");
					playerStunned = true;
					pStunCounter = 2;
				}
				else if (hitRoll < enemy->getStats().dodge / 2)
				{
					playerDesc->setText(false, "You shoot your <LIGHTCYAN>" + Character::player->getWeapon().getName() 
						+ "<LIGHTGRAY>, but the projectile curves to the side as it flies past the <LIGHTMAGENTA>"
						+ enemy->getName() + "<LIGHTGRAY>.");
				}
				else
				{
					playerDesc->setText(false, "You shoot your <LIGHTCYAN>" + Character::player->getWeapon().getName() 
						+ "<LIGHTGRAY>, but the projectile just barely glances off the side of the <LIGHTMAGENTA>" 
						+ enemy->getName() + "<LIGHTGRAY>.");
				}
			}
			else if (input == magicChoice)
			{
				if (hitRoll < 5)
				{
					playerDesc->setText(false, "You try to cast with your <LIGHTCYAN>" + Character::player->getWeapon().getName() 
						+ "<LIGHTGRAY>, but the spell backfires and you get shot backwards onto your back."
						+ " You are stunned the next round.");
					playerStunned = true;
					pStunCounter = 2;
				}
				else if (hitRoll < enemy->getStats().dodge / 2)
				{
					playerDesc->setText(false, "You cast with your <LIGHTCYAN>" + Character::player->getWeapon().getName() 
						+ "<LIGHTGRAY>, but the projectile curves to the side as it flies past the <LIGHTMAGENTA>"
						+ enemy->getName() + "<LIGHTGRAY>.");
				}
				else
				{
					playerDesc->setText(false, "You cast with your <LIGHTCYAN>" + Character::player->getWeapon().getName() 
						+ "<LIGHTGRAY>, but the projectile just barely glances off the side of the <LIGHTMAGENTA>" 
						+ enemy->getName() + "<LIGHTGRAY>.");
				}
			}
			else if (input == knightBash)
			{
				if (hitRoll < 5)
				{
					playerDesc->setText(false, "You try to bash the enemy with your <LIGHTCYAN>" + Character::player->getWeapon().getName() 
						+ "<LIGHTGRAY>, but you instead hit a tree and get knocked onto your back."
						+ " You are stunned the next round.");
					playerStunned = true;
					pStunCounter = 2;
				}
				else if (hitRoll < enemy->getStats().dodge / 2)
				{
					playerDesc->setText(false, "You cast with your <LIGHTCYAN>" + Character::player->getWeapon().getName() 
						+ "<LIGHTGRAY>, but the projectile curves to the side as it flies past the <LIGHTMAGENTA>"
						+ enemy->getName() + "<LIGHTGRAY>.");
				}
				else
				{
					playerDesc->setText(false, "You cast with your <LIGHTCYAN>" + Character::player->getWeapon().getName() 
						+ "<LIGHTGRAY>, but the projectile just barely glances off the side of the <LIGHTMAGENTA>" 
						+ enemy->getName() + "<LIGHTGRAY>.");
				}
			}
			else if (input == knightCharge)
			{
				if (hitRoll < 5)
				{
					distance = 0;
					playerDesc->setText(false, "You manage to close the gap, but you stumble and foll onto the ground. You are stunned the next round.");
					playerStunned = true;
					pStunCounter = 2;
				}
				else if (hitRoll < enemy->getStats().dodge / 2)
				{
					distance = 0;
					playerDesc->setText(false, "You close the gap and attack with your <LIGHTCYAN>" + Character::player->getWeapon().getName() 
						+ "<LIGHTGRAY>, but your foot catches on a rock,  causing your weapon to miss the <LIGHTMAGENTA>"
						+ enemy->getName() + "<LIGHTGRAY>.");
				}
				else
				{
					distance = 0;
					playerDesc->setText(false, "You close the gap and attack with your <LIGHTCYAN>" + Character::player->getWeapon().getName() 
						+ "<LIGHTGRAY>, but your strike glances off the side of the <LIGHTMAGENTA>" 
						+ enemy->getName() + "<LIGHTGRAY>.");
				}
			}
			else if (input == rangerStun)
			{
				if (hitRoll < 10)
				{
					playerDesc->setText(false, "Your <YELLOW>" + Character::player->getPet() 
						+ "<LIGHTGRAY> is oblivious to your command and continues on its merry way, attacking the enemy.");
				}
				else
				{
					playerDesc->setText(false,  "Your <YELLOW>" + Character::player->getPet() 
						+ "<LIGHTGRAY> tries to attack, but misses the <LIGHTMAGENTA>"
						+ enemy->getName() + "<LIGHTGRAY>.");
				}
			}
			else if (input == wizardFreeze)
			{
				if (hitRoll < 10)
				{
					playerDesc->setText(false, "You try to cast a frost spell with your <LIGHTCYAN>" + Character::player->getWeapon().getName() 
						+ "<LIGHTGRAY>, but the spell backfires and you get shot backwards onto your back."
						+ " You are stunned the next round.");
					playerStunned = true;
					pStunCounter = 2;
				}
				else
				{
					playerDesc->setText(false, "You cast a frost spell with your <LIGHTCYAN>" + Character::player->getWeapon().getName() 
						+ "<LIGHTGRAY>, but the ice didn't fully conjure, melting immediately and not affecting the <LIGHTMAGENTA>"
						+ enemy->getName() + "<LIGHTGRAY>.");
				}
			}
			else if (input == wizardShock)
			{
				if (hitRoll < 10)
				{
					playerDesc->setText(false, "You try to cast lightning with your <LIGHTCYAN>" + Character::player->getWeapon().getName() 
						+ "<LIGHTGRAY>, but the spell backfires and you get shot backwards onto your back."
						+ " You are stunned the next round.");
					playerStunned = true;
					pStunCounter = 2;
				}
				else
				{
					playerDesc->setText(false, "You cast a lightning spell with your <LIGHTCYAN>" + Character::player->getWeapon().getName() 
						+ "<LIGHTGRAY>, but the lightning misfired, hitting the ground instead of the <LIGHTMAGENTA>"
						+ enemy->getName() + "<LIGHTGRAY>.");
				}
			}
		}
	}
}

void Combat::end(float delta)
{
	const int CRIT = 95;
	//CALCULATE PET HIT
	int randHit = Random::random(1, 100);
	if (Character::player->getRole() == Ranger)
	{
		if (Random::random(1, 100) > enemy->getStats().dodge)
		{
			petHit = true;
			if (randHit > CRIT)
			{
				Character::player->inflict(enemy->getStats().melee * 2, enemy->getStats().range * 2, enemy->getStats().magic * 2);
				enemyDesc->setText(false, "Your " + Character::player->getPet() + " lets out a roar as it attacks the <LIGHTMAGENTA>" + enemy->getName() 
					+ "<LIGHTGRAY>, ripping its knee apart and dealing <LIGHTRED>double damage<LIGHTGRAY>!");
			}
			else
			{
				Character::player->inflict(enemy->getStats().melee, enemy->getStats().range, enemy->getStats().magic);
				enemyDesc->setText(false, "Your " + Character::player->getPet() + " attacks the <LIGHTMAGENTA>" + enemy->getName() 
					+ "<LIGHTGRAY>, hitting it in its side.");
			}
		}
		else
		{
			petHit = false;
			petDesc->setText(false, "Your " + Character::player->getPet() + " stumbles as it swipes at the <LIGHTMAGENTA>" + enemy->getName() 
					+ "<LIGHTGRAY> and misses.");
		}
	}
	else
	{
		petHit = false;
		petDesc->setHidden(true);
	}

	//UPDATE STUN/ROOT FOR PLAYER
	if (playerStunned)
	{
		pStunCounter--;
		if (pStunCounter <= 0)
			playerStunned = false;
	}
	if (playerRooted)
	{
		pRootCounter--;
		if (pRootCounter <= 0)
		{
			pRootCounter = 0;
			playerRooted = false;
		}
	}

	//CALCULATE ENEMY HIT
	randHit = Random::random(1, 100);
	if (enemyStunned)
	{
		enemyDesc->setText(false, "The <LIGHTMAGENTA>" + enemy->getName() 
			+ "<LIGHTGRAY> is stunned at your magnificence for the round.");
		eStunCounter--;
		if (eStunCounter <= 0)
			enemyStunned = false;
	}
	else if (enemyRooted)
	{
		if (enemy->getStats().melee >= enemy->getStats().range && enemy->getStats().melee >= enemy->getStats().magic)
		{
			if (distance <= 0)
			{
				if (randHit > Character::player->getStats().dodge)
				{
					enemyHit = true;
					if (randHit > CRIT)
					{
						Character::player->inflict(enemy->getStats().melee * 2, enemy->getStats().range * 2, enemy->getStats().magic * 2);
						enemyDesc->setText(false, "The <LIGHTMAGENTA>" + enemy->getName() 
							+ "<LIGHTGRAY> is unable to move. It manages to reach and hit you with its <LIGHTCYAN>"
							+ enemy->getWeapon().getName() + "<LIGHTGRAY>, critting for <LIGHTRED>double damage<LIGHTGRAY>.");
					}
					else
					{
						Character::player->inflict(enemy->getStats().melee, enemy->getStats().range, enemy->getStats().magic);
						enemyDesc->setText(false, "The <LIGHTMAGENTA>" + enemy->getName() 
							+ "<LIGHTGRAY> is unable to move. It's close enough that it attacks and hits you with its <LIGHTCYAN>"
							+ enemy->getWeapon().getName() + "<LIGHTGRAY>.");
					}
				}
				else
				{
					enemyHit = false;
					enemyDesc->setText(false, "The <LIGHTMAGENTA>" + enemy->getName() 
						+ "<LIGHTGRAY> is unable to move. It still tries to attack with its <LIGHTCYAN>"
						+ enemy->getWeapon().getName() + "<LIGHTGRAY>, but stumbles and misses you.");
				}
			}
			else
			{
				enemyHit = false;
				enemyDesc->setText(false, "The <LIGHTMAGENTA>" + enemy->getName() 
					+ "<LIGHTGRAY> is stuck, and can't move to attack!");
			}
		}
		else
		{
			if (randHit > Character::player->getStats().dodge)
			{
				enemyHit = true;
				if (randHit > CRIT)
				{
					Character::player->inflict(enemy->getStats().melee * 2, enemy->getStats().range * 2, enemy->getStats().magic * 2);
					enemyDesc->setText(false, "The <LIGHTMAGENTA>" + enemy->getName() 
						+ "<LIGHTGRAY> is unable to move. It shoots with its <LIGHTCYAN>"
						+ enemy->getWeapon().getName() + "<LIGHTGRAY>, critting you for <LIGHTRED>double damage<LIGHTGRAY>.");
				}
				else 
				{
					Character::player->inflict(enemy->getStats().melee, enemy->getStats().range, enemy->getStats().magic);
					enemyDesc->setText(false, "The <LIGHTMAGENTA>" + enemy->getName() 
						+ "<LIGHTGRAY> is unable to move. It shoots with its <LIGHTCYAN>"
						+ enemy->getWeapon().getName() + "<LIGHTGRAY>, hitting you.");
				}
			}
			else
			{
				enemyHit = false;
				enemyDesc->setText(false, "The <LIGHTMAGENTA>" + enemy->getName() 
					+ "<LIGHTGRAY> is unable to move. It shoots with its <LIGHTCYAN>"
					+ enemy->getWeapon().getName() + "<LIGHTGRAY>, but stumbles and misses you.");
			}
		}
	}
	else
	{
		if (enemy->getStats().melee >= enemy->getStats().range && enemy->getStats().melee >= enemy->getStats().magic)
		{
			if (distance <= 0)
			{
				if (randHit > Character::player->getStats().dodge)
				{
					if (randHit > CRIT)
					{
						enemyHit = true;
						Character::player->inflict(enemy->getStats().melee * 2, enemy->getStats().range * 2, enemy->getStats().magic * 2);
						enemyDesc->setText(false, "The <LIGHTMAGENTA>" + enemy->getName() + "<LIGHTGRAY> strikes you in the knee with its <LIGHTCYAN>"
							+ enemy->getWeapon().getName() + "<LIGHTGRAY>, dealing <LIGHTRED>double damage<LIGHTGRAY>.");
					}
					else
					{
						enemyHit = true;
						Character::player->inflict(enemy->getStats().melee, enemy->getStats().range, enemy->getStats().magic);
						enemyDesc->setText(false, "The <LIGHTMAGENTA>" + enemy->getName() + "<LIGHTGRAY> hits you with its <LIGHTCYAN>"
							+ enemy->getWeapon().getName() + "<LIGHTGRAY>.");
					}
				}
				else
				{
					enemyHit = false;
					enemyDesc->setText(false, "The <LIGHTMAGENTA>" + enemy->getName() + "<LIGHTGRAY> attempts to hit you with its <LIGHTCYAN>"
						+ enemy->getWeapon().getName() + "<LIGHTGRAY>, but it falls flat and misses.");
				}
			}
			else 
			{
				enemyHit = false;
				distance -= enemy->getStats().speed;
				if (distance < 0)
					distance = 0;

				if (distance > 0)
				{
					enemyDesc->setText(false, "The <LIGHTMAGENTA>" + enemy->getName() + "<LIGHTGRAY> moves " 
						+ to_string(static_cast<long long>(enemy->getStats().speed)) + "ft towards you. There is now " 
						+ to_string(static_cast<long long>(distance)) + "ft between you and the <LIGHTMAGENTA>" + enemy->getName() + "<LIGHTGRAY>.");
				}
				else
				{
					enemyDesc->setText(false, "The <LIGHTMAGENTA>" + enemy->getName() + "<LIGHTGRAY> moves " 
						+ to_string(static_cast<long long>(enemy->getStats().speed)) + "ft towards you. It is now within melee range.");
				}
			}
		}
		else
		{
			if (randHit > Character::player->getStats().dodge)
			{
				if (randHit > CRIT)
				{
					enemyHit = true;
					Character::player->inflict(enemy->getStats().melee * 2, enemy->getStats().range * 2, enemy->getStats().magic * 2);
					enemyDesc->setText(false, "The <LIGHTMAGENTA>" + enemy->getName() + "<LIGHTGRAY> shoots you in the knee with its <LIGHTCYAN>"
						+ enemy->getWeapon().getName() + "<LIGHTGRAY>, dealing <LIGHTRED>double damage<LIGHTGRAY>.");
				}
				else
				{
					enemyHit = true;
					Character::player->inflict(enemy->getStats().melee, enemy->getStats().range, enemy->getStats().magic);
					enemyDesc->setText(false, "The <LIGHTMAGENTA>" + enemy->getName() + "<LIGHTGRAY> shoots you with its <LIGHTCYAN>"
						+ enemy->getWeapon().getName() + "<LIGHTGRAY>.");
				}
			}
			else
			{
				enemyHit = false;
				enemyDesc->setText(false, "The <LIGHTMAGENTA>" + enemy->getName() + "<LIGHTGRAY> attempts to shoot you with its <LIGHTCYAN>"
					+ enemy->getWeapon().getName() + "<LIGHTGRAY>, but it curves to one side and misses.");
			}
		}
	}

	if (enemyRooted)
	{
		eRootCounter--;
		if (eRootCounter <= 0)
			enemyRooted = false;
	}

	//REPOSITION TEXT
	if (Character::player->getRole() == Ranger)
	{
		petDesc->setPosition(0, playerDesc->getPosition().y + playerDesc->getDimension().y + 1);
		enemyDesc->setPosition(0, petDesc->getPosition().y + petDesc->getDimension().y + 1);
	}
	else
	{
		petDesc->setPosition(0, 0);
		enemyDesc->setPosition(0, playerDesc->getPosition().y + playerDesc->getDimension().y + 1);
	}

	choice->setPosition(enemyDesc->getPosition().x + 3, enemyDesc->getPosition().y + enemyDesc->getDimension().y + 1);
	
	//UPDATE STATUS ICONS
	if (playerStunned)
		playerStunFrame->setHidden(false);
	else
		playerStunFrame->setHidden(true);
	if (playerRooted)
		playerRootFrame->setHidden(false);
	else
		playerRootFrame->setHidden(true);
	if (enemyStunned)
		enemyStunFrame->setHidden(false);
	else
		enemyStunFrame->setHidden(true);
	if (enemyRooted)
		enemyRootFrame->setHidden(false);
	else
		enemyRootFrame->setHidden(true);

	//REPOSITION STATUS ICONS
	if (playerStunFrame->isHidden())
	{
		playerRootFrame->setPosition(playerHP->getPosition().x + playerHP->getDimension().x, 
			playerHP->getPosition().y);
	}
	else
	{
		playerRootFrame->setPosition(playerStunFrame->getPosition().x + playerStunFrame->getDimension().x, 
			playerStunFrame->getPosition().y);
	}
	if (enemyStunFrame->isHidden())
	{
		enemyRootFrame->setPosition(enemyHP->getPosition().x - enemyStunFrame->getDimension().x, 
			enemyHP->getPosition().y);
	}
	else
	{
		enemyRootFrame->setPosition(enemyStunFrame->getPosition().x - enemyStunFrame->getDimension().x, 
		enemyStunFrame->getPosition().y);
	}

	//UPDATE DISTANCE
	dist->setText(false, "Distance: " + to_string(static_cast<long long>(distance)) + "ft");

	petDesc->setPaused(true);
	enemyDesc->setPaused(true);
	state = Start;
}

void Combat::updateMenu()
{
	meleeChoice = rangeChoice = magicChoice = knightBash = knightCharge = rangerStun
		= wizardFreeze = wizardShock = backUpChoice = moveInChoice = potionsChoice = nothingChoice = -1;

	choice->clear();
	int count = 0;

	if (!playerStunned)
	{
		//BASIC ATTACKS
		if (Character::player->getWeapon().getStats().melee > 0 && distance <= 0)
		{
			if (!playerRooted || distance <= 0)
			{
				meleeChoice = count;
				melee->setText(false, "Attack with your <LIGHTCYAN>" + Character::player->getWeapon().getName()
					+ "<LIGHTGRAY> (" + to_string(static_cast<long long>(Character::player->getStats().melee))
					+ " Dmg)");
				melee->setPosition(0, count + 1);
				choice->addMember(melee);
				count++;
			}
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
					+ "<LIGHTGRAY> (75% Stun, " + to_string(static_cast<long long>(Character::player->getStats().melee / 2))
					+ " Dmg)");
				bash->setPosition(0, count + 1);
				choice->addMember(bash);
				count++;
			}
			if (distance > 0)
			{
				if (!playerRooted)
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
		}
		else if (Character::player->getRole() == Ranger)
		{
			rangerStun = count;
			stun->setText(false, "Command your <YELLOW>" + Character::player->getPet()
				+ "<LIGHTGRAY> to stun (50% Stun, " + to_string(static_cast<long long>(Character::player->getPetDmg() / 2))
				+ " Dmg)");
			stun->setPosition(0, count + 1);
			choice->addMember(stun);
			count++;
		}
		else if (Character::player->getRole() == Wizard)
		{
			wizardFreeze = count;
			freeze->setText(false, "Freeze the enemy with your <LIGHTCYAN>" + Character::player->getWeapon().getName()
				+ "<LIGHTGRAY> (75% Root)");
			freeze->setPosition(0, count + 1);
			choice->addMember(freeze);
			count++;

			wizardShock = count;
			shock->setText(false, "Shock the enemy with your <LIGHTCYAN>" + Character::player->getWeapon().getName()
				+ "<LIGHTGRAY> (50% Stun, " + to_string(static_cast<long long>(Character::player->getStats().magic / 2))
				+ " Dmg)");
			shock->setPosition(0, count + 1);
			choice->addMember(shock);
			count++;
		}
		Usables use = Character::player->getUsables();
		if (use.hpPotions > 0)
		{
			potionsChoice = count;
			potions->setText(false, "Use <LIGHTRED>HP potion<LIGHTGRAY> (HP +" 
				+ to_string(static_cast<long long>(Character::player->getBaseStats().health / 2)) + ")");
			potions->setPosition(0, count + 1);
			choice->addMember(potions);
			count++;
		}
		if (distance > 0)
		{
			if (!playerRooted)
			{
				moveInChoice = count;
				moveIn->setText(false, "Move in (Close distance by " 
					+ to_string(static_cast<long long>(Character::player->getStats().speed)) + "ft)");
				moveIn->setPosition(0, count + 1);
				choice->addMember(moveIn);
				count++;
			}
		}
		if (!playerRooted)
		{
			backUpChoice = count;
			backUp->setText(false, "Back away (Add " 
				+ to_string(static_cast<long long>(Character::player->getStats().speed)) + "ft between you and the enemy)");
			backUp->setPosition(0, count + 1);
			choice->addMember(backUp);
			count++;
		}
	}
	else
	{
		nothingChoice = count;
		nothing->setText(false, "Sit on your ass because you're <YELLOW>Stunned");
		nothing->setPosition(0, count + 1);
		choice->addMember(nothing);
		count++;
	}

	if (choice->getFocusedIndex() >= count)
		choice->setFocusedIndex(0);
}

void Combat::fadeOut()
{
	if (timer.getTime() > 1)
		manager->swap(new MainMenu(manager));
}