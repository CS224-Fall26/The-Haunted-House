#include "CodePuzzle.hpp"
#include "InputUtils.hpp"

//CodePuzzle inherits from Puzzle and uses the same solving process to check codes. It handles the Bookshelf, Grandfather Clock, and Chest puzzles, each with different codes and rewards. Codes are stored as strings to support symbols and leading zeros, and no destructor is needed.
// Default constructor initializes the puzzle with empty codes.
CodePuzzle::CodePuzzle() 
    : Puzzle(),
      code(""),
      altCode("")
{
}

// Passes the puzzle details to Puzzle and stores both codes.
CodePuzzle::CodePuzzle(const std::string& name, const std::string& description,
                       const std::string& prompt, const std::string& hint,
                       const std::string& requiredFlag, Item* reward,
                       const std::string& code, const std::string& altCode)
    : Puzzle(name, description, prompt, hint, requiredFlag, reward),
      code(code),
      altCode(altCode)
{
}

// Checks if the answer matches the main code or alternative code.
bool CodePuzzle::checkAnswer(const std::string& answer) const
{
    std::string cleaned = cleanText(answer);   // Removes spaces and converts to lowercase

    if (cleaned == cleanText(code))
    {
        return true;
    }
    if (altCode != "" && cleaned == cleanText(altCode))
    {
        return true;   // Accepts the alternative code if provided
    }
    return false;
}
