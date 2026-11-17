#ifndef PUZZLE_HPP
#define PUZZLE_HPP

#include <string>
#include "Interactable.hpp"

// Forward declaration since only an Item pointer is needed.
class Item;

// Abstract class that inherits from Interactable.
// Uses the Template Method pattern to handle common puzzle steps.
// RiddlePuzzle checks words, while CodePuzzle checks codes.
class Puzzle : public Interactable
{
public:
    Puzzle();
    Puzzle(const std::string& name, const std::string& description,
           const std::string& prompt, const std::string& hint,
           const std::string& requiredFlag, Item* reward);

    // Handles the common puzzle-solving process.
    void interact(Player& player, GameState& state) override;

    // Pure virtual function implemented by each puzzle type.
    // const prevents changes to the puzzle.
    virtual bool checkAnswer(const std::string& answer) const = 0;

    bool isSolved() const;
    int getAttempts() const;

    // No destructor needed since Mansion owns the reward Items.

private:
    std::string prompt;         // Puzzle question
    std::string hint;           // Hint after 3 wrong attempts
    std::string requiredFlag;   // Required clue, empty if none
    Item* reward;               // Reward pointer, nullptr if none
    bool solved;
    int attempts;               // Wrong answer count
};

#endif