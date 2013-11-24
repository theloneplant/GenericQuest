#ifndef SYMBOL
#define SYMBOL

enum Color;

class Symbol
{
    public:
		Symbol();
		Symbol(char newSymbol, int newColor);
		bool operator==(const Symbol &);
		bool operator!=(const Symbol &);
		void setChar(char newSymbol);
		void setForegroundColor(int newColor);
		void setBackgroundColor(int newColor);
		char getChar();
		int  getColor();

	private:
		char symbol;
		int  color;
};
#endif