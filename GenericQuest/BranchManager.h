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
		void add(Branch* newBranch);

	private:
		vector<Branch*> branches;

		BranchManager(const BranchManager&);
		BranchManager& operator=(const BranchManager&);
};
#endif