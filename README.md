# Generic Quest
######A Text Based Adventure for Windows
-------------------------------------------
__Author:__ Michael LaPlante

__Language:__ C/C++

__IDE:__ Microsoft Visual Studio 2010

__Libraries:__ Standard C/C++ Libraries, Windows Console Library

###About
Generic Quest is a text-based adventure RPG that plays off of the common clichés commonly seen in fantasy based stories. The player is able to choose a class of hero to play as, and is always referred to as "Hero."

###Features
The goal of this project is to push the console window to its limit, by creating a canvas that can draw 2D sprites of ASCII art and messages, and animating them with velocities, accelerations, and motion tweening. The rendering engine can also look for tags in text files and set the color of text to a file-specified color. User input is handled on the same thread by using _kbhit() and _getch() to simulate a multithreaded, non-blocking user input to allow animations to play while the user is selecting their choice.

* Optimized console renderer that displays 2D images of text in full color.
* Velocities, accelerations, and motion tweening for use on 2D sprites
* Flexible File IO system with tag parsing
* Non-blocking user input
* Simple combat system
* Branching architecture to allow user choice
