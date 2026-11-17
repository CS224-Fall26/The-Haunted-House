// Puzzle.hpp  -  written by Hijab Asif Malik (Member B). See Puzzle.cpp for the full viva notes.
#ifndef PUZZLE_HPP
#define PUZZLE_HPP

#include <string>
#include "Interactable.hpp"

// Forward declaration: Puzzle only stores a POINTER to its reward Item.
class Item;

// Puzzle IS-A Interactable, and it is ABSTRACT too (checkAnswer is pure virtual).
//
// DESIGN PATTERN: TEMPLATE METHOD
//   interact() is the "template method": it fixes the ORDER of the steps that
//   every puzzle follows (already solved? clue found? ask, check, reward or
//   count the failure, hint after 3 tries). This code is written ONCE here.
//   checkAnswer() is the one step that differs, so each subclass fills it in:
//     RiddlePuzzle compares a word, CodePuzzle compares a number code.
//   Adding a new kind of puzzle later = write one small checkAnswer().
class Puzzle : public Interactable
{
public:
    Puzzle();
    Puzzle(const std::string& name, const std::string& description,
           const std::string& prompt, const std::string& hint,
           const std::string& requiredFlag, Item* reward);

    // THE TEMPLATE METHOD (overrides Interactable::interact).
    void interact(Player& player, GameState& state) override;

    // THE STEP SUBCLASSES FILL IN. Pure virtual, so Puzzle stays abstract.
    // const: checking an answer never changes the puzzle.
    virtual bool checkAnswer(const std::string& answer) const = 0;

    bool isSolved() const;
    int getAttempts() const;

    // No destructor needed: Puzzle owns nothing on the heap.
    // AGGREGATION: Puzzle only POINTS to its reward Item. Mansion owns every
    // Item and deletes it, so Puzzle must never delete the reward.

private:
    std::string prompt;         // the question shown to the player
    std::string hint;           // shown after 3 wrong answers
    std::string requiredFlag;   // clue needed first; "" = no clue needed
    Item* reward;               // given on success; nullptr = no reward
    bool solved;
    int attempts;               // number of WRONG answers so far
};

#endif
