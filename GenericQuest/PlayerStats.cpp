#include "stdafx.h"
#include "Canvas.h"
#include "Symbol.h"
#include "Frame.h"
#include "Color.h"
#include "Text.h"
#include "Animation.h"
#include "Menu.h"
#include "Tween.h"
#include "Input.h"
#include "Random.h"
#include "Character.h"
#include "BranchManager.h"
#include "Branch.h"
#include "PlayerStats.h"

PlayerStats::PlayerStats(BranchManager* bm)
{
	Branch::Branch(bm);
	manager = bm;
	timer.reset();

	int randRole = Random::random(1, 3);
	if (randRole == 1)
		Character::player->init(Knight);
	else if (randRole == 2)
		Character::player->init(Ranger);
	else if (randRole == 3)
		Character::player->init(Wizard);

	for (int i = 0; i < 10; i++)
		Character::player->levelUp();
	Character::player->earnGold(Random::random(0, 30), Random::random(0, 30), Random::random(0, 30));

	frame = new Frame("stats.fram", 10, -20);

	Text* message = new Text(false, "", false, 0, 0, 0, 0);
	Animation* cursor = new Animation("cursor.anim", 0, 0, true, false, 3);
	cursor->play();
	Text* option1 = new Text(false, "Back", true, 0, 0, 0, 0);

	menu = new Menu(message, cursor, option1, frame->getPosition().x + 28, frame->getPosition().y + 17, 72, 80);

	//PLAYER INFO
	Text* name = new Text(false, Character::player->getName() + "'s Stats", false, 0, 0, 
		frame->getPosition().x + 2, frame->getPosition().y + 3);

	string str = "";
	Color col;
	if (Character::player->getRole() == Knight)
	{
		str = "Knight";
		col = FG_LIGHTRED;
	}
	else if (Character::player->getRole() == Ranger)
	{
		str = "Ranger";
		col = FG_LIGHTGREEN;
	}
	else
	{
		str = "Wizard";
		col = FG_LIGHTBLUE;
	}
	Text* level = new Text(false, "Lvl " + to_string(static_cast<long long>(Character::player->getLevel())), 
		false, 0, 0, frame->getPosition().x + 2, frame->getPosition().y + 9);
	Text* role = new Text(false, " " + str, false, 0, 0, level->getPosition().x + level->getFrame().at(0).size(), frame->getPosition().y + 9);
	role->setForegroundColor(col);

	//HP AND XP
	string hpLeft = to_string(static_cast<long long>(Character::player->getHealth()));
	string hpTotal = to_string(static_cast<long long>(Character::player->getStats().health));
	Text* hp = new Text(false, "HP: " + hpLeft + "/" + hpTotal, 
		false, 0, 0, frame->getPosition().x + 2, frame->getPosition().y + 15);

	string xpLeft = to_string(static_cast<long long>(Character::player->getXP()));
	string xpTotal = to_string(static_cast<long long>(Character::player->getXPToLevel()));
	Text* xp = new Text(false, "XP: " + xpLeft + "/" + xpTotal, 
		false, 0, 0, frame->getPosition().x + 2, frame->getPosition().y + 16);

	//BASE STATS
	Text* strength = new Text(false, "Str: " + to_string(static_cast<long long>(Character::player->getStats().strength)), 
		false, 0, 0, frame->getPosition().x + 2, frame->getPosition().y + 11);
	Text* dexterity = new Text(false, "Dex: " + to_string(static_cast<long long>(Character::player->getStats().dexterity)), 
		false, 0, 0, frame->getPosition().x + 2, frame->getPosition().y + 12);
	Text* intelligence = new Text(false, "Int: " + to_string(static_cast<long long>(Character::player->getStats().intelligence)), 
		false, 0, 0, frame->getPosition().x + 2, frame->getPosition().y + 13);

	//DEFENSE STATS
	Text* armor = new Text(false, "Armor: " + to_string(static_cast<long long>(Character::player->getStats().armor)), 
		false, 0, 0, frame->getPosition().x + 22, frame->getPosition().y + 14);
	Text* dodge = new Text(false, "Dodge: " + to_string(static_cast<long long>(Character::player->getStats().dodge)) + "%", 
		false, 0, 0, frame->getPosition().x + 22, frame->getPosition().y + 15);
	Text* resist = new Text(false, "Resist: " + to_string(static_cast<long long>(Character::player->getStats().resist)), 
		false, 0, 0, frame->getPosition().x + 22, frame->getPosition().y + 16);

	//GOLD
	Text* gold = new Text(false, to_string(static_cast<long long>(Character::player->getGold().gold)) + "g", 
		false, 0, 0, frame->getPosition().x + 48, frame->getPosition().y + 18);
	gold->setForegroundColor(FG_YELLOW);
	Text* silver= new Text(false, to_string(static_cast<long long>(Character::player->getGold().silver)) + "s", 
		false, 0, 0, frame->getPosition().x + 52, frame->getPosition().y + 18);
	silver->setForegroundColor(FG_WHITE);
	Text* copper= new Text(false, to_string(static_cast<long long>(Character::player->getGold().copper)) + "c", 
		false, 0, 0, frame->getPosition().x + 56, frame->getPosition().y + 18);
	copper->setForegroundColor(FG_RED);

	Tween* tween = new Tween(SinOut, frame, 10, 2, 0.3f);
	tween->add(menu);
	tween->add(name);
	tween->add(level);
	tween->add(role);
	tween->add(hp);
	tween->add(xp);
	tween->add(strength);
	tween->add(dexterity);
	tween->add(intelligence);
	tween->add(armor);
	tween->add(dodge);
	tween->add(resist);
	tween->add(gold);
	tween->add(silver);
	tween->add(copper);
	tween->play();

	myFrames.push_back(frame);
	myFrames.push_back(menu);
	myFrames.push_back(name);
	myFrames.push_back(level);
	myFrames.push_back(role);
	myFrames.push_back(hp);
	myFrames.push_back(xp);
	myFrames.push_back(strength);
	myFrames.push_back(dexterity);
	myFrames.push_back(intelligence);
	myFrames.push_back(armor);
	myFrames.push_back(dodge);
	myFrames.push_back(resist);
	myFrames.push_back(gold);
	myFrames.push_back(silver);
	myFrames.push_back(copper);
	myTweens.push_back(tween);
}

PlayerStats::~PlayerStats()
{

}

void PlayerStats::update(float delta)
{
	Branch::update(delta);
	
	for (unsigned int i = 0; i < myTweens.size(); i++)
	{
		myTweens.at(i)->update();
	}
	for (unsigned int i = 0; i < myFrames.size(); i++)
	{
		myFrames.at(i)->update(delta);
	}
}

void PlayerStats::draw(Canvas* canvas)
{
	Branch::draw(canvas);
}

void PlayerStats::start(float delta)
{
	int input = menu->input();

	if (input != -1)
	{
		if (input == 0)
		{
			state = End;
			myTweens.at(0)->restart(10, -22);
			myTweens.at(0)->setDuration(0.3f);
		}
	}
}

void PlayerStats::input(float delta)
{
}

void PlayerStats::end(float delta)
{
	int input = menu->input();

	if (input != -1)
	{
		if (input == 0)
		{
			state = Start;
			myTweens.at(0)->restart(10, 3);
		}
	}
	if (myTweens.at(0)->isFinished())
	{
		Input::clear();
		manager->pop();
	}
}