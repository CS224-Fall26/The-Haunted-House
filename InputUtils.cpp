#include "InputUtils.hpp"

#include <iostream>
using namespace std;

#include <cctype>    // library provides standard functions for classifying and transforming individual characters: tolower() needed to convert char to lowercase
#include <cstdlib>   // Includes string to number conversion methods : atoi

// Reads one full line the player types.
string readLine() 
{
    string line;
    getline(cin, line);
    return line;
}

// Waits until the player presses Enter. Whatever they type is ignored.
void waitForEnter() 
{
    cout << "Press Enter to continue...";
    readLine();
}

// Normalizes the text: every letter becomes lower case and every space is removed
string cleanText(const string& text) 
{
    string result = "";
    for (int i = 0; i < (int)text.size(); i++) 
    {
        char c = text[i];
        if (c != ' ')
        {
            char lower = tolower(c);
            result = result + lower;
        }
    }
    return result;
}

// Keeps asking until the player types a whole number from min to max.
int readInt(int min, int max) {
    while (true) 
    {
        // read what the player typed, as text (safer option because cin would break if letters are typed when cin takes integers)
        string text = readLine();

        // checks that every char is only digits (0 to 9) and not empty.
        bool isDigits = true;
        if (text.empty()) 
        {
            isDigits = false;
        }
        for (int i = 0; i<(int)text.size(); i++) 
        {
            if (text[i]<'0' || text[i]>'9') 
            {
                isDigits = false;
            }
        }

        // if it is digit turn the text into a number and check the range.
        if (isDigits && text.size() <= 6)   //size check for atoi so large int value is rejected
        {
            int number = atoi(text.c_str());  //C_str() converts text into C-style string which atoi accepts 
            if (number >= min && number <= max) 
            {
                return number;   // valid input
            }
        }

        // Invalid input so tell the player and loop around to ask again.
        cout << "Please enter a number between " << min << " and " << max << "."<<endl;
        cout << "Choice: ";
    }
}