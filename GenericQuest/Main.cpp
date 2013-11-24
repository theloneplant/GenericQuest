#include "stdafx.h"
#include "Canvas.h"
#include "Branch.h"
#include "MainMenu.h"
#include "BranchManager.h"
#include "Timer.h"

using namespace std;

int getInput(int min, int max);
vector<string> getWords(string line);
bool print(string fileName);
int getColor(string color);

void update();
void draw(Canvas& canvas);

int main()
{
	HANDLE screen = GetStdHandle( STD_OUTPUT_HANDLE );
	
	SetConsoleTitle("Generic Quest");

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(screen, &cursorInfo);
    cursorInfo.bVisible = false; // set the cursor visibility
    SetConsoleCursorInfo(screen, &cursorInfo);

	// Remember how things were when we started
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo( screen, &csbi );

	BranchManager bm;
	MainMenu blah(&bm);
	bm.add(&blah);
	Canvas canvas;
	Timer timer;
	float delta = 0;
	COORD pos = {0, 23};

	cout << fixed << setprecision(1);

	while(true)
	{
		delta = timer.getDelta();
		bm.update(delta);
		bm.draw(&canvas);

		canvas.draw(screen);
		
		/*
		if (1 / delta < 500)
		{
			SetConsoleCursorPosition(screen, pos);
			cout << 1 / delta << " FPS";
		}

		if (_kbhit())
		{
			pos.Y = 24;
			SetConsoleCursorPosition(screen, pos);
			char ch = _getch();
			cout << "Your character was: " << ch;
			pos.Y = 23;
		}
		*/
	}
	
	if (print("Test.txt"))
	{
		_getch();
	}

	SetConsoleTextAttribute( screen, csbi.wAttributes );

	cout << "Press any key to continue...";
	_getch();
	return 0;
}

int getInput(int min, int max) //Number between these values
{
	bool flag = false;
	int value = 0;

	while(!flag)
	{
		value = _getch() - '0';

		for (int i = min; i <= max; i++)
		{
			if (value == i)
				return value;
		}
		//cout << "Please enter a number between " << min << "-" << max << endl;
	}

	return value;
}

string wordWrap(string line) //Doesn't count for tabs
{
	string newLine = line;
	if (line.length() > 80)
	{
		for (int i = 1; i <= (int)newLine.length() / 80; i++) //For each "line"
		{
			int tmp = i * 80 - 1;

			while (!isspace(newLine.at(tmp)))
			{
				tmp--;

				if (isspace(newLine.at(tmp)))
				{
					newLine.insert(newLine.begin() + tmp, '\n');
				}
			}

			tmp++;

			do
			{
				newLine.erase(newLine.begin() + tmp);
			}while(isspace(newLine.at(tmp)));
		}
	}
	return newLine;
}

bool print(string fileName)
{
	bool tag = false, set = false;
	ifstream stream(fileName.c_str());
	if (stream.fail())
		return false;

	string text = "";

	while(getline(stream, text))
	{
		text = wordWrap(text);
		string tagType = "";

		for(int i = 0; i < (int)text.length(); i++)
		{
			//set = true;

			if(text.at(i) == '<')
			{
				tag = true;
			}
			else if (text.at(i) == '>')
			{
				tag = false;
				set = false;
			}
			else if (tag)
			{
				tagType.append(1, text.at(i)); // Word wrapping bug, it looks at the tags as well
			}
			else if (!set)
			{
				set = true;
				HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );
				SetConsoleTextAttribute(hstdout, getColor(tagType));
				tagType = "";

				cout << text.at(i);
				Sleep(10);
			}
			else
			{
				cout << text.at(i);
				Sleep(10);
			}
		}
		cout << endl;
		Sleep(1000);
	}
	return true;
}