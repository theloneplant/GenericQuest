#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif

#ifndef STDAFX
#define STDAFX

#include <string>
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <fstream>
#include <vector>
#include <windows.h>
#include <cmath>
#include <time.h>

using namespace std;

const double pi = 3.1415926535897;
const int CONSOLE_WIDTH = 80;
const int CONSOLE_HEIGHT = 24;

#endif