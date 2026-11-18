#ifndef INPUTUTILS_HPP
#define INPUTUTILS_HPP

#include <string>
using namespace std;

// Helper functions for validating the input every time the game needs
// the player to type something so that cin never breaks.

int readInt(int min, int max);  //Only allows entering an int between the choices given


string readLine(); // Reads one whole line the player types, spaces included (like their name).


void waitForEnter(); // Shows "Press Enter to continue..." and waits until the player presses Enter.


string cleanText(const string& text); // Gives back a copy of the text in lower case with every space removed (puzzles use this to compare answers)

#endif