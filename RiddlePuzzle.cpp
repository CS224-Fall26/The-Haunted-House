// =====================================================================
// RiddlePuzzle.cpp  -  written by Hijab Asif Malik (Member B)
// ---------------------------------------------------------------------
// VIVA SUMMARY
//  * RiddlePuzzle IS-A Puzzle IS-A Interactable (two levels of inheritance).
//  * It INHERITS the whole puzzle procedure (Puzzle::interact, the Template
//    Method) and only fills in the missing step: checkAnswer() for a WORD.
//  * Used for the Writing Desk: "The more of me you take, the more you leave
//    behind. What am I?"  ->  keyword "footsteps", reward Brass Key.
//  * No destructor: it owns nothing on the heap (keyword is a std::string,
//    which cleans itself up).
// =====================================================================
#include "RiddlePuzzle.hpp"
#include "InputUtils.hpp"   // cleanText()

// DEFAULT CONSTRUCTOR: builds the Puzzle part with Puzzle(), then the keyword.
RiddlePuzzle::RiddlePuzzle()
    : Puzzle(),
      keyword("")
{
}

// PARAMETERIZED CONSTRUCTOR
// The first six values belong to Puzzle (and Interactable above it), so they
// are passed UP to the Puzzle constructor. Only "keyword" is stored here.
RiddlePuzzle::RiddlePuzzle(const std::string& name, const std::string& description,
                           const std::string& prompt, const std::string& hint,
                           const std::string& requiredFlag, Item* reward,
                           const std::string& keyword)
    : Puzzle(name, description, prompt, hint, requiredFlag, reward),
      keyword(keyword)
{
}

// OVERRIDES the pure virtual Puzzle::checkAnswer().
// cleanText() (Jazib's helper) makes a lower-case copy with no spaces, so
// "FootSteps", " footsteps " and "foot steps" all match "footsteps".
// const: checking an answer never changes the puzzle.
bool RiddlePuzzle::checkAnswer(const std::string& answer) const
{
    return cleanText(answer) == cleanText(keyword);
}
