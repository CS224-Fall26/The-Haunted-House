// RiddlePuzzle.hpp  -  written by Hijab Asif Malik (Member B). See RiddlePuzzle.cpp for the full viva notes.
#ifndef RIDDLEPUZZLE_HPP
#define RIDDLEPUZZLE_HPP

#include <string>
#include "Puzzle.hpp"

// RiddlePuzzle IS-A Puzzle IS-A Interactable: a two-level hierarchy.
// It inherits the whole puzzle procedure (interact) from Puzzle and only
// supplies the missing step: how to check a WORD answer.
// Used for the Writing Desk riddle (answer "footsteps").
class RiddlePuzzle : public Puzzle
{
public:
    RiddlePuzzle();
    RiddlePuzzle(const std::string& name, const std::string& description,
                 const std::string& prompt, const std::string& hint,
                 const std::string& requiredFlag, Item* reward,
                 const std::string& keyword);

    bool checkAnswer(const std::string& answer) const override;

private:
    std::string keyword;   // the correct word
};

#endif
