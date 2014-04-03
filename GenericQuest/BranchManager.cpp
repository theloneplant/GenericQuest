#include "stdafx.h"
#include "Canvas.h"
#include "Input.h"
#include "Branch.h"
#include "PlayerStats.h"
#include "PlayerInventory.h"
#include "PauseMenu.h"
#include "BranchManager.h"

BranchManager::BranchManager()
{
	gameStarted = false;
	menuEnabled = false;
	inMenu = false;
}

BranchManager::BranchManager(Branch* branch)
{
	gameStarted = false;
	menuEnabled = false;
	inMenu = false;
	branches.push_back(branch);
}

BranchManager::~BranchManager()
{
	for (unsigned int i = 0; i < branches.size(); i++)
		pop();
}

void BranchManager::update(float delta)
{
	branches.at(branches.size() - 1)->update(delta);

	if (Input::keyHit())
	{
		char input = Input::get();
		if (input == 's' || input == 'p')
		{
			if (gameStarted && !inMenu)
			{
				PlayerStats* stats = new PlayerStats(this);
				push(stats);
				inMenu = true;
			}
		}
		else if (input == 'i' || input == 'b')
		{
			if (gameStarted && !inMenu)
			{
				PlayerInventory* inv = new PlayerInventory(this);
				push(inv);
				inMenu = true;
			}
		}
		else if (input == 27)
		{
			if (inMenu)
			{
				branches.back()->setState(End);
			}
			else if(menuEnabled)
			{
				PauseMenu* pause = new PauseMenu(this);
				push(pause);
				inMenu = true;
			}
		}
	}
}

void BranchManager::draw(Canvas* canvas)
{
	for (unsigned int i = 0; i < branches.size(); i++)
	{
		branches.at(i)->draw(canvas);
	}
}

void BranchManager::swap(Branch* newBranch)
{
	pop();
	push(newBranch);
}

void BranchManager::cleanSwap(Branch* newBranch)
{
	for (unsigned int i = 0; i < branches.size(); )
	{
		pop();
		inMenu = false;
	}
	push(newBranch);
}

void BranchManager::push(Branch* newBranch)
{
	branches.push_back(newBranch);
}

void BranchManager::pop()
{
	if (branches.size() > 0)
	{
		Branch *old = branches.back();
		branches.pop_back();
		delete old;
	}
}

void BranchManager::setGameStart(bool started)
{
	gameStarted = started;
}

void BranchManager::setMenuEnabled(bool enabled)
{
	menuEnabled = enabled;
}

void BranchManager::setInMenu(bool newInMenu)
{
	inMenu = newInMenu;
}