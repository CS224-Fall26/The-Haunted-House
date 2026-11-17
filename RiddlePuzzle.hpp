#ifndef RIDDLEPUZZLE_HPP
#define RIDDLEPUZZLE_HPP

#include <string>
#include "Puzzle.hpp"

// RiddlePuzzle inherits from Puzzle, which inherits from Interactable.
// It uses Puzzle's interact() and checks word answers through checkAnswer().
class RiddlePuzzle : public Puzzle
{
public:
    RiddlePuzzle();
    RiddlePuzzle(const std::string& name, const std::string& description,
                 const std::string& prompt, const std::string& hint,
                 const std::string& requiredFlag, Item* reward,
                 const std::string& keyword);

    // Overrides the answer-checking function.
    bool checkAnswer(const std::string& answer) const override;

private:
    std::string keyword;   // Correct answer
};

#endif