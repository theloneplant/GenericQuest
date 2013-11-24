#ifndef FILEIO
#define FILEIO

#include <string>
#include "Symbol.h"
#include "Frame.h"

using namespace std;

class FileIO
{
	public:
		static void buildFrame(string file, vector<vector<Symbol>>& frame, Dimension& dim);
		static void buildAnimation(string file, vector<Frame*>& anim, Dimension& dim);
		static void buildText(bool useFile, string file, vector<vector<Symbol>>& frame, Dimension& dim);
};

#endif