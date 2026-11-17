// Puzzle uses the Template Method pattern to handle common puzzle steps.
// RiddlePuzzle and CodePuzzle inherit from it and check answers differently.
// Puzzle is abstract and only points to rewards owned by Mansion.

#include "Puzzle.hpp"

#include <iostream>
#include "Player.hpp"       // Player inventory
#include "Inventory.hpp"    // Add rewards
#include "Item.hpp"         // Item names
#include "GameState.hpp"    // Game flags
#include "InputUtils.hpp"   // User input

// Default constructor starts an unsolved puzzle with no reward.
Puzzle::Puzzle()
    : Interactable("Puzzle", "A strange puzzle."),
      prompt("What is the answer?"),
      hint("There is no hint."),
      requiredFlag(""),
      reward(nullptr),
      solved(false),
      attempts(0)
{
}

// Sets puzzle details and stores a pointer to the reward.
Puzzle::Puzzle(const std::string& name, const std::string& description,
               const std::string& prompt, const std::string& hint,
               const std::string& requiredFlag, Item* reward)
    : Interactable(name, description),
      prompt(prompt),
      hint(hint),
      requiredFlag(requiredFlag),
      reward(reward),
      solved(false),
      attempts(0)
{
}

// Template Method handles the solving process for all puzzles.
void Puzzle::interact(Player& player, GameState& state)
{
    // Prevent solving the same puzzle again.
    if (solved)
    {
        std::cout << "You have already solved this.\n";
        return;
    }

    // Check if the required clue has been found.
    if (requiredFlag != "" && !state.hasFlag(requiredFlag))
    {
        std::cout << getDescription() << "\n";
        std::cout << "You cannot make sense of it yet.\n";
        return;
    }

    // Ask the player for an answer.
    std::cout << prompt << "\n";
    std::cout << "Your answer: ";
    std::string answer = readLine();

    // Calls the subclass's checkAnswer() using polymorphism.
    if (checkAnswer(answer))
    {
        solved = true;
        std::cout << "Correct! Something clicks inside the " << getName() << ".\n";

        // Give the reward if one exists.
        if (reward != nullptr)
        {
            player.getInventory().add(reward);
            std::cout << "You received: " << reward->getName() << "\n";
        }
    }
    else
    {
        attempts++;   // Count wrong answers
        std::cout << "That is not right. (Attempt " << attempts << ")\n";

        // Show hint after 3 wrong attempts.
        if (attempts >= 3)
        {
            std::cout << "Hint: " << hint << "\n";
        }
    }
}

// Returns whether the puzzle is solved.
bool Puzzle::isSolved() const
{
    return solved;
}

// Returns the number of wrong attempts.
int Puzzle::getAttempts() const
{
    return attempts;
}