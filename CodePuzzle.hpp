// CodePuzzle.hpp  -  written by Hijab Asif Malik (Member B). See CodePuzzle.cpp for the full viva notes.
#ifndef CODEPUZZLE_HPP
#define CODEPUZZLE_HPP

#include <string>
#include "Puzzle.hpp"

// CodePuzzle IS-A Puzzle: same procedure, different answer check.
// Used for the Bookshelf (4132), Grandfather Clock (315 or 3:15) and Chest (1704).
// One class serves three puzzles; only their DATA differs.
class CodePuzzle : public Puzzle
{
public:
    CodePuzzle();
    CodePuzzle(const std::string& name, const std::string& description,
               const std::string& prompt, const std::string& hint,
               const std::string& requiredFlag, Item* reward,
               const std::string& code, const std::string& altCode);

    bool checkAnswer(const std::string& answer) const override;

private:
    std::string code;      // the correct code, e.g. "4132"
    std::string altCode;   // another accepted form, e.g. "3:15"; "" = none
};

#endif
