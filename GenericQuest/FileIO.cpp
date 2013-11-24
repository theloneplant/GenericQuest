#include "stdafx.h"
#include "Color.h"
#include "FileIO.h"

void FileIO::buildFrame(string file, vector<vector<Symbol>>& frame, Dimension& dim)
{
	//Make some temps
	Symbol symbol;
	ifstream stream(file);
	string str;
	int width = 0, height = 0;

	//Calculate width and height
	while (getline(stream, str))
	{
		if (width < str.length())
			width = str.length();

		height++;
	}

	stream.close();

	//Initialize each symbol
	frame.resize(height);
	for (int i = 0; i < height; i++)
	{
		frame.at(i).resize(width);
	}

	stream.open(file);

	//Assign each symbol
	for (int y = 0; y < height; y++)
	{
		getline(stream, str);
		for (int x = 0; x < width; x++)
		{
			if (x < str.length())
				frame.at(y).at(x).setChar(str.at(x));
			else
				frame.at(y).push_back(symbol);
		}
	}

	dim.x = width;
	dim.y = height;

	stream.close();
}

void FileIO::buildAnimation(string file, vector<Frame*>& anim, Dimension& dim)
{
	//Make some temps
	Symbol symbol;
	ifstream stream(file);
	string str;
	int width = 0, height = 0, size = 0;

	//Get the height of each frame
	stream >> height;
	getline(stream, str); // Finish the line

	//Calculate width and size
	while (getline(stream, str))
	{
		if (width < str.length())
			width = str.length();

		size++;
	}
	size /= height; //Size truncates any excess lines

	//Reset stream
	stream.close();
	stream.open(file);

	// Ignore 1st line, we already have its info
	getline(stream, str); 

	//Build the frames
	for (int i = 0; i < size; i++)
	{
		Frame* frame = new Frame();
		frame->setDimension(width, height);

		for (int y = 0; y < height; y++)
		{
			getline(stream, str); //New string every line

			for(int x = 0; x < width; x++)
			{
				if (x < str.length())
					symbol.setChar(str.at(x));
				else
					symbol.setChar('`');

				frame->setSymbol(symbol, x, y);
			}
		}
		anim.push_back(frame);
	}

	dim.x = width;
	dim.y = height;
}

void FileIO::buildText(bool useFile, string file, vector<vector<Symbol>>& frame, Dimension& dim)
{
	vector<vector<Symbol>> columns;
	ifstream stream(file);
	string str;
	string colorName = "LIGHTGRAY";
	int width = 0, count = 0;

	if (useFile)
	{
		//Get colors from tags
		while (getline(stream, str))
		{
			vector<Symbol> row;
			while (count < str.length())
			{
				Symbol symbol;
				if (str.at(count) == '<') //Build the color
				{
					colorName = "";
					str.erase(str.begin() + count);
					while (str.at(count) != '>' && count < str.size())
					{
						colorName.push_back(str.at(count));
						str.erase(str.begin() + count); //Makes it easier to keep my place
					}
				}
				else //Build the string
				{
					symbol.setChar(str.at(count));
					symbol.setForegroundColor(getColor(colorName));
					row.push_back(symbol);
				}
				count++;
			}
			columns.push_back(row);
			count = 0;
		}

		//Word Wrap
		int begin = 0, end = 0;

		for (int y = 0; y < columns.size(); y++) //For each row
		{
			begin = 0;
			end = 0;

			if (columns.at(y).size() > CONSOLE_WIDTH) //If big enough to justify word wrapping
			{
				while(end < columns.at(y).size()) //For each "line"
				{
					vector<Symbol> temp; //Temporary row for final array
					Symbol symbol;
					end = begin + CONSOLE_WIDTH - 1; //Keeps track of the chunks that will be rows

					if (end < columns.at(y).size())
					{
						while (!isspace(columns.at(y).at(end).getChar()))
						{
							end--; //Avoid words
						}

						//Build the new row
						for (int i = begin; i < end; i++)
						{
							temp.push_back(columns.at(y).at(i));
						}

						begin = end + 1; //Avoid that stupid space
						frame.push_back(temp);
					}
					else
					{
						//Build the remaining row
						for (int i = begin; i < columns.at(y).size(); i++)
						{
							temp.push_back(columns.at(y).at(i));
						}
						frame.push_back(temp);
					}
				}
			}
			else
			{
				frame.push_back(columns.at(y));
			}
		}

		//Adjust the size of the frame
		for (int y = 0; y < frame.size(); y++)
		{
			for (int x = 0; x < frame.at(y).size(); x++)
			{
				if (width < frame.at(y).size()) //Find the max width
					width = frame.at(y).size();
			}
		}

		for (int i = 0; i < frame.size(); i++)
		{
			frame.at(i).resize(width); //Set everything to that length with default params
		}
		dim.x = width;
		dim.y = frame.size();
	}
	else
	{
		Symbol symbol;
		frame.resize(1);
		for (int i = 0; i < file.length(); i++)
		{
			symbol.setChar(file.at(i));
			frame.at(0).push_back(symbol);
		}

		dim.x = frame.at(0).size();
		dim.y = frame.size();
	}
}