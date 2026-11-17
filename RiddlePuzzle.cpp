// RiddlePuzzle inherits from Puzzle and uses its solving process.
// It checks word answers, like "footsteps" in the Writing Desk puzzle.
// No destructor needed since it doesn't own dynamic memory.

#include "RiddlePuzzle.hpp"
#include "InputUtils.hpp"   // For cleanText()

// Default constructor initializes an empty keyword.
RiddlePuzzle::RiddlePuzzle()
    : Puzzle(),
      keyword("")
{
}

// Passes puzzle details to the base class and stores the keyword.
RiddlePuzzle::RiddlePuzzle(const std::string& name, const std::string& description,
                           const std::string& prompt, const std::string& hint,
                           const std::string& requiredFlag, Item* reward,
                           const std::string& keyword)
    : Puzzle(name, description, prompt, hint, requiredFlag, reward),
      keyword(keyword)
{
}

// Overrides checkAnswer() to compare words.
// cleanText() ignores spaces and capitalization.
bool RiddlePuzzle::checkAnswer(const std::string& answer) const
{
    return cleanText(answer) == cleanText(keyword);
}