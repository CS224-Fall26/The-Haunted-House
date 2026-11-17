// =====================================================================
// Puzzle.cpp  -  written by Hijab Asif Malik (Member B)
// ---------------------------------------------------------------------
// VIVA SUMMARY
//  * DESIGN PATTERN: TEMPLATE METHOD.
//      - interact() is the TEMPLATE METHOD: it fixes the ORDER of the steps
//        that every puzzle follows. It is written ONCE, here in the base class.
//      - checkAnswer() is the ONE STEP that is different for each puzzle, so
//        it is PURE VIRTUAL and each subclass writes its own version:
//          RiddlePuzzle -> compares a word   (Writing Desk: "footsteps")
//          CodePuzzle   -> compares a code   (Bookshelf 4132, Clock 315, Chest 1704)
//      - WHY: without it, every puzzle class would copy the same "solved? /
//        clue? / attempts / hint / reward" code. A bug fix would be needed in
//        every copy. Now a new kind of puzzle only needs one small function.
//  * Puzzle is ABSTRACT (checkAnswer is "= 0"), so you cannot create a plain
//    Puzzle, only RiddlePuzzle or CodePuzzle.
//  * TWO-LEVEL INHERITANCE: RiddlePuzzle -> Puzzle -> Interactable.
//  * AGGREGATION: Puzzle only POINTS to its reward Item. Mansion owns all
//    Items and deletes them, so Puzzle has NO destructor. If Puzzle deleted
//    the reward, the item would be deleted twice (crash) and the Inventory
//    would hold a dangling pointer.
//
// TRACE - player types 4132 at the Bookshelf after reading the Diary:
//   Room calls objects[i]->interact(...)  -> Puzzle::interact runs
//   step 1: solved is false -> continue
//   step 2: requiredFlag is "diaryRead" and the flag exists -> continue
//   step 3: prints the prompt, readLine() returns "4132"
//   step 4: checkAnswer("4132") is VIRTUAL, so CodePuzzle::checkAnswer runs
//           -> returns true -> solved = true -> "Correct!"
//           -> player.getInventory().add(reward) -> "You received: Iron Key"
// =====================================================================
#include "Puzzle.hpp"

#include <iostream>
#include "Player.hpp"       // player.getInventory()
#include "Inventory.hpp"    // getInventory().add(...)
#include "Item.hpp"         // reward->getName()
#include "GameState.hpp"    // state.hasFlag(...)
#include "InputUtils.hpp"   // readLine()

// DEFAULT CONSTRUCTOR
// Calls the Interactable constructor first (base part), then sets Puzzle's
// own members. reward = nullptr means "no reward". A new puzzle always starts
// unsolved with 0 attempts.
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

// PARAMETERIZED CONSTRUCTOR
// RiddlePuzzle and CodePuzzle call this one from their own constructors.
// "Item* reward" only copies the ADDRESS of an Item that Mansion created;
// no new Item is made.
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

// THE TEMPLATE METHOD - the same fixed steps for EVERY kind of puzzle.
// It overrides Interactable::interact(). Subclasses do NOT override this
// function; they only supply checkAnswer().
void Puzzle::interact(Player& player, GameState& state)
{
    // STEP 1: a solved puzzle stays solved (no second reward).
    if (solved)
    {
        std::cout << "You have already solved this.\n";
        return;
    }

    // STEP 2: some puzzles need a clue first, e.g. the Bookshelf needs the
    // "diaryRead" flag. "" means no clue is needed (the Writing Desk).
    // If the clue is missing we stop BEFORE asking, so attempts do not change.
    if (requiredFlag != "" && !state.hasFlag(requiredFlag))
    {
        std::cout << getDescription() << "\n";
        std::cout << "You cannot make sense of it yet.\n";
        return;
    }

    // STEP 3: ask the question. readLine() is Jazib's helper (we never use
    // cin directly, so input problems are handled in one place).
    std::cout << prompt << "\n";
    std::cout << "Your answer: ";
    std::string answer = readLine();

    // STEP 4: the step that CHANGES between puzzles.
    // checkAnswer() is VIRTUAL, so C++ looks at the REAL object and runs
    // RiddlePuzzle::checkAnswer or CodePuzzle::checkAnswer.
    if (checkAnswer(answer))
    {
        solved = true;
        std::cout << "Correct! Something clicks inside the " << getName() << ".\n";

        // reward is a pointer, so check it is not nullptr before using it.
        if (reward != nullptr)
        {
            // The Inventory stores the SAME pointer (no copy of the Item).
            player.getInventory().add(reward);
            std::cout << "You received: " << reward->getName() << "\n";
        }
    }
    else
    {
        attempts++;   // count only WRONG answers
        std::cout << "That is not right. (Attempt " << attempts << ")\n";

        // After 3 wrong answers the hint is shown (and on every try after).
        if (attempts >= 3)
        {
            std::cout << "Hint: " << hint << "\n";
        }
    }
}

// const getters: they only read the data.
bool Puzzle::isSolved() const
{
    return solved;
}

int Puzzle::getAttempts() const
{
    return attempts;
}
