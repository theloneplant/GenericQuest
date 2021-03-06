#ifndef BRANCH_MANAGER
#define BRANCH_MANAGER

class Branch;
class Canvas;

class BranchManager
{
    public:
		BranchManager();
		BranchManager(Branch* branch);
		~BranchManager();
		void update(float delta);
		void draw(Canvas* canvas);
		void swap(Branch* newBranch);
		void cleanSwap(Branch* newBranch);
		void push(Branch* newBranch);
		void pop();
		void setGameStart(bool started);
		void setMenuEnabled(bool enabled);
		void setInMenu(bool newInMenu);

	private:
		vector<Branch*> branches;
		bool gameStarted, menuEnabled, inMenu;

		BranchManager(const BranchManager&);
		BranchManager& operator=(const BranchManager&);
};
#endif