#include "stdafx.h"
#include "Random.h"
#include "Tween.h"
#include "Symbol.h"
#include "Canvas.h"
#include "Item.h"
#include "Frame.h"
#include "Text.h"
#include "Animation.h"
#include "StatusBar.h"
#include "Menu.h"
#include "BranchManager.h"
#include "Branch.h"
#include "Reward.h"

Reward::Reward(BranchManager* bm, Branch* newLink, int cr) : Branch(bm)
{
	timer.reset();
	link = newLink;
	link->resetTimer();

	duration = 0.5f;

	//Calculate gold reward
	int randCash = Random::random(75, 125);
	cash.copper = 9 * cr * randCash / 100.0;
	cash.silver = 0;
	cash.gold = 0;
	int cTemp = cash.copper % 10;
	cash.silver += cash.copper / 10.0;
	int sTemp = cash.silver % 10;
	cash.gold += cash.silver / 10.0;
	cash.copper = cTemp;
	cash.silver = sTemp;

	//Calculate xp
	xp = EXPERIENCE_MODIFIER * cr;
	xpCount = 1;

	//Init frames
	Text* message = new Text(false, "", true, 15, 500, 0, 0);
	Animation* cursor = new Animation("cursor.anim", 15, 10, true, false, 3);
	cursor->play();
	loot = new Text(false, "Loot everything!", false, 0, 0, 0, 0);
	menu = new Menu(message, cursor, 0, 0, 72, 80);
	menu->setPosition(CONSOLE_WIDTH / 2 - loot->getDimension().x / 2, 22);
	menu->addMember(loot);
	menu->setHidden(true);

	victory = new Frame("victory.fram", 20, -15);
	victory->setPosition(CONSOLE_WIDTH / 2 - victory->getDimension().x / 2, -15);
	victory->setForegroundColor(FG_YELLOW);
	gold = new Text(false, "<YELLOW># Gold <WHITE># Silver <RED># Copper", false, 0, 0, 0, 0);
	gold->setPosition(CONSOLE_WIDTH / 2 - gold->getDimension().x / 2, 14);
	gold->setHidden(true);
	level = new Text(false, "Level #", false, 0, 0, 0, 0);
	level->setPosition(CONSOLE_WIDTH / 2 - level->getDimension().x / 2, 17);
	level->setHidden(true);
	xpBar = new StatusBar(24, FG_WHITE, BG_BROWN, BG_DARKGRAY, 32, 17);
	xpBar->setHidden(true);
	item = new Text(false, "LOOT", false, 0, 0, 0, 0);
	item->setHidden(true);
	flash = new Animation("flash.anim", 18, 10, true, true, 8);
	flash->setPosition(CONSOLE_WIDTH / 2 - flash->getDimension().x / 2, 10);
	flash->setHidden(true);
	levelUp = new Animation("levelup.anim", 18, 10, true, true, 3);

	if (Random::random(1, 100) > 50)
		giveItem = true;
	else
		giveItem = false;
	goldFinish = xpFinish = lootFinish = false;

	//Generate random item
	int rand = Random::random(1, 100);
	if (rand < 10)
		randomItem = new Item("Elvish Bow", Weapon, cr / 2, cr, 0);
	else if (rand < 20)
		randomItem = new Item("Dwarven Sword", Weapon, cr, 0, cr / 2);
	else if (rand < 30)
		randomItem = new Item("Mage Wand", Weapon, cr / 2, 0, cr );
	else if (rand < 40)
		randomItem = new Item("Steel Plate", Armor, cr * 2, 0, cr);
	else if (rand < 50)
		randomItem = new Item("Leather Armor", Armor, cr / 2, cr, cr / 2);
	else if (rand < 60)
		randomItem = new Item("Red Robes", Armor, 0, cr, cr * 2);
	else if (rand < 70)
		randomItem = new Item("Flame Sword", Weapon, 2 * cr, 0, cr);
	else if (rand < 80)
		randomItem = new Item("Enchanted Bow", Weapon, 0, 2 * cr, cr);
	else if (rand < 90)
		randomItem = new Item("Glowing Staff", Weapon, cr, 0, 2 * cr);
	else
		randomItem = new Item("Wabbajack", Weapon, cr * 5, cr * 5, cr * 5);

	tween = new Tween(SinOut, victory, CONSOLE_WIDTH / 2 - victory->getDimension().x / 2, 6, .7f);
	tween->play();
	myTweens.push_back(tween);

	myFrames.push_back(victory);
	myFrames.push_back(gold);
	myFrames.push_back(item);
	myFrames.push_back(level);
	myFrames.push_back(xpBar);
	myFrames.push_back(flash);
	myFrames.push_back(menu);
}

Reward::~Reward()
{
}
void Reward::update(float delta)
{
	Branch::update(delta);
}

void Reward::draw(Canvas* canvas)
{
	Branch::draw(canvas);
}

void Reward::start(float delta)
{
	if (tween->isFinished())
	{
		flash->setHidden(false);
		flash->play();
		if (!flash->isFinished())
		{
			timer.reset();
		}
		else if (!goldFinish)
		{
			gold->setHidden(false);
			gold->setText(false, "<YELLOW>" + to_string(static_cast<long long>(cash.gold * (timer.getTime() / duration))) 
				+ " Gold" + "   <WHITE>" + to_string(static_cast<long long>(cash.silver * (timer.getTime() / duration)))
				+ " Silver" + "   <RED>" + to_string(static_cast<long long>(cash.copper * (timer.getTime() / duration)))
				+ " Copper");
			gold->setPosition(CONSOLE_WIDTH / 2 - gold->getDimension().x / 2, 14);

			if (!goldFinish && timer.getTime() > duration)
			{
				goldFinish = true;
				timer.reset();
				duration = 1.0f / (Character::player->getLevel() * 100);
			}
		}
		else if (!xpFinish)
		{
			if (timer.getTime() > 0.5f)
			{
				level->setHidden(false);
				xpBar->setHidden(false);

				if (timer.getTime() > 1)
				{
					float currentTime = timer.getTime() - 1;

					while (currentTime > duration * xpCount && xp > 0)
					{
						Character::player->addXP(1);
						xp--;
						xpCount++;
					}

					if (xp == 0)
					{
						xpFinish = true;
						timer.reset();
					}
				}

				string hpText2 = to_string(static_cast<long long>(Character::player->getXP()))
					+ "/" + to_string(static_cast<long long>(Character::player->getXPToLevel()));
				xpBar->calculateBar(hpText2, Character::player->getXP(), Character::player->getXPToLevel());

				level->setText(false, "<WHITE>Level " + to_string(static_cast<long long>(Character::player->getLevel())));
				level->setPosition(32 - level->getDimension().x - 1, 17);
			}
		}
		else if (!lootFinish)
		{
			if (giveItem)
			{
				if (timer.getTime() > 0.5f)
				{
					item->setHidden(false);
					item->setText(false, "You found: <LIGHTCYAN>" + randomItem->getName());
					item->setPosition(CONSOLE_WIDTH / 2 - item->getDimension().x / 2, 20);
				}
			}
			else
			{
				if (timer.getTime() > 0.5f)
				{
					item->setHidden(false);
					item->setText(false, "You didn't find any new equipment :(");
					item->setPosition(CONSOLE_WIDTH / 2 - item->getDimension().x / 2, 20);
				}
			}
			if (timer.getTime() > 1)
			{
				lootFinish = true;
				timer.reset();
			}
		}
		else
		{
			if (timer.getTime() > 0.5f)
			{
				state = Input;
				menu->setHidden(false);
			}
		}
	}
}

void Reward::input(float delta)
{
	int input = menu->input();

	if (input != -1)
	{
		if (input == 0)
		{
			state = End;
			if (giveItem)
			{
				Item item;
				item.setItemType(randomItem->getItemType());
				item.setName(randomItem->getName());
				item.setStats(randomItem->getStats());
				Character::player->addItem(item);
			}
			Character::player->earnGold(cash.gold, cash.silver, cash.copper);
			Character::player->calculateGold();
		}
	}
}

void Reward::end(float delta)
{
	link->init();
	manager->swap(link);
}